#include "HASMRules.h"


typedef struct Label
{
    const char* label;
    u_int32_t ptr;
} Label;

typedef struct Labels
{
    Label* labels;
    int count;
    int capacity;
} Labels;

struct Labels* createLabels()
{
    struct Labels* labels = malloc(sizeof(struct Labels));
    labels->count = 0;
    labels->capacity = 256;
    labels->labels = malloc(sizeof(Label) * 256);
    return labels;
}

void addLabel(struct Labels* labels, struct Label label)
{
    labels->labels[labels->count++] = label;
    if (labels->count == labels->capacity)
    {
        labels->capacity += 256;
        labels->labels = realloc(labels->labels, labels->capacity * sizeof(struct Label));
    }
}

u_int32_t findLabel(struct Labels* labels, char* label)
{
    for (int i = 0; i < labels->count; i++)
    {
        if (strcmp(labels->labels[i].label, label) == 0)
        {
            return labels->labels[i].ptr;
        }
    }
    return -1;
}


void replaceCharsAtOffset(FILE *file, long offset, const char *replacement) {
    // Seek to the specified offset in the file
    if (fseek(file, offset, SEEK_SET) != 0) {
        perror("Error seeking to offset");
        return;
    }

    // Replace characters at the given offset
    size_t replacementLength = strlen(replacement);
    for (size_t i = 0; i < replacementLength; ++i) {
        if (fputc(replacement[i], file) == EOF) {
            perror("Error writing to file");
            return;
        }
    }
}

long GetFileSize(FILE *file) {
    // Save the current position of the file pointer
    long current_pos = ftell(file);
    if (current_pos == -1) {
        perror("ftell");
        return -1;  // Error getting the current position
    }

    // Move to the end of the file
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("fseek");
        return -1;  // Error moving to the end of the file
    }

    // Get the size of the file (current position is the file size)
    long size = ftell(file);
    if (size == -1) {
        perror("ftell");
        return -1;  // Error getting the size of the file
    }

    // Restore the original file pointer position
    fseek(file, current_pos, SEEK_SET);

    return size;
}


#pragma region MOV_Codegen_functions

unsigned char getModRM(unsigned char mod, unsigned char reg, unsigned char rm) {
    unsigned char modRM = (mod << 6) | (reg << 3) | rm;
    return modRM;
}

void hexStringToByteArray(FILE* file, const char* hexString, int size) {
    // Skip the "0x" prefix if it exists
    const char* hex = hexString;
    if (strncmp(hexString, "0x", 2) == 0) {
        hex = hexString + 2;
    }
    
    size_t length = strlen(hex);

    // Ensure that the string length is even
    if (length % 2 != 0) {
        length++;  // Make it even by considering the next character as zero
    }
    

    size_t byteArraySize = length / 2;
    
    // Convert hex string to byte array
    for (size_t i = 0; i < byteArraySize; ++i) {
        u_int8_t byte;
        sscanf(hex + 2 * byteArraySize - 2 * (i+1), "%2hhx", &byte);
        fprintf(file, "%c", byte);
    }
    if (size - (int)byteArraySize > 0)
    {
        for (int i = 0; i < size - byteArraySize; i++)
        {
            fprintf(file, "%c", 0);
        }
    }
}

int file_pointer = 0;
int hexStringSize(const char* hexString) {
    // Skip the "0x" prefix if it exists
    const char* hex = hexString;
    if (strncmp(hexString, "0x", 2) == 0) {
        hex = hexString + 2;
    }

    size_t length = strlen(hex);

    // Ensure that the string length is even
    if (length % 2 != 0) {
        length++;  // Make it even by considering the next character as zero
    }

    return length / 2;
}
// Function to convert unsigned 32-bit to byte array
void handleLoadOffset(FILE* file, int num, int src, int dst) {
    if (num < -127 || num > 127)
    {
        fprintf(file, "%c", getModRM(0b10, src, dst));
        fprintf(file, "%c%c%c%c", num & 0xFF, (num >> 8) & 0xFF, (num >> 16) & 0xFF, (num >> 24) & 0xFF);
    }
    else
    {
        fprintf(file, "%c", getModRM(0b01, src, dst));
        fprintf(file, "%c", num);
    }
}

void handleComplexLoadOffset(FILE* file, int num, int mod, int src_l, int src_r, int dst) {
    if (num < -127 || num > 127)
    {
        fprintf(file, "%c%c", getModRM(0b10, dst, 0b100), getModRM(mod, src_r, src_l));
        fprintf(file, "%c%c%c%c", num & 0xFF, (num >> 8) & 0xFF, (num >> 16) & 0xFF, (num >> 24) & 0xFF);
    }
    else
    {
        fprintf(file, "%c%c", getModRM(0b01, dst, 0b100), getModRM(mod, src_r, src_l));
        fprintf(file, "%c", num);
    }
}
// mov r r
void fileprint_r_r_instruction(FILE* file, u_int8_t instruction, int left_register_size, int left_register_value, int right_register_size, int right_register_value)
{
    if (left_register_size == 8 && right_register_size == 8)
    {
        fprintf(file, "%c%c", instruction-2, getModRM(0b11, right_register_value, left_register_value));
    }
    else if (left_register_size == 16 && right_register_size == 16)
    {
        fprintf(file, "%c%c%c", 0x66, instruction-1, getModRM(0b11, right_register_value, left_register_value));
    }
    else if (left_register_size == 32 && right_register_size == 32)
    {
        fprintf(file, "%c%c", instruction-1, getModRM(0b11, right_register_value, left_register_value));
    }
    else if (left_register_size == 64 && right_register_size == 64)
    {
        fprintf(file, "%c%c%c", 0x48, instruction-1, getModRM(0b11, right_register_value, left_register_value));
    }
}

void fileprint_r_imm_instruction(FILE* file, u_int8_t instruction, int left_register_size, int left_register_value, const char* imm)
{
    if (instruction == 0xb0)
    {
        if (left_register_size == 8)
        {
            fprintf(file, "%c", 0xB0 + left_register_value);
            hexStringToByteArray(file, imm, 1);
        }
        else if (left_register_size == 16)
        {
            fprintf(file, "%c%c", 0x66, 0xB8 + left_register_value);
            hexStringToByteArray(file, imm, 2);
        }
        else if (left_register_size == 32)
        {
            fprintf(file, "%c", 0xB8 + left_register_value);
            hexStringToByteArray(file, imm, 4);
        }
        else if (left_register_size == 64)
        {
            int size = hexStringSize(imm);
            if (size <= 4)
            {
                fprintf(file, "%c%c%c", 0x48, 0xC7, 0xC0 + left_register_value);
                hexStringToByteArray(file, imm, 4);
            }
            else
            {
                fprintf(file, "%c%c", 0x48, 0xB8 + left_register_value);
                hexStringToByteArray(file, imm, 8);
            }
        }
    }
    else
    {
    // instruction is 0xB0
        if (left_register_size == 8)
        {
            fprintf(file, "%c%c", 0x80, instruction + left_register_value);
            hexStringToByteArray(file, imm, 1);
        }
        else if (left_register_size == 16)
        {
            int size = hexStringSize(imm);
            if (size == 1)
            {
                fprintf(file, "%c%c%c", 0x66, 0x83, instruction + left_register_value);
                hexStringToByteArray(file, imm, 1);
            }
            else
            {
                fprintf(file, "%c%c%c", 0x66, 0x81, instruction + left_register_value);
                hexStringToByteArray(file, imm, 2);
            }
        }
        else if (left_register_size == 32)
        {
            int size = hexStringSize(imm);
            if (size == 1)
            {
                fprintf(file, "%c%c", 0x83, instruction + left_register_value);
                hexStringToByteArray(file, imm, 1);
            }
            else
            {
                fprintf(file, "%c%c", 0x81, instruction + left_register_value);
                hexStringToByteArray(file, imm, 4);
            }
        }
        else if (left_register_size == 64)
        {
            int size = hexStringSize(imm);
            if (size == 1)
            {
                fprintf(file, "%c%c%c", 0x48, 0x83, instruction + left_register_value);
                hexStringToByteArray(file, imm, 1);
            }
            else
            {
                fprintf(file, "%c%c%c", 0x48, 0x81, instruction + left_register_value);
                hexStringToByteArray(file, imm, 4);
            }
        }
    }
}
// MOV r [r]
void fileprint_r_indirect_instruction(FILE* file, u_int8_t instruction, int inverse, int left_register_size, int left_register_value, int right_register_size, int right_register_value)
{
    if (inverse)
    {
        instruction -= 2;
    }

    if (right_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    if (left_register_size == 8)
    {
        fprintf(file, "%c%c", instruction, getModRM(0b00, right_register_value, left_register_value));
    }
    else if (left_register_size == 16)
    {
        fprintf(file, "%c%c%c", 0x66, instruction+1, getModRM(0b00, right_register_value, left_register_value));
    }
    else if (left_register_size == 32)
    {
        fprintf(file, "%c%c", instruction+1, getModRM(0b00, right_register_value, left_register_value));
    }
    else if (left_register_size == 64)
    {
        fprintf(file, "%c%c%c", 0x48, instruction+1, getModRM(0b00, right_register_value, left_register_value));
    }
}
// mov r [n]
void fileprint_r_direct_instruction(FILE* file, u_int8_t instruction, int inverse, int left_register_size, int left_register_value, const char* hex)
{
    if (inverse)
    {
        instruction -= 2;
    }

    if (left_register_size == 8)
    {
        fprintf(file, "%c%c%c", instruction, getModRM(0b00, left_register_value, 0b100), 0x25);
        hexStringToByteArray(file, hex, 4);
    }
    else if (left_register_size == 16)
    {
        fprintf(file, "%c%c%c%c", 0x66, instruction+1, getModRM(0b00, left_register_value, 0b100), 0x25);
        hexStringToByteArray(file, hex, 4);
    }
    else if (left_register_size == 32)
    {
        fprintf(file, "%c%c%c", instruction+1, getModRM(0b00, left_register_value, 0b100), 0x25);
        hexStringToByteArray(file, hex, 4);
    }
    else if (left_register_size == 64)
    {
        fprintf(file, "%c%c%c%c", 0x48, instruction+1, getModRM(0b00, left_register_value, 0b100), 0x25);
        hexStringToByteArray(file, hex, 4);
    }
}
// mov r [r+n]
void fileprint_r_offset_instruction(FILE* file, u_int8_t instruction, int inverse, int offset, int left_register_size, int left_register_value, int right_register_size, int right_register_value)
{
    if (inverse)
    {
        instruction -= 2;
    }

    if (right_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    if (left_register_size == 8)
    {
        fprintf(file, "%c", instruction);
        handleLoadOffset(file, offset, left_register_value, right_register_value);
    }
    else if (left_register_size == 16)
    {
        fprintf(file, "%c%c", 0x66, instruction+1);
        handleLoadOffset(file, offset, left_register_value, right_register_value);
    }
    else if (left_register_size == 32)
    {
        fprintf(file, "%c", instruction+1);
        handleLoadOffset(file, offset, left_register_value, right_register_value);
    }
    else if (left_register_size == 64)
    {
        fprintf(file, "%c%c", 0x48, instruction+1);
        handleLoadOffset(file, offset, left_register_value, right_register_value);
    }

}
// mov r [r+r*n]
void fileprint_r_scaled_instruction(FILE* file, u_int8_t instruction, int inverse, int left_register_size, int left_register_value, int right_left_register_size, int right_left_register_value, int right_right_register_size, int right_right_register_value, int multiple)
{
    if (inverse)
    {
        instruction -= 2;
    }

    if (right_left_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    int mod = 0;
    if (multiple == 1)
    {
        mod = 0b00;
    }
    else if (multiple == 2)
    {
        mod = 0b01;
    }
    else if (multiple == 4)
    {
        mod = 0b10;
    }
    else if (multiple == 8)
    {
        mod = 0b11;
    }
    

    if (left_register_size == 8)
    {
        fprintf(file, "%c%c%c", instruction, getModRM(0b00, left_register_value, 0b100), getModRM(mod, right_right_register_value, right_left_register_value));
    }
    else if (left_register_size == 16)
    {
        fprintf(file, "%c%c%c%c", 0x66, instruction+1, getModRM(0b00, left_register_value, 0b100), getModRM(mod, right_right_register_value, right_left_register_value));
    }
    else if (left_register_size == 32)
    {
        fprintf(file, "%c%c%c", instruction+1, getModRM(0b00, left_register_value, 0b100), getModRM(mod, right_right_register_value, right_left_register_value));
    }
    else if (left_register_size == 64)
    {
        fprintf(file, "%c%c%c%c", 0x48, instruction+1, getModRM(0b00, left_register_value, 0b100), getModRM(mod, right_right_register_value, right_left_register_value));
    }
}
// mov r [r+r]
void fileprint_r_indexed_instruction(FILE* file, u_int8_t instruction, int inverse, int left_register_size, int left_register_value, int right_left_register_size, int right_left_register_value, int right_right_register_size, int right_right_register_value)
{
    fileprint_r_scaled_instruction(file, instruction, inverse, left_register_size, left_register_value, right_left_register_size, right_left_register_value, right_right_register_size, right_right_register_value, 1);
}
// mov r [r+r*n+n]
void fileprint_r_complex_instruction(FILE* file, u_int8_t instruction, int inverse, int left_register_size, int left_register_value, int right_left_register_size, int right_left_register_value, int right_right_register_size, int right_right_register_value, int multiple, int offset)
{
    if (inverse)
    {
        instruction-=2;
    }

    if (right_left_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    int mod = 0;
    if (multiple == 1)
    {
        mod = 0b00;
    }
    else if (multiple == 2)
    {
        mod = 0b01;
    }
    else if (multiple == 4)
    {
        mod = 0b10;
    }
    else if (multiple == 8)
    {
        mod = 0b11;
    }

    if (left_register_size == 8)
    {
        fprintf(file, "%c", instruction);
        handleComplexLoadOffset(file, offset, mod, right_left_register_value, right_right_register_value, left_register_value);
    }
    else if (left_register_size == 16)
    {
        fprintf(file, "%c%c", 0x66, instruction+1);
        handleComplexLoadOffset(file, offset, mod, right_left_register_value, right_right_register_value, left_register_value);
    }
    else if (left_register_size == 32)
    {
        fprintf(file, "%c", instruction+1);
        handleComplexLoadOffset(file, offset, mod, right_left_register_value, right_right_register_value, left_register_value);
    }
    else if (left_register_size == 64)
    {
        fprintf(file, "%c%c", 0x48, instruction+1);
        handleComplexLoadOffset(file, offset, mod, right_left_register_value, right_right_register_value, left_register_value);
    }
}





#pragma endregion

#pragma region MUL_Codegen_functions
void fileprint_r_instruction(FILE* file, int instruction, u_int8_t group, int register_size, int register_value)
{
    if (register_size == 8)
    {
        fprintf(file, "%c%c", group-1, getModRM(0b11, instruction, register_value));
    }
    else if (register_size == 16)
    {
        fprintf(file, "%c%c%c", 0x66, group, getModRM(0b11, instruction, register_value));
    }
    else if (register_size == 32)
    {
        fprintf(file, "%c%c", group, getModRM(0b11, instruction, register_value));
    }
    else if (register_size == 64)
    {
        fprintf(file, "%c%c%c", 0x48, group, getModRM(0b11, instruction, register_value));
    }
}
void fileprint_indirect_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int register_size, int register_value)
{
    if (register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    if (size_specifier == 8)
    {
        fprintf(file, "%c%c", group-1, getModRM(0b00, instruction, register_value));
    }
    else if (size_specifier == 16)
    {
        fprintf(file, "%c%c%c", 0x66, group, getModRM(0b00, instruction, register_value));
    }
    else if (size_specifier == 32)
    {
        fprintf(file, "%c%c", group, getModRM(0b00, instruction, register_value));
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c%c%c", 0x48, group, getModRM(0b00, instruction, register_value));
    }
}
// CHANGE THE WAY WE ARE DOING instruction SO IT IS PROPER
void fileprint_offset_instruction(FILE* file, u_int8_t instruction, u_int8_t group, int size_specifier, int register_size, int register_value, int offset)
{

    if (register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    if (size_specifier == 8)
    {
        fprintf(file, "%c", group-1);
        handleLoadOffset(file, offset, instruction, register_value);
    }
    else if (size_specifier == 16)
    {
        fprintf(file, "%c%c", 0x66, group);
        handleLoadOffset(file, offset, instruction, register_value);
    }
    else if (size_specifier == 32)
    {
        fprintf(file, "%c", group);
        handleLoadOffset(file, offset, instruction, register_value);
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c%c", 0x48, group);
        handleLoadOffset(file, offset, instruction, register_value);
    }

}
void fileprint_scaled_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value, int multiple)
{
    if (left_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    int mod = 0;
    if (multiple == 1)
    {
        mod = 0b00;
    }
    else if (multiple == 2)
    {
        mod = 0b01;
    }
    else if (multiple == 4)
    {
        mod = 0b10;
    }
    else if (multiple == 8)
    {
        mod = 0b11;
    }

    if (size_specifier == 8)
    {
        fprintf(file, "%c%c%c", group-1, getModRM(0b00, instruction, 0b100), getModRM(mod, right_register_value, left_register_value));
    }
    else if (size_specifier == 16)
    {
        fprintf(file, "%c%c%c%c", 0x66, group,  getModRM(0b00, instruction, 0b100), getModRM(mod, right_register_value, left_register_value));
    }
    else if (size_specifier == 32)
    {
        fprintf(file, "%c%c%c", group,  getModRM(0b00, instruction, 0b100), getModRM(mod, right_register_value, left_register_value));
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c%c%c%c", 0x48, group,  getModRM(0b00, instruction, 0b100), getModRM(mod, right_register_value, left_register_value));
    }
}
void fileprint_indexed_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value)
{
    fileprint_scaled_instruction(file, instruction, group, size_specifier, left_register_size, left_register_value, right_register_size, right_register_value, 1);
}
void fileprint_complex_instruction(FILE* file, u_int8_t instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value, int multiple, int offset)
{


    if (left_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    int mod = 0;
    if (multiple == 1)
    {
        mod = 0b00;
    }
    else if (multiple == 2)
    {
        mod = 0b01;
    }
    else if (multiple == 4)
    {
        mod = 0b10;
    }
    else if (multiple == 8)
    {
        mod = 0b11;
    }

    if (size_specifier == 8)
    {
        fprintf(file, "%c", group - 1);
        handleComplexLoadOffset(file, offset, mod, left_register_value, right_register_value, instruction);
    }
    else if (size_specifier == 16)
    {
        fprintf(file, "%c%c", 0x66, group);
        handleComplexLoadOffset(file, offset, mod, left_register_value, right_register_value, instruction);
    }
    else if (size_specifier == 32)
    {
        fprintf(file, "%c", group);
        handleComplexLoadOffset(file, offset, mod, left_register_value, right_register_value, instruction);
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c%c", 0x48, group);
        handleComplexLoadOffset(file, offset, mod, left_register_value, right_register_value, instruction);
    }
}
#pragma endregion
#pragma region Pop_Push
void fileprint_pp_r_instruction(FILE* file, int instruction, u_int8_t group, int register_size, int register_value)
{
    if (instruction == 0b110)
    {
        if (register_size == 16)
        {
            fprintf(file, "%c%c", 0x66, 0x50 + register_value);
        }
        else if (register_size == 64)
        {
            fprintf(file, "%c", 0x50 + register_value);
        }
    }
    else
    {
        if (register_size == 16)
        {
            fprintf(file, "%c%c", 0x66, 0x58 + register_value);
        }
        else if (register_size == 64)
        {
            fprintf(file, "%c", 0x58 + register_value);
        }
    }
    
}
void fileprint_pp_indirect_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int register_size, int register_value)
{
    if (register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    if (size_specifier == 16)
    {
        fprintf(file, "%c%c%c", 0x66, group, getModRM(0b00, instruction, register_value));
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c%c", group, getModRM(0b00, instruction, register_value));
    }
}
// CHANGE THE WAY WE ARE DOING instruction SO IT IS PROPER
void fileprint_pp_offset_instruction(FILE* file, u_int8_t instruction, u_int8_t group, int size_specifier, int register_size, int register_value, int offset)
{

    if (register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    if (size_specifier == 16)
    {
        fprintf(file, "%c%c", 0x66, group);
        handleLoadOffset(file, offset, instruction, register_value);
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c", group);
        handleLoadOffset(file, offset, instruction, register_value);
    }
}

void fileprint_pp_scaled_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value, int multiple)
{
    if (left_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    int mod = 0;
    if (multiple == 1)
    {
        mod = 0b00;
    }
    else if (multiple == 2)
    {
        mod = 0b01;
    }
    else if (multiple == 4)
    {
        mod = 0b10;
    }
    else if (multiple == 8)
    {
        mod = 0b11;
    }


    if (size_specifier == 16)
    {
        fprintf(file, "%c%c%c%c", 0x66, group,  getModRM(0b00, instruction, 0b100), getModRM(mod, right_register_value, left_register_value));
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c%c%c", group,  getModRM(0b00, instruction, 0b100), getModRM(mod, right_register_value, left_register_value));
    }
}
void fileprint_pp_indexed_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value)
{
    fileprint_pp_scaled_instruction(file, instruction, group, size_specifier, left_register_size, left_register_value, right_register_size, right_register_value, 1);
}
void fileprint_pp_complex_instruction(FILE* file, u_int8_t instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value, int multiple, int offset)
{
    if (left_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    int mod = 0;
    if (multiple == 1)
    {
        mod = 0b00;
    }
    else if (multiple == 2)
    {
        mod = 0b01;
    }
    else if (multiple == 4)
    {
        mod = 0b10;
    }
    else if (multiple == 8)
    {
        mod = 0b11;
    }

    if (size_specifier == 16)
    {
        fprintf(file, "%c%c", 0x66, group);
        handleComplexLoadOffset(file, offset, mod, left_register_value, right_register_value, instruction);
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c", group);
        handleComplexLoadOffset(file, offset, mod, left_register_value, right_register_value, instruction);
    }
}
#pragma endregion




struct Labels* labels;


#define COMPILER HASM
#define NODE Root
iteration(semantics)
{
    labels = createLabels();
    continue_it();
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Statement
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE NOP_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fprintf(file, "%c", 0x90);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE RET_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fprintf(file, "%c", 0xC3);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Plus_Minus
iteration(semantics)
{
    continue_it();
    switch (var_0->var_index)
    {
        case 1:
            var_0->val = 1;
        break;
        case 2:
            var_0->val = -1;
        break;
    }
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Label
iteration(semantics)
{
    continue_it();
    var_0->value = var_0->var_1->token->value;
}
iteration(codegen)
{
    var_0->ptr = GetFileSize(file);
    struct Label label;
    label.label = var_0->value;
    label.ptr = var_0->ptr;
    addLabel(labels, label);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Register64
iteration(semantics)
{
    continue_it();
    var_0->reg_value = var_0->var_index-1;
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Register32
iteration(semantics)
{
    continue_it();
    var_0->reg_value = var_0->var_index-1;
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Register16
iteration(semantics)
{
    continue_it();
    var_0->reg_value = var_0->var_index-1;
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Register8
iteration(semantics)
{
    continue_it();
    var_0->reg_value = var_0->var_index-1;
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Register
iteration(semantics)
{
    continue_it();
    switch(var_0->var_index)
    {
        case 1:
            var_0->reg_size = 8;
            var_0->reg_value = var_0->var.var_1->reg_value;
        break;
        case 2:
            var_0->reg_size = 16;
            var_0->reg_value = var_0->var.var_2->reg_value;
        break;
        case 3:
            var_0->reg_size = 32;
            var_0->reg_value = var_0->var.var_3->reg_value;
        break;
        case 4:
            var_0->reg_size = 64;
            var_0->reg_value = var_0->var.var_4->reg_value;
        break;
    }
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Multi_Purpose_instruction
iteration(semantics)
{
    continue_it();
    switch(var_0->var_index)
    {
        case 1:
        var_0->r = 0x8A;
        var_0->imm = 0xB0;
        break;
        case 2:
        var_0->r = 0x02;
        var_0->imm = 0xC0;
        break;
        case 3:
        var_0->r = 0x2A;
        var_0->imm = 0xE8;
        break;
        case 4:
        var_0->r = 0x0A;
        var_0->imm = 0xC8;
        break;
        case 5:
        var_0->r = 0x22;
        var_0->imm = 0xE0;
        break;
        case 6:
        var_0->r = 0x3A;
        var_0->imm = 0xF8;
        break;
        case 7:
        var_0->r = 0x12;
        var_0->imm = 0xD0;
        break;
        case 8:
        var_0->r = 0x1A;
        var_0->imm = 0xD8;
        break;
        case 9:
        var_0->r = 0x32;
        var_0->imm = 0xF0;
        break;
        case 10:
        var_0->r = 0x86;
        var_0->imm = 0xC0;
        break;
    }
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Bitwise_instruction
iteration(semantics)
{
    var_0->group = 0xF7;
    continue_it();
    switch (var_0->var_index)
    {
        case 1:
        var_0->instruction = 0b000;
        break;
        case 2:
        var_0->instruction = 0b001;
        break;
        case 3:
        var_0->instruction = 0b010;
        break;
        case 4:
        var_0->instruction = 0b011;
        break;
        case 5:
        var_0->instruction = 0b100;
        break;
        case 6:
        var_0->instruction = 0b100;
        break;
        case 7:
        var_0->instruction = 0b101;
        break;
        case 8:
        var_0->instruction = 0b111;
        break;
    }
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Miscellaneous_Arithmetic_instruction
iteration(semantics)
{
    var_0->group = 0xF7;
    continue_it();
    switch (var_0->var_index)
    {
        case 1:
        var_0->instruction = 0b100;
        break;
        case 2:
        var_0->instruction = 0b101;
        break;
        case 3:
        var_0->instruction = 0b110;
        break;
        case 4:
        var_0->instruction = 0b111;
        break;
        case 5:
        var_0->instruction = 0b010;
        break;
        case 6:
        var_0->instruction = 0b011;
        break;
    }
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Inc_Dec_instruction
iteration(semantics)
{
    var_0->group = 0xFF;
    continue_it();
    switch (var_0->var_index)
    {
        case 1:
        var_0->instruction = 0b000;
        break;
        case 2:
        var_0->instruction = 0b001;
        break;
    }
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Push_Pop_instruction
iteration(semantics)
{
    continue_it();
    switch (var_0->var_index)
    {
        case 1:
        var_0->instruction = 0b110;
        var_0->group = 0xFF;
        break;
        case 2:
        var_0->instruction = 0b000;
        var_0->group = 0x8F;
        break;
    }
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE unary_instruction
iteration(semantics)
{
    continue_it();
    switch (var_0->var_index)
    {
        case 1:
        var_0->instruction = var_0->var.var_1->instruction;
        var_0->group = var_0->var.var_1->group;
        break;
        case 2:
        var_0->instruction = var_0->var.var_2->instruction;
        var_0->group = var_0->var.var_2->group;
        break;
    }
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE Size_Specifier
iteration(semantics)
{
    continue_it();
    switch (var_0->var_index)
    {
        case 1:
        var_0->size = 8;
        break;
        case 2:
        var_0->size = 16;
        break;
        case 3:
        var_0->size = 32;
        break;
        case 4:
        var_0->size = 64;
        break;
    }
}
iteration(codegen)
{
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_r_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_r_instruction(file, var_0->var_1->r, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_3->reg_size, var_0->var_3->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_imm_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_imm_instruction(file, var_0->var_1->imm, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_3->token->value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_direct_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_direct_instruction(file, var_0->var_1->r, 0, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_4->token->value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_indirect_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_indirect_instruction(file, var_0->var_1->r, 0, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_4->reg_size, var_0->var_4->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_offset_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_offset_instruction(file, var_0->var_1->r, 0, atoi(var_0->var_6->token->value) * var_0->var_5->val, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_4->reg_size, var_0->var_4->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_indexed_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_indexed_instruction(file, var_0->var_1->r, 0, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_scaled_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_scaled_instruction(file, var_0->var_1->r, 0, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value));
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_complex_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_complex_instruction(file, var_0->var_1->r, 0, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value), atoi(var_0->var_10->token->value) * var_0->var_9->val);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_direct_r_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_direct_instruction(file, var_0->var_1->r, 1, var_0->var_5->reg_size, var_0->var_5->reg_value, var_0->var_3->token->value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_indirect_r_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_indirect_instruction(file, var_0->var_1->r, 1, var_0->var_5->reg_size, var_0->var_5->reg_value, var_0->var_3->reg_size, var_0->var_3->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_offset_r_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_offset_instruction(file, var_0->var_1->r, 1, atoi(var_0->var_5->token->value) * var_0->var_4->val, var_0->var_7->reg_size, var_0->var_7->reg_value, var_0->var_3->reg_size, var_0->var_3->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_indexed_r_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_indexed_instruction(file, var_0->var_1->r, 1, var_0->var_7->reg_size, var_0->var_7->reg_value, var_0->var_3->reg_size, var_0->var_3->reg_value, var_0->var_5->reg_size, var_0->var_5->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_scaled_r_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_scaled_instruction(file, var_0->var_1->r, 1, var_0->var_9->reg_size, var_0->var_9->reg_value, var_0->var_3->reg_size, var_0->var_3->reg_value, var_0->var_5->reg_size, var_0->var_5->reg_value, atoi(var_0->var_7->token->value));
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE MOV_complex_r_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_complex_instruction(file, var_0->var_1->r, 1, var_0->var_11->reg_size, var_0->var_11->reg_value, var_0->var_3->reg_size, var_0->var_3->reg_value, var_0->var_5->reg_size, var_0->var_5->reg_value, atoi(var_0->var_7->token->value), atoi(var_0->var_9->token->value) * var_0->var_8->val);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE r_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->reg_size, var_0->var_2->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE indirect_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_indirect_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE index_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_indexed_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE scaled_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_scaled_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value));
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE complex_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_complex_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value), atoi(var_0->var_10->token->value)*var_0->var_9->val);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE offset_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_offset_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, atoi(var_0->var_6->token->value)*var_0->var_5->val);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE pp_r_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_pp_r_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->reg_size, var_0->var_2->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE pp_indirect_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_pp_indirect_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE pp_index_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_pp_indexed_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE pp_scaled_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_pp_scaled_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value));
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE pp_complex_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_pp_complex_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value), atoi(var_0->var_10->token->value)*var_0->var_9->val);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE pp_offset_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_pp_offset_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, atoi(var_0->var_6->token->value)*var_0->var_5->val);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE bitwise_hex_r_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_instruction(file, var_0->var_1->instruction, 0xC1, var_0->var_2->reg_size, var_0->var_2->reg_value);
    hexStringToByteArray(file, var_0->var_3->token->value, 1);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE bitwise_hex_indirect_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_indirect_instruction(file, var_0->var_1->instruction, 0xC1, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value);
    hexStringToByteArray(file, var_0->var_6->token->value, 1);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE bitwise_hex_index_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_indexed_instruction(file, var_0->var_1->instruction, 0xC1, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value);
    hexStringToByteArray(file, var_0->var_8->token->value, 1);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE bitwise_hex_scaled_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_scaled_instruction(file, var_0->var_1->instruction, 0xC1, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value));
    hexStringToByteArray(file, var_0->var_10->token->value, 1);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE bitwise_hex_complex_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_complex_instruction(file, var_0->var_1->instruction, 0xC1, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value), atoi(var_0->var_10->token->value)*var_0->var_9->val);
    hexStringToByteArray(file, var_0->var_12->token->value, 1);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE bitwise_hex_offset_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_offset_instruction(file, var_0->var_1->instruction, 0xC1, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, atoi(var_0->var_6->token->value)*var_0->var_5->val);
    hexStringToByteArray(file, var_0->var_8->token->value, 1);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE bitwise_cl_r_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_r_instruction(file, var_0->var_1->instruction, 0xD3, var_0->var_2->reg_size, var_0->var_2->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE bitwise_cl_indirect_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_indirect_instruction(file, var_0->var_1->instruction, 0xD3, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE bitwise_cl_index_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_indexed_instruction(file, var_0->var_1->instruction, 0xD3, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE bitwise_cl_scaled_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_scaled_instruction(file, var_0->var_1->instruction, 0xD3, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value));
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE bitwise_cl_complex_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_complex_instruction(file, var_0->var_1->instruction, 0xD3, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value), atoi(var_0->var_10->token->value)*var_0->var_9->val);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}
#define NODE bitwise_cl_offset_instruction
iteration(semantics)
{
    continue_it();
}
iteration(codegen)
{
    fileprint_offset_instruction(file, var_0->var_1->instruction, 0xD3, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, atoi(var_0->var_6->token->value)*var_0->var_5->val);
    continue_it();
}
iteration(label_resolution)
{
     continue_it();
}