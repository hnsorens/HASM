#include "HASMRules.h"

char* long_to_hex_string(int value) {
    // Calculate the size of the string needed: 2 hex digits per byte + "0x" + null terminator
    size_t byte_count = sizeof(int);
    size_t string_size = 2 * byte_count + 3; // "0x" + 2 digits per byte + null terminator

    // Allocate memory for the string
    char* hex_string = (char*)malloc(string_size);
    if (hex_string == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }

    // Build the hexadecimal string
    snprintf(hex_string, string_size, "0x");
    for (size_t i = 0; i < byte_count; ++i) {
        snprintf(hex_string + 2 + i * 2, 3, "%02X", (unsigned char)((value >> (8 * (byte_count - 1 - i))) & 0xFF));
    }

    return hex_string;
}

long hex_to_long(const char* hex_str) {
    if (hex_str == NULL) {
        printf("an error has occured!");
        exit(1);
    }

    char* endptr;
    long result = strtol(hex_str, &endptr, 16);

    return result;
}

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
    printf("Didnt find label %s. \n", label);
    return -1;
}


int replace_bytes(FILE *file, int offset, int size, long value) {
    if (size <= 0 || size > sizeof(long)) {
        fprintf(stderr, "Error: Invalid size. Must be between 1 and %lu.\n", sizeof(long));
        return -1;
    }

    uint8_t buffer[sizeof(long)] = {0};
    memcpy(buffer, &value, size);

    if (fseek(file, offset, SEEK_SET) != 0) {
        printf("There was some error!");
        exit(1);
    }

    if (fwrite(buffer, 1, size, file) != (size_t)size) {
        printf("There was some error!");
        exit(1);
    }

    if (fflush(file) != 0) {
       printf("There was some error!");
        exit(1);
    }

    return 0;
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
    
    if (instruction == 0x00)
    {
        if (left_register_size == 8)
        {
            fprintf(file, "%c%c", 0xF6, 0xC0 + left_register_value);
            hexStringToByteArray(file, imm, 1);
        }
        else if (left_register_size == 16)
        {
            fprintf(file, "%c%c%c", 0x66, 0xF7, 0xC0 + left_register_value);
            hexStringToByteArray(file, imm, 2);
        }
        else if (left_register_size == 32)
        {
            fprintf(file, "%c%c", 0xF7, 0xC0 + left_register_value);
            hexStringToByteArray(file, imm, 4);
        }
        else if (left_register_size == 64)
        {
            fprintf(file, "%c%c%c", 0x48, 0xF7, 0xC0 + left_register_value);
            hexStringToByteArray(file, imm, 4);
        }
    }
    else if (instruction == 0xb0)
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
    if (inverse || instruction == 0x88 || instruction == 0x86)
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
    if (inverse || instruction == 0x88 || instruction == 0x86)
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
    if (inverse || instruction == 0x88 || instruction == 0x86)
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
    if (inverse || instruction == 0x88 || instruction == 0x86)
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
    if (inverse || instruction == 0x88 || instruction == 0x86)
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





void fileprint_jmp_r_instruction(FILE* file, int instruction, u_int8_t group, int register_size, int register_value)
{
    if (register_size == 16)
    {
        fprintf(file, "%c", 0x66);
    }
    fprintf(file, "%c", 0xFF);
    fprintf(file, "%c", 0xE0 + register_value);
}
void fileprint_jmp_indirect_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int register_size, int register_value)
{
    fileprint_jmp_offset_instruction(file, instruction, group, size_specifier, register_size, register_value, 0);
}
// CHANGE THE WAY WE ARE DOING instruction SO IT IS PROPER
void fileprint_jmp_offset_instruction(FILE* file, u_int8_t instruction, u_int8_t group, int size_specifier, int register_size, int register_value, int offset)
{
    int size_offset = size_specifier / 8;

    if (register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    fprintf(file, "%c", 0xFF);
    handleLoadOffset(file, offset + size_offset, instruction, register_value);
}
void fileprint_jmp_scaled_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value, int multiple)
{
    fileprint_jmp_complex_instruction(file, instruction, group, size_specifier, left_register_size, left_register_value, right_register_size, right_register_value, multiple, 0);
}
void fileprint_jmp_indexed_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value)
{
    fileprint_jmp_scaled_instruction(file, instruction, group, size_specifier, left_register_size, left_register_value, right_register_size, right_register_value, 1);
}
void fileprint_jmp_complex_instruction(FILE* file, u_int8_t instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value, int multiple, int offset)
{
    int size_offset = size_specifier / 8;

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

    fprintf(file, "%c", 0xFF);
    handleComplexLoadOffset(file, offset + size_offset, mod, left_register_value, right_register_value, instruction);
}


struct Labels* labels;

#define COMPILER HASM
#define NODE Root
recurse(semantics)
{
    labels = createLabels();
    continue_it();
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Global
recurse(semantics)
{
    beggining_label = var_0->var_2->token->value;
    var_0->ehdr = (Elf64_Ehdr) {
        .e_ident = {
            ELFMAG0,
            ELFMAG1,
            ELFMAG2,
            ELFMAG3,
            ELFCLASS64,
            ELFDATA2LSB,
            EV_CURRENT,
            ELFOSABI_SYSV,
            0, 0, 0, 0, 0, 0, 0
        },
        .e_type = ET_EXEC,
        .e_machine = EM_X86_64,
        .e_entry = 0, // filled in later
        .e_phoff = 64,
        .e_shoff = 0,
        .e_flags = 0,
        .e_ehsize = 64,
        .e_phentsize = 56,
        .e_phnum = 1,
        .e_shentsize = 0,
        .e_shnum = 0,
        .e_shstrndx = SHN_UNDEF
    };
    fwrite(&var_0->ehdr, 1, sizeof(var_0->ehdr), file);

    
    var_0->phdr = (Elf64_Phdr) {
        .p_type = PT_LOAD,
        .p_offset = 0x78, // 64 + 56
        .p_vaddr = 0x400078,
        .p_paddr = 0x400078,
        .p_filesz = 0, // filled in later
        .p_memsz = 0, // filled in later
        .p_flags = PF_X | PF_R,
        .p_align = 0x8
    };
    fwrite(&var_0->phdr, 1, sizeof(var_0->phdr), file);

    continue_it();
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
    replace_bytes(file, 0x18, 4, 0x400000 + beggining_offset);
    replace_bytes(file, 0x60, 4, GetFileSize(file) - 0x78);
    replace_bytes(file, 0x68, 4, GetFileSize(file) - 0x78);
     continue_it();
}
#define NODE Section_Text_Statement
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}
#define NODE Statement
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Section_Data_Statement
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Section_Text
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Section_Data
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Plus_Minus
recurse(semantics)
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
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Label
recurse(semantics)
{
    continue_it();
    var_0->value = var_0->var_1->token->value;
}
recurse(codegen)
{
    var_0->ptr = GetFileSize(file);
    struct Label label;
    label.label = var_0->value;
    label.ptr = var_0->ptr;
    addLabel(labels, label);
    if (strcmp(var_0->value, beggining_label) == 0)
    {
        beggining_offset = var_0->ptr;
    }
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Register64
recurse(semantics)
{
    continue_it();
    var_0->reg_value = var_0->var_index-1;
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Register32
recurse(semantics)
{
    continue_it();
    var_0->reg_value = var_0->var_index-1;
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Register16
recurse(semantics)
{
    continue_it();
    var_0->reg_value = var_0->var_index-1;
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Register8
recurse(semantics)
{
    continue_it();
    var_0->reg_value = var_0->var_index-1;
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Register
recurse(semantics)
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
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Multi_Purpose_instruction_no_xchg
recurse(semantics)
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
        var_0->imm = 0x00;
        break;
    }
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Multi_Purpose_instruction
recurse(semantics)
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
        var_0->r = 0x88;
        var_0->imm = 0xC0;
        break;
        case 11:
        var_0->r = 0x86;
        var_0->imm = 0xC0;
        break;
    }
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Multi_Purpose_instruction_w_lea
recurse(semantics)
{
    continue_it();
    switch(var_0->var_index)
    {
        case 1:
        var_0->r = var_0->var.var_1->r;
        var_0->imm = var_0->var.var_1->imm;
        break;
        case 2:
        var_0->r = 0x8C;
        var_0->imm = 0xD0;
        break;
        
    }
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Jump_instruction
recurse(semantics)
{
    continue_it();
    var_0->instruction = var_0->var_index-1;
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}
#define NODE Miscellaneous_Arithmetic_instruction
recurse(semantics)
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
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Inc_Dec_instruction
recurse(semantics)
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
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Push_Pop_instruction
recurse(semantics)
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
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE unary_instruction
recurse(semantics)
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
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Size_Specifier
recurse(semantics)
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
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_r_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_r_instruction(file, var_0->var_1->r, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_3->reg_size, var_0->var_3->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE Hex_Identifier
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}
#define NODE MOV_r_imm_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    long value;
    if (var_0->var_3->var_index == 1)
    {
        value = findLabel(labels, var_0->var_3->var.var_1->token->value);
        value += 0x400000;
        fileprint_r_imm_instruction(file, var_0->var_1->imm, var_0->var_2->reg_size, var_0->var_2->reg_value, long_to_hex_string(value));
    }
    if (var_0->var_3->var_index == 2)
    {
        fileprint_r_imm_instruction(file, var_0->var_1->imm, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_3->var.var_2->token->value);
    }
    
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_direct_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_direct_instruction(file, var_0->var_1->r, 0, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_4->token->value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_indirect_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_indirect_instruction(file, var_0->var_1->r, 0, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_4->reg_size, var_0->var_4->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_offset_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_offset_instruction(file, var_0->var_1->r, 0, atoi(var_0->var_6->token->value) * var_0->var_5->val, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_4->reg_size, var_0->var_4->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_indexed_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_indexed_instruction(file, var_0->var_1->r, 0, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_scaled_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_scaled_instruction(file, var_0->var_1->r, 0, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value));
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE MOV_r_complex_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_complex_instruction(file, var_0->var_1->r, 0, var_0->var_2->reg_size, var_0->var_2->reg_value, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value), atoi(var_0->var_10->token->value) * var_0->var_9->val);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE MOV_direct_r_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_direct_instruction(file, var_0->var_1->r, 1, var_0->var_5->reg_size, var_0->var_5->reg_value, var_0->var_3->token->value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE MOV_indirect_r_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_indirect_instruction(file, var_0->var_1->r, 1, var_0->var_5->reg_size, var_0->var_5->reg_value, var_0->var_3->reg_size, var_0->var_3->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE MOV_offset_r_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_offset_instruction(file, var_0->var_1->r, 1, atoi(var_0->var_5->token->value) * var_0->var_4->val, var_0->var_7->reg_size, var_0->var_7->reg_value, var_0->var_3->reg_size, var_0->var_3->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE MOV_indexed_r_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_indexed_instruction(file, var_0->var_1->r, 1, var_0->var_7->reg_size, var_0->var_7->reg_value, var_0->var_3->reg_size, var_0->var_3->reg_value, var_0->var_5->reg_size, var_0->var_5->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE MOV_scaled_r_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_scaled_instruction(file, var_0->var_1->r, 1, var_0->var_9->reg_size, var_0->var_9->reg_value, var_0->var_3->reg_size, var_0->var_3->reg_value, var_0->var_5->reg_size, var_0->var_5->reg_value, atoi(var_0->var_7->token->value));
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE MOV_complex_r_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_complex_instruction(file, var_0->var_1->r, 1, var_0->var_11->reg_size, var_0->var_11->reg_value, var_0->var_3->reg_size, var_0->var_3->reg_value, var_0->var_5->reg_size, var_0->var_5->reg_value, atoi(var_0->var_7->token->value), atoi(var_0->var_9->token->value) * var_0->var_8->val);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE r_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_r_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->reg_size, var_0->var_2->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE indirect_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_indirect_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE index_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_indexed_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE scaled_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_scaled_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value));
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE complex_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_complex_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value), atoi(var_0->var_10->token->value)*var_0->var_9->val);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE offset_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_offset_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, atoi(var_0->var_6->token->value)*var_0->var_5->val);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE pp_r_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_pp_r_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->reg_size, var_0->var_2->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE pp_indirect_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_pp_indirect_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE pp_index_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_pp_indexed_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE pp_scaled_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_pp_scaled_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value));
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE pp_complex_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_pp_complex_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value), atoi(var_0->var_10->token->value)*var_0->var_9->val);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE pp_offset_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_pp_offset_instruction(file, var_0->var_1->instruction, var_0->var_1->group, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, atoi(var_0->var_6->token->value)*var_0->var_5->val);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}

#define NODE jump_label
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    var_0->ptr = GetFileSize(file);
    fprintf(file, "%c%c%c%c%c%c", 0x0F, 0x80 + var_0->var_1->instruction,0,0,0,0);
    continue_it();
}
recurse(label_resolution)
{
    int position = findLabel(labels, var_0->var_2->token->value);
    if (position != -1)
    {
        int offset = position - var_0->ptr-6;

        replace_bytes(file, var_0->ptr+2, 1, offset & 0xFF);
        replace_bytes(file, var_0->ptr+3, 1, (offset >> 8) & 0xFF);
        replace_bytes(file, var_0->ptr+4, 1, (offset >> 16) & 0xFF);
        replace_bytes(file, var_0->ptr+5, 1, (offset >> 24) & 0xFF);
    }
    else
    {
        printf("ERROR: Label does not exist\n");
    }
    continue_it();
}
#define NODE syscall_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fprintf(file, "%c%c", 0x0F, 0x05);
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}
#define NODE Directive
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}
#define NODE Variable
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    struct Label label;
    label.label = var_0->var_1->token->value;
    label.ptr = GetFileSize(file);
    addLabel(labels, label);
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}
#define NODE Variable_Value
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}
#define NODE Variable_Value_DB
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    switch (var_0->var_index)
    {
        case 1:
            char* string = var_0->var.var_1->token->value;
            for (int i = 1; i < strlen(string)-1; i++)
            {
                fprintf(file, "%c", string[i]);
            }
        break;
        case 2:
            fprintf(file, "%c", var_0->var.var_2->token->value[1]);
        break;
        case 3:
            int filesize = GetFileSize(file);
            fprintf(file, "0");
            replace_bytes(file, filesize, 1, atoi(var_0->var.var_3->token->value));
        break;
        case 4:
            hexStringToByteArray(file, var_0->var.var_4->token->value, 1);
        break;
    }
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}
#define NODE Variable_Value_DW
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    switch (var_0->var_index)
    {
        case 1:
            char* string = var_0->var.var_1->token->value;
            for (int i = 1; i < strlen(string)-1; i++)
            {
                fprintf(file, "%c", string[i]);
                fprintf(file, "\0");
            }
        break;
        case 2:
            fprintf(file, "%c", var_0->var.var_2->token->value[1]);
            fprintf(file, "\0");
        break;
        case 3:
            int filesize = GetFileSize(file);
            fprintf(file, "\0\0");
            replace_bytes(file, filesize, 2, atoi(var_0->var.var_3->token->value));
        break;
        case 4:
            hexStringToByteArray(file, var_0->var.var_4->token->value, 2);
        break;
    }
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}
#define NODE Variable_Value_DD
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    switch (var_0->var_index)
    {
        case 1:
            char* string = var_0->var.var_1->token->value;
            for (int i = 1; i < strlen(string)-1; i++)
            {
                fprintf(file, "%c", string[i]);
                fprintf(file, "\0\0\0");
            }
        break;
        case 2:
            fprintf(file, "%c", var_0->var.var_2->token->value[1]);
            fprintf(file, "\0\0\0");
        break;
        case 3:
            int filesize = GetFileSize(file);
            fprintf(file, "\0\0\0\0");
            replace_bytes(file, filesize, 4, atoi(var_0->var.var_3->token->value));
        break;
        case 4:
            hexStringToByteArray(file, var_0->var.var_4->token->value, 4);
        break;
    }
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}
#define NODE Variable_Value_DQ
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    switch (var_0->var_index)
    {
        case 1:
            char* string = var_0->var.var_1->token->value;
            for (int i = 1; i < strlen(string)-1; i++)
            {
                fprintf(file, "%c", string[i]);
                fprintf(file, "\0\0\0\0\0\0\0");
            }
        break;
        case 2:
            fprintf(file, "%c", var_0->var.var_2->token->value[1]);
            fprintf(file, "\0\0\0\0\0\0\0");
        break;
        case 3:
            int filesize = GetFileSize(file);
            fprintf(file, "\0\0\0\0\0\0\0\0");
            replace_bytes(file, filesize, 8, atoi(var_0->var.var_3->token->value));
        break;
        case 4:
            hexStringToByteArray(file, var_0->var.var_4->token->value, 8);
        break;
    }
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}

#define NODE NOP_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fprintf(file, "%c", 0x90);
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}
#define NODE INT_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fprintf(file, "%c", 0xCD);
    hexStringToByteArray(file, var_0->var_2->token->value, 1);
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}

#define NODE WAIT_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fprintf(file, "%c", 0x9B);
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}

#define NODE jmp_r_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_jmp_r_instruction(file, 4, 0, var_0->var_2->reg_size, var_0->var_2->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE jmp_indirect_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_jmp_indirect_instruction(file, 4, 0, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE jmp_index_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_jmp_indexed_instruction(file, 4, 0, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE jmp_scaled_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_jmp_scaled_instruction(file, 4, 0, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value));
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE jmp_complex_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_jmp_complex_instruction(file, 4, 0, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, var_0->var_6->reg_size, var_0->var_6->reg_value, atoi(var_0->var_8->token->value), atoi(var_0->var_10->token->value)*var_0->var_9->val);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE jmp_offset_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fileprint_jmp_offset_instruction(file, 4, 0, var_0->var_2->size, var_0->var_4->reg_size, var_0->var_4->reg_value, atoi(var_0->var_6->token->value)*var_0->var_5->val);
    continue_it();
}
recurse(label_resolution)
{
     continue_it();
}
#define NODE jmp_label
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    var_0->ptr = GetFileSize(file);
    fprintf(file, "%c%c%c%c%c", 0xE9,0,0,0,0);
    continue_it();
}
recurse(label_resolution)
{
    int position = findLabel(labels, var_0->var_2->token->value);
    if (position != -1)
    {
        int offset = position - var_0->ptr - 5;

        replace_bytes(file, var_0->ptr+1, 1, offset & 0xFF);
        replace_bytes(file, var_0->ptr+2, 1, (offset >> 8) & 0xFF);
        replace_bytes(file, var_0->ptr+3, 1, (offset >> 16) & 0xFF);
        replace_bytes(file, var_0->ptr+4, 1, (offset >> 24) & 0xFF);
    }
    else
    {
        printf("ERROR: Label does not exist\n");
    }
    continue_it();
}
#define NODE call_label
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    var_0->ptr = GetFileSize(file);
    fprintf(file, "%c%c%c%c%c", 0xE8,0,0,0,0);
    continue_it();
}
recurse(label_resolution)
{
    int position = findLabel(labels, var_0->var_2->token->value);
    if (position != -1)
    {
        int offset = position - var_0->ptr - 5;

        replace_bytes(file, var_0->ptr+1, 1, offset & 0xFF);
        replace_bytes(file, var_0->ptr+2, 1, (offset >> 8) & 0xFF);
        replace_bytes(file, var_0->ptr+3, 1, (offset >> 16) & 0xFF);
        replace_bytes(file, var_0->ptr+4, 1, (offset >> 24) & 0xFF);
    }
    else
    {
        printf("ERROR: Label does not exist\n");
    }
    continue_it();
}
#define NODE RET_instruction
recurse(semantics)
{
    continue_it();
}
recurse(codegen)
{
    fprintf(file, "%c", 0xC3);
    continue_it();
}
recurse(label_resolution)
{
    continue_it();
}