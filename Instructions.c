/*
 * HASM - x86 Assembly Compiler
 * Instruction Parsing and Encoding Implementation
 * 
 * This file contains the implementation of all instruction parsing and encoding functions.
 * It handles operand parsing, register lookup, instruction encoding, and utility functions
 * for number conversion and byte manipulation.
 */

#include "Instructions.h"
#include "assembler.h"

/* ==================== REGISTER MAP ==================== */

/* Static register lookup table - maps register names to register structures */
static Register register_map[26*26*26]; // Register lookup table

/* ==================== DEBUGGING UTILITIES ==================== */

/**
 * Print a line from the source file at a specific position
 * Used for error reporting to show the problematic line
 * @param file Source file to read from
 * @param target_pos Position in file to find the line for
 */
void print_line_at_pos(FILE *file, long target_pos) {
    if (fseek(file, 0, SEEK_SET) != 0) {
        perror("fseek failed");
        return;
    }

    long line_start = 0;
    long current_pos = 0;
    int c;

    /* Find the start of the line (backtrack to previous '\n' or file start) */
    while (current_pos < target_pos) {
        c = fgetc(file);
        if (c == EOF) break;
        if (c == '\n') {
            line_start = current_pos + 1;  /* Next char after '\n' */
        }
        current_pos++;
    }

    /* Rewind to the line start */
    if (fseek(file, line_start, SEEK_SET) != 0) {
        perror("fseek failed");
        return;
    }

    /* Print the line until '\n' or EOF */
    while ((c = fgetc(file)) != EOF && c != '\n') {
        putchar(c);
    }
    printf("\n");
}

/* ==================== INSTRUCTION ENCODING UTILITIES ==================== */

/**
 * Generate ModR/M byte for x86 instruction encoding
 * @param mod Mod field (0-3) - addressing mode
 * @param reg Register field (0-7) - register number
 * @param rm R/M field (0-7) - register/memory operand
 * @return Combined ModR/M byte
 */
unsigned char get_mod_rm(unsigned char mod, unsigned char reg, unsigned char rm) {
    unsigned char modRM = (mod << 6) | (reg << 3) | rm;
    return modRM;
}

/**
 * Write a value in little-endian byte order to the output file
 * @param value Value to write
 * @param byte_count Number of bytes to write (max 8)
 */
void write_little_endian_bytes(__uint64_t value, size_t byte_count) {
    if (byte_count > 8) byte_count = 8;  /* Limit to 8 bytes */

    for (size_t i = 0; i < byte_count; ++i) {
        unsigned char byte = (value >> (8 * i)) & 0xFF;  /* Extract byte i */
        fprintf(file_out, "%c", byte);
    }
}

/**
 * Print a signed integer as ASCII representation
 * Used for writing immediate values to output file
 * @param n_bytes Number of bytes to write
 * @param num Integer value to convert
 */
void print_signed_integer_as_ascii(int n_bytes, __int64_t num) {
    /* Pointer to the raw bytes of the integer */
    unsigned char* byte_ptr = (unsigned char*)&num;
    
    /* Print the bytes as ASCII characters */
    for (int i = 0; i < n_bytes; ++i) {
        fprintf(file_out, "%c", byte_ptr[i]);
    }
}

/**
 * Convert an integer to little-endian bytes in a buffer
 * @param value Integer value to convert
 * @param buffer Output buffer for bytes
 * @param numBytes Number of bytes to write
 */
void intToBytes(unsigned long value, char *buffer, size_t numBytes) {
    if (numBytes > sizeof(unsigned long)) {
        fprintf(stderr, "Error: numBytes exceeds size of unsigned long.\n");
        return;
    }

    /* Copy each byte, little-endian order */
    for (size_t i = 0; i < numBytes; ++i) {
        buffer[i] = (value >> (8 * i)) & 0xFF;
    }
}

/**
 * Convert a string representation of a number to decimal
 * Handles hex (0x), binary (0b), and decimal numbers
 * @param input String to convert (modified in place)
 */
void convertToDecimalInPlace(char *input) {
    int base = 10;
    char *numberStr = input;

    /* Detect base from prefix */
    if (strncmp(input, "0x", 2) == 0 || strncmp(input, "0X", 2) == 0) {
        base = 16;  /* Hexadecimal */
        numberStr = input + 2;
    } else if (strncmp(input, "0b", 2) == 0 || strncmp(input, "0B", 2) == 0) {
        base = 2;   /* Binary */
        numberStr = input + 2;
    }

    /* Convert to integer */
    char *end;
    long value = strtol(numberStr, &end, base);
    if (*end != '\0') {
        fprintf(stderr, "Invalid number format: %s\n", input);
        input[0] = '\0'; /* Empty the input string */
        return;
    }

    /* Overwrite the input with decimal string */
    snprintf(input, 32, "%ld", value); /* Ensure input has enough space */
}



/**
 * Initialize the register lookup map
 * Sets up mappings from register names to register numbers and sizes
 * Uses a hash function based on the first 3 characters of register names
 */
void init_register_map()
{
    memset(register_map, -1, sizeof(register_map));  /* Initialize all entries to invalid */

    char* opcode_str = "";
    /* Macro to add a register to the map */
    #define ADD_REG(opcode, size, reg) \
        opcode_str = #opcode; \
        register_map[abs(((opcode_str[0] - 'A') % 26) + ((opcode_str[1] - 'A') % 26) * 26 + ((opcode_str[2] - 'A') % 26) * 26 * 26)] = (Register){size, reg};

    /* 64-bit registers (R-prefix) */
    ADD_REG(RAX, 64, 0)
    ADD_REG(RCX, 64, 1)
    ADD_REG(RDX, 64, 2)
    ADD_REG(RBX, 64, 3)
    ADD_REG(RSP, 64, 4)
    ADD_REG(RBP, 64, 5)
    ADD_REG(RSI, 64, 6)
    ADD_REG(RDI, 64, 7)
    ADD_REG(R8, 64, 8)
    ADD_REG(R9, 64, 9)
    ADD_REG(R10, 64, 10)
    ADD_REG(R11, 64, 11)
    ADD_REG(R12, 64, 12)
    ADD_REG(R13, 64, 13)
    ADD_REG(R14, 64, 14)
    ADD_REG(R15, 64, 15)

    /* 32-bit registers (E-prefix) */
    ADD_REG(EAX, 32, 0)
    ADD_REG(ECX, 32, 1)
    ADD_REG(EDX, 32, 2)
    ADD_REG(EBX, 32, 3)
    ADD_REG(ESP, 32, 4)
    ADD_REG(EBP, 32, 5)
    ADD_REG(ESI, 32, 6)
    ADD_REG(EDI, 32, 7)

    /* 16-bit registers (no prefix) */
    ADD_REG(AX, 16, 0)
    ADD_REG(CX, 16, 1)
    ADD_REG(DX, 16, 2)
    ADD_REG(BX, 16, 3)
    ADD_REG(SP, 16, 4)
    ADD_REG(BP, 16, 5)
    ADD_REG(SI, 16, 6)
    ADD_REG(DI, 16, 7)

    /* 8-bit low registers (L-suffix) */
    ADD_REG(AL, 8, 0)
    ADD_REG(CL, 8, 1)
    ADD_REG(DL, 8, 2)
    ADD_REG(BL, 8, 3)
    ADD_REG(AH, 8, 4)
    ADD_REG(CH, 8, 5)
    ADD_REG(DH, 8, 6)
    ADD_REG(BH, 8, 7)

    #undef ADD_REG
}

/**
 * Look up a register by name and return its structure
 * @param reg Register name (e.g., "RAX", "EAX", "AL")
 * @return Register structure with size and register number
 */
Register find_register(const char* reg)
{
    return register_map[abs(((reg[0] - 'A') % 26) + ((reg[1] - 'A') % 26) * 26 + ((reg[2] - 'A') % 26) * 26 * 26)];
}

/**
 * Print an error message with source location information
 * Shows the problematic line and points to the exact position
 * @param token Token that caused the error
 * @param error_message Main error message
 * @param is_note Whether this is a note (additional info)
 * @param note Additional note text
 */
void error(Token* token, char* error_message, int is_note, char* note)
{
    printf("%s:%i:%i: error: %s\n  ", "program.asm", token->line, token->line_pos, error_message);
    print_line_at_pos(file, token->file_pos);
    for (int i = 0; i < token->line_pos+1; i++)
    {
        putchar(' ');
    }
    printf("^\n");
    if (is_note)
    printf("note: %s\n", note);
}

Operand find_next_operand(int allowed_operands)
{
    char note[128] = "Expected one of: ";

    if (allowed_operands & OP_REG)
    {
        strcat(note, "Register, ");
    }
    if (allowed_operands & OP_IMM)
    {
        strcat(note, "Immediate Value, ");
    }
    if (allowed_operands & OP_MEM)
    {
        strcat(note, "Memory, ");
    }
    if (allowed_operands & OP_IDT)
    {
        strcat(note, "Label, ");
    }
    note[strlen(note)-2] = '\0';


    offset++;
    Operand operand;
    Register reg = find_register(TOKEN(offset)->content);
    if (TOKEN(offset)->content[0] == '[' || (offset + 1 < (int)tokens.size && TOKEN(offset+1)->content[0] == '[' && 
        (strcmp(TOKEN(offset)->content, "BYTE") == 0 || 
        strcmp(TOKEN(offset)->content, "WORD") == 0 || 
        strcmp(TOKEN(offset)->content, "DWORD") == 0 || 
        strcmp(TOKEN(offset)->content, "QWORD") == 0)))
    {
        if (!(allowed_operands & OP_MEM))
        {
            error(TOKEN(offset), "Memory Operand Not Allowed!", 1, note);
        }
        if (offset + 1 < (int)tokens.size && TOKEN(offset+1)->content[0] == '[')
        {
            if (strcmp(TOKEN(offset)->content, "BYTE") == 0)
            {
                operand.mem.size = 8;
            }
            else if (strcmp(TOKEN(offset)->content, "WORD") == 0)
            {
                operand.mem.size = 16;
            }
            else if (strcmp(TOKEN(offset)->content, "DWORD") == 0)
            {
                operand.mem.size = 32;
            }
            else if (strcmp(TOKEN(offset)->content, "QWORD") == 0)
            {
                operand.mem.size = 64;
            }
            else
            {
                error(TOKEN(offset), "Invalid or missing size specifier before memory operand.", 1, "Expected one of: BYTE, WORD, DWORD, QWORD.");
            }
            offset++;
        }
    
        // memory
        operand.type = OPERAND_MEMORY;
        offset++;

        operand.mem.base = (Register){-1, -1};
        operand.mem.index = (Register){-1, -1};
        operand.mem.scale = 1;
        operand.mem.displacement = 0;
        Register reg = find_register(TOKEN(offset)->content);
        if (reg.size != 255)
        {
            if (TOKEN(offset+1)->content[0] == '*')
            {
                operand.mem.index = reg;
                offset += 2;
                operand.mem.scale = atoi(TOKEN(offset)->content);
                if (TOKEN(offset+1)->content[0] == '+')
                {
                    operand.mem.displacement = atoi(TOKEN(offset+2)->content);
                    offset += 2;
                }
                else if (TOKEN(offset+1)->content[0] == '-')
                {
                    operand.mem.displacement = -atoi(TOKEN(offset+2)->content);
                    offset += 2;
                }
            }
            else
            {
                operand.mem.base = reg;
                if (TOKEN(offset+1)->content[0] != ']')
                {
                    reg = find_register(TOKEN(offset+2)->content);
                    if (reg.size != 255)
                    {
                        offset += 2;
                        operand.mem.index = reg;
                        if (operand.mem.index.reg == 4)
                        {
                            Register temp = operand.mem.index;
                            operand.mem.index = operand.mem.base;
                            operand.mem.base = temp;
                        }
                        if (TOKEN(offset+1)->content[0] == '*')
                        {
                            operand.mem.scale = atoi(TOKEN(offset+2)->content);
                            
                            offset+=2;
                        }
                    }
                    if (TOKEN(offset+1)->content[0] == '+')
                    {
                        operand.mem.displacement = atoi(TOKEN(offset+2)->content);
                        offset += 2;
                    }
                    else if (TOKEN(offset+1)->content[0] == '-')
                    {
                        operand.mem.displacement = -atoi(TOKEN(offset+2)->content);
                        offset += 2;
                    }
                }
            }
            
        }
        else
        {
            operand.mem.displacement = atoi(TOKEN(offset)->content);
        }
        offset++;

        if (operand.mem.index.size != 255  && operand.mem.scale == 1 && operand.mem.base.reg == 5)
        {
            Register temp = operand.mem.base;
            operand.mem.base = operand.mem.index;
            operand.mem.index = temp;
        }

    }
    else if (reg.size != 255)
    {
        if (!(allowed_operands & OP_REG))
        {
            error(TOKEN(offset), "Register Operand Not Allowed!", 1, note);
        }
        operand.type = OPERAND_REGISTER;
        operand.reg = reg;

    }
    else if (isdigit(TOKEN(offset)->content[0]))
    {
        if (!(allowed_operands & OP_IMM))
        {
            error(TOKEN(offset), "Immediate Operand Not Allowed!", 1, note);
        }
        operand.type = OPERAND_IMMEDIATE;
        operand.immediate = atoi(TOKEN(offset)->content);
    }
    else
    {
        if (!(allowed_operands & OP_IDT))
        {
            error(TOKEN(offset), "Identifier Operand Not Allowed!", 1, note);
        }
        operand.type = OPERAND_IDENTIFIER;
        operand.idt.var_name = TOKEN(offset)->content;
    }
    return operand;
}

int unary_instructions(Instruction* inst, __uint8_t instruction, __uint8_t id)
{
    Operand op1 = inst->val.instruction.op1;

    if (op1.type == OPERAND_REGISTER)
    {
        if (op1.reg.size == 64 || (instruction == 0xFF && id == 4))
        {
            int extended_offset = 0;
            if (op1.reg.reg > 7)
            {
                extended_offset++;
                op1.reg.reg -= 8;
            }
            if (instruction == 0xFF && id == 4)
            {
                if (extended_offset != 0) fprintf(file_out, "%c", 0x40 + extended_offset);
                fprintf(file_out, "%c%c", instruction, get_mod_rm(3, id, op1.reg.reg));
            }
            else
            {
                fprintf(file_out, "%c%c%c", 0x48+extended_offset, instruction, get_mod_rm(3, id, op1.reg.reg));
            }
        }
        else if (op1.reg.size == 32)
        {
            fprintf(file_out, "%c%c", instruction, get_mod_rm(3, id, op1.reg.reg));
        }
        else if (op1.reg.size == 16)
        {
            fprintf(file_out, "%c%c%c", 0x66, instruction, get_mod_rm(3, id, op1.reg.reg));
        }
        else if (op1.reg.size == 8)
        {
            fprintf(file_out, "%c%c", instruction-1, get_mod_rm(3, id, op1.reg.reg));
        }
    }
    else if (op1.type == OPERAND_IMMEDIATE)
    {
        // make some error happen. this should not happen
    }
    else if (op1.type == OPERAND_MEMORY)
    {
        if (op1.mem.base.size == 32 || op1.mem.index.size == 32)
        {
            fprintf(file_out, "%c", 0x67);
        }
        
        int extended_offset = 0;
        if (op1.mem.index.reg != 255 && op1.mem.index.reg > 7)
        {
            extended_offset += 2;
            op1.mem.index.reg -= 8;
        }
        if (op1.mem.base.reg != 255 && op1.mem.base.reg > 7)
        {
            extended_offset++;
            op1.mem.base.reg -= 8;
        }

        if (instruction != 0xFF || id != 4) // not JMP
        {
            if (op1.mem.size == 64)
            {
                fprintf(file_out, "%c%c", 0x48 + extended_offset, instruction);
            }
            else if (op1.mem.size == 32)
            {
                if (extended_offset != 0) fprintf(file_out, "%c", 0x40 + extended_offset);
                fprintf(file_out, "%c", instruction);
            }
            else if (op1.mem.size == 16)
            {
                fprintf(file_out, "%c", 0x66);
                if (extended_offset != 0) fprintf(file_out, "%c", 0x40 + extended_offset);
                fprintf(file_out, "%c", instruction);
            }
            else if (op1.mem.size == 8)
            {
                if (extended_offset != 0) fprintf(file_out, "%c", 0x40 + extended_offset);
                fprintf(file_out, "%c", instruction-1);
            }
        }
        else
        {
            if (extended_offset != 0) fprintf(file_out, "%c", 0x40 + extended_offset);
            fprintf(file_out, "%c", instruction);
        }

        if (op1.mem.base.size == 255 && op1.mem.index.size == 255)
        {
            fprintf(file_out, "%c%c", get_mod_rm(0, id, 4), 0x25);
            write_little_endian_bytes(op1.mem.displacement, 4);
        }
        else
        {
            if (op1.mem.index.size != 255)
            {
                int scale;
                switch (op1.mem.scale)
                {
                case 1:
                    scale = 0;
                    break;
                case 2:
                    scale = 1;
                    break;
                case 4:
                    scale = 2;
                    break;
                case 8:
                    scale = 3;
                    break;
                
                default:
                    break;
                }
                fprintf(file_out, "%c%c", get_mod_rm(MAX(op1.mem.base.reg == 5 ? 1 : 0, op1.mem.displacement == 0 ? 0 : ((op1.mem.displacement > -128 && op1.mem.displacement < 128) ? 1 : 2)), id, 4),
                    get_mod_rm(scale, op1.mem.index.reg, op1.mem.base.reg));
            }
            else
            {
                fprintf(file_out, "%c", get_mod_rm(MAX(op1.mem.base.reg == 5 ? 1 : 0 , op1.mem.displacement == 0 ? 0 : ((op1.mem.displacement > -128 && op1.mem.displacement < 128) ? 1 : 2)), id, op1.mem.base.reg));

                if (op1.mem.base.reg == 4)
                {
                    fprintf(file_out, "%c", 0x24);
                }
                else if (op1.mem.base.reg == 4)
                {
                    fprintf(file_out, "%c", 0x00);
                }
            }

            if ((op1.mem.displacement != 0 && op1.mem.displacement > -128 && op1.mem.displacement < 128) || (op1.mem.displacement > -128 && op1.mem.displacement < 128 && op1.mem.base.reg == 5))
            {
                print_signed_integer_as_ascii(1, op1.mem.displacement);
            }
            else if (op1.mem.displacement != 0)
            {
                print_signed_integer_as_ascii(4, op1.mem.displacement);
            }
        }
    }
    return 1;
}

int unary_instructions_size(Instruction* inst, __uint8_t instruction, __uint8_t id)
{
    inst->type = INST_INSTRUCTION;
    int instruction_size = 0;
    Operand op1 = find_next_operand(OP_REG | OP_IMM | OP_MEM | OP_IDT);
    inst->val.instruction.op1 = op1;
    offset++;

    if (op1.type == OPERAND_REGISTER)
    {
        if (op1.reg.size == 64)
        {
            int extended_offset = 0;
            if (op1.reg.reg > 7)
            {
                extended_offset++;
                op1.reg.reg -= 8;
            }
            instruction_size += 3;
        }
        else if (op1.reg.size == 32)
        {
            instruction_size += 2;
        }
        else if (op1.reg.size == 16)
        {
            instruction_size += 3;
        }
        else if (op1.reg.size == 8)
        {
            instruction_size += 2;
        }
    }
    else if (op1.type == OPERAND_IMMEDIATE)
    {
        // make some error happen. this should not happen
    }
    else if (op1.type == OPERAND_MEMORY)
    {
        if (op1.mem.base.size == 32 || op1.mem.index.size == 32)
        {
            instruction_size++;
        }
        
        int extended_offset = 0;
        if (op1.mem.index.reg != 255 && op1.mem.index.reg > 7)
        {
            extended_offset += 2;
            op1.mem.index.reg -= 8;
        }
        if (op1.mem.base.reg != 255 && op1.mem.base.reg > 7)
        {
            extended_offset++;
            op1.mem.base.reg -= 8;
        }

        if (instruction != 0xFF || id != 4) // not JMP
        {
            if (op1.mem.size == 64)
            {
                instruction_size++;
            }
            else if (op1.mem.size == 32)
            {
                if (extended_offset != 0) instruction_size++;
                instruction_size++;
            }
            else if (op1.mem.size == 16)
            {
                instruction_size+=2;
                if (extended_offset != 0) instruction_size++;
            }
            else if (op1.mem.size == 8)
            {
                if (extended_offset != 0) instruction_size++;
                instruction_size++;
            }
        }
        else
        {
            instruction_size++;
        }

        if (op1.mem.base.size == 255 && op1.mem.index.size == 255)
        {
            instruction_size+=6;
        }
        else
        {
            if (op1.mem.index.size != 255)
            {
                instruction_size+=2;
            }
            else
            {
                instruction_size++;
                if (op1.mem.base.reg == 4)
                {
                    instruction_size++;
                }
            }

            if ((op1.mem.displacement != 0 && op1.mem.displacement > -128 && op1.mem.displacement < 128) || (op1.mem.displacement > -128 && op1.mem.displacement < 128 && op1.mem.base.reg == 5))
            {
                instruction_size++;
            }
            else if (op1.mem.displacement != 0)
            {
                instruction_size+=4;
            }
        }
    }
    inst->size = instruction_size;
    return 1;
}

int multi_purpose_instruction(Instruction* inst, __uint8_t instruction, __uint8_t rax_imm_op, __uint8_t id)
{
    Operand op1 = inst->val.instruction.op1;
    Operand op2 = inst->val.instruction.op2;
    
    if (instruction != 0x8D && op1.type == OPERAND_REGISTER && op2.type == OPERAND_REGISTER)
    {
        if (op1.reg.size != op2.reg.size)
        {
 
        }

        if (op1.reg.size == 64)
        {
            unsigned char opt = 0x48;
            if (op1.reg.reg > 7)
            {
                opt++;
                op1.reg.reg -= 8;
            }
            if (op2.reg.reg > 7)
            {
                opt += 4;
                op2.reg.reg -= 8;
            }
            fprintf(file_out, "%c%c", opt, instruction);
        }
        else if (op1.reg.size == 32)
        {
            fprintf(file_out, "%c", instruction);
        }
        else if (op1.reg.size == 16)
        {
            fprintf(file_out, "%c%c", 0x66, instruction);
        }
        else if (op1.reg.size == 8)
        {
            fprintf(file_out, "%c", instruction-1);
        }

        fprintf(file_out, "%c", get_mod_rm(3, op2.reg.reg, op1.reg.reg));
    }
    else if (instruction != 0x8D && op1.type == OPERAND_REGISTER && (op2.type == OPERAND_IMMEDIATE || (instruction == 0x89 && op2.type == OPERAND_IDENTIFIER)))
    {
        
        if (instruction == 0x89) // MOV
        {
            if (op2.type == OPERAND_IDENTIFIER)
            {
                op2.type = OPERAND_IMMEDIATE;
                for (int i = 0; i < (int)instructions.size; i++)
                {
                    if (INSTRUCTION(i)->type == INST_VARIABLE && strcmp(INSTRUCTION(i)->val.var.var_name, op2.idt.var_name) == 0)
                    {
                        if (INSTRUCTION(i)->val.var.is_constant)
                        {
                            op2.immediate = INSTRUCTION(i)->val.var.constant;
                        }
                        else
                        {
                            op2.immediate = 0x400078 + INSTRUCTION(i)->offset;
                        }
                        break;
                    }
                }
            }
            if (op1.reg.size == 64)
            {
                int size = 4;
                if (op2.immediate > __INT32_MAX__)
                {
                    size = 8;
                    fprintf(file_out, "%c", 0x48);
                }
                unsigned char opt = 0x48;
                if (op1.reg.reg > 7)
                {
                    opt++;
                    op1.reg.reg -= 8;
                }
                fprintf(file_out, "%c", opt);
                fprintf(file_out, "%c", 0xC7);
                fprintf(file_out, "%c", get_mod_rm(3, 0, op1.reg.reg));
                write_little_endian_bytes(op2.immediate, size);
            }
            else if (op1.reg.size == 32)
            {
                fprintf(file_out, "%c", get_mod_rm(2, 7, op1.reg.reg));
                write_little_endian_bytes(op2.immediate, 4);
            }
            else if (op1.reg.size == 16)
            {
                fprintf(file_out, "%c%c", 0x66, get_mod_rm(2, 7, op1.reg.reg));
                write_little_endian_bytes(op2.immediate, 2);
            }
            else if (op1.reg.size == 8)
            {
                fprintf(file_out, "%c", get_mod_rm(2, 6, op1.reg.reg));
                write_little_endian_bytes(op2.immediate, 1);
            } 
        }
        else // ANY other instruction
        {
            if (op1.reg.reg == 0 && (op2.immediate > 255 || op1.reg.size == 8 || instruction == 0x85))
            {
                if (op1.reg.size == 64) fprintf(file_out, "%c", 0x48);
                if (op1.reg.size == 16) fprintf(file_out, "%c", 0x66);

                if (op1.reg.size == 8)
                {
                    fprintf(file_out, "%c", rax_imm_op-1);
                }
                else
                {
                    fprintf(file_out, "%c", rax_imm_op);
                }

                if (op1.reg.size >= 32)
                {
                    write_little_endian_bytes(op2.immediate, 4);
                }
                else if (op1.reg.size == 16)
                {
                    write_little_endian_bytes(op2.immediate, 2);
                }
                else if (op1.reg.size == 8)
                {
                    write_little_endian_bytes(op2.immediate, 1);
                }
            }
            else if (op1.reg.size == 64)
            {
                int extended_offset = 0;
                if (op1.reg.reg > 7)
                {
                    extended_offset++;
                    op1.reg.reg -= 8;
                }
                if (instruction == 0x85)
                {
                    fprintf(file_out, "%c%c%c", 0x48 + extended_offset, 0xF7, get_mod_rm(3, 0, op1.reg.reg));
                    write_little_endian_bytes(op2.immediate, 4);
                }
                else if (op2.immediate > 255)
                {
                    fprintf(file_out, "%c%c%c", 0x48 + extended_offset, 0x81, get_mod_rm(3, id, op1.reg.reg));
                    write_little_endian_bytes(op2.immediate, 4);
                }
                else
                {
                    fprintf(file_out, "%c%c%c", 0x48 + extended_offset, 0x83, get_mod_rm(3, id, op1.reg.reg));
                    write_little_endian_bytes(op2.immediate, 1);
                }
            }
            else if (op1.reg.size == 32)
            {
                if (instruction == 0x85)
                {
                    fprintf(file_out, "%c%c", 0xF7, get_mod_rm(3, 0, op1.reg.reg));
                    write_little_endian_bytes(op2.immediate, 4);
                }
                else if (op2.immediate > 255)
                {
                    fprintf(file_out, "%c%c", 0x81, get_mod_rm(3, id, op1.reg.reg));
                    write_little_endian_bytes(op2.immediate, 4);
                }
                else
                {
                    fprintf(file_out, "%c%c", 0x83, get_mod_rm(3, id, op1.reg.reg));
                    write_little_endian_bytes(op2.immediate, 1);
                }
            }
            else if (op1.reg.size == 16)
            {
                if (instruction == 0x85)
                {
                    fprintf(file_out, "%c%c%c", 0x66, 0xF7, get_mod_rm(3, 0, op1.reg.reg));
                    write_little_endian_bytes(op2.immediate, 2);
                }
                else if (op2.immediate > 255)
                {
                    fprintf(file_out, "%c%c%c", 0x66, 0x81, get_mod_rm(3, id, op1.reg.reg));
                    write_little_endian_bytes(op2.immediate, 2);
                }
                else
                {
                    fprintf(file_out, "%c%c%c", 0x66, 0x83, get_mod_rm(3, id, op1.reg.reg));
                    write_little_endian_bytes(op2.immediate, 1);
                }
            }
            else if (op1.reg.size == 8)
            {
                if (instruction == 0x85)
                {
                    fprintf(file_out, "%c%c", 0xF6, get_mod_rm(3, id, op1.reg.reg));
                    write_little_endian_bytes(op2.immediate, 1);
                }
                else
                {
                    fprintf(file_out, "%c%c", 0x80, get_mod_rm(3, id, op1.reg.reg));
                    write_little_endian_bytes(op2.immediate, 1);
                }
            }
        }

    }
    else if ((op1.type == OPERAND_REGISTER && op2.type == OPERAND_MEMORY) || (op2.type == OPERAND_REGISTER && op1.type == OPERAND_MEMORY && instruction != 0x8D))
    {
        int reverse_offset = 0;
        if (op1.type == OPERAND_REGISTER && op2.type == OPERAND_MEMORY)
        {
            if (instruction != 0x85 && instruction != 0x8D) // There is no reverse for test and lea
            reverse_offset = 2;
            Operand temp = op1;
            op1 = op2;
            op2 = temp;
        }

        unsigned char opt_offset = 0;
        if (op1.mem.base.size == 32 || op1.mem.index.size == 32)
        {
            fprintf(file_out, "%c", 0x67);
        }
        else if (op1.mem.base.size == 64 || op1.mem.index.size == 64)
        {
            if (op1.mem.base.size != 255 && op1.mem.base.reg > 7)
            {
                opt_offset++;
                op1.mem.base.reg -= 8;
            }
            if (op1.mem.index.size != 255 && op1.mem.index.reg > 7)
            {
                opt_offset += 2;
                op1.mem.index.reg -= 8;
            }
        }

        if (op2.reg.size == 64)
        {
            if (op2.reg.reg > 7)
            {
                opt_offset += 4;
                op2.reg.reg -= 8;
            }
            fprintf(file_out, "%c", 0x48 + opt_offset);
        }
        else if (op2.reg.size == 32 && opt_offset != 0)
        {
            fprintf(file_out, "%c", 0x40 + opt_offset);
        }
        else if (op2.reg.size == 16)
        {
            fprintf(file_out, "%c", 0x66);
            if (opt_offset != 0)
            {
                fprintf(file_out, "%c", 0x40 + opt_offset);
            }
        }
        else if (op2.reg.size == 8 && opt_offset != 0)
        {
            fprintf(file_out, "%c", 0x40 + opt_offset);
        }

        if (op2.reg.size == 8)
        {
            fprintf(file_out, "%c", instruction-1 + reverse_offset);
        }
        else
        {
            fprintf(file_out, "%c", instruction + reverse_offset);
        }

        if (op1.mem.base.reg == 4 && op1.mem.index.size == 255)
        {
            if (op1.mem.index.size != 255)
            {
                fprintf(file_out, "%c%c", get_mod_rm(op1.mem.displacement != 0 ? (op1.mem.displacement < 128 && op1.mem.displacement > -128 ? 1 : 2) : 0, op2.reg.reg, 4),
                                    get_mod_rm(0, op1.mem.index.reg, 4));
            }
            else
            {
                fprintf(file_out, "%c%c", get_mod_rm(op1.mem.displacement != 0 ? (op1.mem.displacement < 128 && op1.mem.displacement > -128 ? 1 : 2) : 0, op2.reg.reg, 4),
                                    get_mod_rm(0, 4, 4));
            }
            
            if (op1.mem.displacement > -128 && op1.mem.displacement < 128 && op1.mem.displacement != 0)
            {
                print_signed_integer_as_ascii(1, op1.mem.displacement);
            }
            else if (op1.mem.displacement != 0)
            {
                print_signed_integer_as_ascii(4, op1.mem.displacement);
            }
        }
        else if (op1.mem.index.size != 255 && op1.mem.base.reg != 5)
        {
            int scale = op1.mem.scale;
            switch (scale)
            {
            case 1:
                scale = 0;
                break;
            case 2:
                scale = 1;
                break;
            case 4:
                scale = 2;
                break;
            case 8:
                scale = 3;
                break;
            
            default:
                break;
            }
            fprintf(file_out, "%c%c", get_mod_rm(op1.mem.base.size == 255 ? 0: (op1.mem.displacement != 0 ? (op1.mem.displacement < 128 && op1.mem.displacement > -128 ? 1 : 2) : 0), op2.reg.reg, 4),
                                    get_mod_rm(scale, op1.mem.index.reg, op1.mem.base.reg == 255 ? 5 : op1.mem.base.reg));
            if (op1.mem.displacement > -128 && op1.mem.displacement < 128 && op1.mem.displacement != 0)
            {
                print_signed_integer_as_ascii(1, op1.mem.displacement);
            }
            else if (op1.mem.displacement != 0)
            {
                print_signed_integer_as_ascii(4, op1.mem.displacement);
            }
        }
        else if (op1.mem.index.size != 255 && op1.mem.base.reg == 5)
        {
            int scale = op1.mem.scale;
            switch (scale)
            {
            case 1:
                scale = 0;
                break;
            case 2:
                scale = 1;
                break;
            case 4:
                scale = 2;
                break;
            case 8:
                scale = 3;
                break;
            
            default:
                break;
            }
            fprintf(file_out, "%c%c", get_mod_rm(op1.mem.base.size == 255 ? 0: (op1.mem.displacement < 128 && op1.mem.displacement > -128 ? 1 : 2), op2.reg.reg, 4),
                                    get_mod_rm(scale, op1.mem.index.reg, op1.mem.base.reg));
            if (op1.mem.displacement > -128 && op1.mem.displacement < 128)
            {
                print_signed_integer_as_ascii(1, op1.mem.displacement);
            }
            else if (op1.mem.displacement != 0)
            {
                print_signed_integer_as_ascii(4, op1.mem.displacement);
            }
        }
        else if (op1.mem.index.size == 255 && op1.mem.base.reg != 5)
        {
            fprintf(file_out, "%c", get_mod_rm(op1.mem.displacement != 0 ? (op1.mem.displacement < 128 && op1.mem.displacement > -128 ? 1 : 2) : 0, op2.reg.reg, op1.mem.base.reg));
            if (op1.mem.displacement > -128 && op1.mem.displacement < 128 && op1.mem.displacement != 0)
            {
                print_signed_integer_as_ascii(1, op1.mem.displacement);
            }
            else if (op1.mem.displacement != 0)
            {
                print_signed_integer_as_ascii(4, op1.mem.displacement);
            }
        }
        else if (op1.mem.index.size == 255 && op1.mem.base.reg == 5)
        {
            fprintf(file_out, "%c", get_mod_rm(op1.mem.displacement < 128 && op1.mem.displacement > -128 ? 1 : 2, op2.reg.reg, op1.mem.base.reg));
            if (op1.mem.displacement > -128 && op1.mem.displacement < 128)
            {
                print_signed_integer_as_ascii(1, op1.mem.displacement);
            }
            else if (op1.mem.displacement != 0)
            {
                print_signed_integer_as_ascii(4, op1.mem.displacement);
            }
        }
    }

    return 1;
}

int multi_purpose_instruction_size(Instruction* inst, __uint8_t instruction)
{
    inst->type = INST_INSTRUCTION;
    int instruction_size = 0;
    Operand op1 = find_next_operand(OP_REG | OP_MEM);
    Operand op2 = find_next_operand(OP_REG | OP_MEM | OP_IDT | OP_IMM);
    inst->val.instruction.op1 = op1;
    inst->val.instruction.op2 = op2;
    offset++;
    
    if (op1.type == OPERAND_REGISTER && op2.type == OPERAND_REGISTER)
    {
        if (op1.reg.size != op2.reg.size)
        {
 
        }

        if (op1.reg.size == 64)
        {
            unsigned char opt = 0x48;
            if (op1.reg.reg > 7)
            {
                opt++;
                op1.reg.reg -= 8;
            }
            if (op2.reg.reg > 7)
            {
                opt += 4;
                op2.reg.reg -= 8;
            }
            instruction_size+=2;
        }
        else if (op1.reg.size == 32)
        {
            instruction_size++;
        }
        else if (op1.reg.size == 16)
        {
            instruction_size+=2;
        }
        else if (op1.reg.size == 8)
        {
            instruction_size++;
        }
        
        instruction_size++;
    }
    if (op1.type == OPERAND_REGISTER && op2.type == OPERAND_IMMEDIATE)
    {
        if (instruction == 0x89) // MOV
        {
            if (op1.reg.size == 64)
            {
                int size = 4;
                if (op2.immediate > __INT32_MAX__)
                {
                    size = 8;
                    instruction_size++;
                }
                unsigned char opt = 0x48;
                if (op1.reg.reg > 7)
                {
                    opt++;
                    op1.reg.reg -= 8;
                }
                instruction_size+=3;
                instruction_size+=size;
            }
            else if (op1.reg.size == 32)
            {
                instruction_size+=5;
            }
            else if (op1.reg.size == 16)
            {
                instruction_size+=4;
            }
            else if (op1.reg.size == 8)
            {
                instruction_size+=2;
            } 
        }
        else // ANY other instruction
        {
            if (op1.reg.reg == 0 && (op2.immediate > 255 || op1.reg.size == 8 || instruction == 0x85))
            {
                if (op1.reg.size == 64) instruction_size++;
                if (op1.reg.size == 16) instruction_size++;

                if (op1.reg.size == 8)
                {
                    instruction_size++;
                }
                else
                {
                    instruction_size++;
                }

                if (op1.reg.size >= 32)
                {
                    instruction_size+=4;
                }
                else if (op1.reg.size == 16)
                {
                    instruction_size+=2;
                }
                else if (op1.reg.size == 8)
                {
                    instruction_size++;
                }
            }
            else if (op1.reg.size == 64)
            {
                int extended_offset = 0;
                if (op1.reg.reg > 7)
                {
                    extended_offset++;
                    op1.reg.reg -= 8;
                }
                if (instruction == 0x85)
                {
                    instruction_size+=7;
                }
                else if (op2.immediate > 255)
                {
                    instruction_size+=7;
                }
                else
                {
                    instruction_size+=4;
                }
            }
            else if (op1.reg.size == 32)
            {
                if (instruction == 0x85)
                {
                    instruction_size+=6;
                }
                else if (op2.immediate > 255)
                {
                    instruction_size+=6;
                }
                else
                {
                    instruction_size+=3;
                }
            }
            else if (op1.reg.size == 16)
            {
                if (instruction == 0x85)
                {
                    instruction_size+=5;
                }
                else if (op2.immediate > 255)
                {
                    instruction_size+=5;
                }
                else
                {
                    instruction_size+=4;
                }
            }
            else if (op1.reg.size == 8)
            {
                if (instruction == 0x85)
                {
                    instruction_size+=3;
                }
                else
                {
                    instruction_size+=3;
                }
            }
        }

    }
    else if ((op1.type == OPERAND_REGISTER && op2.type == OPERAND_MEMORY) || (op2.type == OPERAND_REGISTER && op1.type == OPERAND_MEMORY))
    {

        if (op1.type == OPERAND_REGISTER && op2.type == OPERAND_MEMORY)
        {
            Operand temp = op1;
            op1 = op2;
            op2 = temp;
        }

        unsigned char opt_offset = 0;
        if (op1.mem.base.size == 32 || op1.mem.index.size == 32)
        {
            instruction_size++;
        }
        else if (op1.mem.base.size == 64 || op1.mem.index.size == 64)
        {
            if (op1.mem.base.size != 255 && op1.mem.base.reg > 7)
            {
                opt_offset++;
                op1.mem.base.reg -= 8;
            }
            if (op1.mem.index.size != 255 && op1.mem.index.reg > 7)
            {
                opt_offset += 2;
                op1.mem.index.reg -= 8;
            }
        }

        if (op2.reg.size == 64)
        {
            if (op2.reg.reg > 7)
            {
                opt_offset += 4;
                op2.reg.reg -= 8;
            }
            instruction_size++;
        }
        else if (op2.reg.size == 32 && opt_offset != 0)
        {
            instruction_size++;
        }
        else if (op2.reg.size == 16)
        {
            instruction_size++;
            if (opt_offset != 0)
            {
                instruction_size++;
            }
        }
        else if (op2.reg.size == 8 && opt_offset != 0)
        {
            instruction_size++;
        }

        if (op2.reg.size == 8)
        {
            instruction_size++;
        }
        else
        {
            instruction_size++;
        }

        if (op1.mem.base.reg == 4 && op1.mem.index.size == 255)
        {
            if (op1.mem.index.size != 255)
            {
                instruction_size+=2;
            }
            else
            {
                instruction_size+=2;
            }
            
            if (op1.mem.displacement > -128 && op1.mem.displacement < 128 && op1.mem.displacement != 0)
            {
                instruction_size++;
            }
            else if (op1.mem.displacement != 0)
            {
                instruction_size+=4;
            }
        }
        else if (op1.mem.index.size != 255 && op1.mem.base.reg != 5)
        {
            instruction_size+=2;
            if (op1.mem.displacement > -128 && op1.mem.displacement < 128 && op1.mem.displacement != 0)
            {
                instruction_size++;
            }
            else if (op1.mem.displacement != 0)
            {
                instruction_size+=4;
            }
        }
        else if (op1.mem.index.size != 255 && op1.mem.base.reg == 5)
        {
            instruction_size+=2;
            if (op1.mem.displacement > -128 && op1.mem.displacement < 128)
            {
                instruction_size++;
            }
            else if (op1.mem.displacement != 0)
            {
                instruction_size+=4;
            }
        }
        else if (op1.mem.index.size == 255 && op1.mem.base.reg != 5)
        {
            instruction_size++;
            if (op1.mem.displacement > -128 && op1.mem.displacement < 128 && op1.mem.displacement != 0)
            {
                instruction_size++;
            }
            else if (op1.mem.displacement != 0)
            {
                instruction_size+=4;
            }
        }
        else if (op1.mem.index.size == 255 && op1.mem.base.reg == 5)
        {
            instruction_size++;
            if (op1.mem.displacement > -128 && op1.mem.displacement < 128)
            {
                instruction_size++;
            }
            else if (op1.mem.displacement != 0)
            {
                instruction_size+=4;
            }
        }
    }
    inst->size = instruction_size;
    return 1;
}

int jump_instruction(Instruction* inst, __uint8_t instruction)
{
    int offset = (*inst->val.jmp.label_offset - inst->offset) - inst->size;
    
    if (inst->size == 2)
    {
        fprintf(file_out, "%c", 0x70 + instruction);
        print_signed_integer_as_ascii(1, offset);
    }
    else if (inst->size == 6)
    {
        fprintf(file_out, "%c%c", 0x0F, 0x80 + instruction);
        print_signed_integer_as_ascii(4, offset);
    }
    return 1;
}

int jump_instruction_size(Instruction* inst)
{
    offset++;
    inst->val.jmp.label = TOKEN(offset)->content;
    offset++;
    inst->type = INST_JUMP;
    inst->size = 2;

    return 1;
}

int push_pop_instruction(Instruction* inst, __uint8_t instruction)
{
    Operand op1 = inst->val.instruction.op1;

    if (op1.type == OPERAND_REGISTER)
    {
        if (op1.reg.size == 64)
        {
            if (op1.reg.reg > 7)
            {
                op1.reg.reg -= 8;
                fprintf(file_out, "%c", 0x41);
            }
            fprintf(file_out, "%c", instruction + op1.reg.reg);

        }
        else if (op1.reg.size == 16)
        {
            fprintf(file_out, "%c%c", 0x66, instruction + op1.reg.reg);
        }
        else
        {
            // error
        }
    }
    else if (op1.type == OPERAND_IMMEDIATE)
    {
        if (instruction == 0x50)
        {
            if (op1.immediate > 255)
            {
                fprintf(file_out, "%c", 0x68);
                write_little_endian_bytes(op1.immediate, 4);
            }
            else
            {
                fprintf(file_out, "%c", 0x6A);
                write_little_endian_bytes(op1.immediate, 1);
            }
        }
        else
        {
            printf("cannot use immediate value on pop");
        }
    }
    else if (op1.type == OPERAND_MEMORY)
    {
        if (op1.mem.index.size == 32 || op1.mem.base.size == 32)
        {
            fprintf(file_out, "%c", 0x67);
        }

    
        if (op1.mem.size == 16)
        {
            fprintf(file_out, "%c", 0x66);
        }

        if (op1.mem.index.size == 64 || op1.mem.base.size == 64)
        {
            int opt = 0;
            if (op1.mem.index.reg > 7 && op1.mem.index.reg < 255)
            {
                opt+=2;
                op1.mem.index.reg -= 8;
            }
            if (op1.mem.base.reg > 7 && op1.mem.base.reg < 255)
            {
                opt++;
                op1.mem.base.reg -= 8;
            }
            if (opt != 0)
            fprintf(file_out, "%c", 0x40 + opt);
        }
        

        if (op1.mem.base.reg == 255 && op1.mem.index.reg == 255)
        {
            if (instruction == 0x50)
            {
                fprintf(file_out, "%c%c", 0xFF, 0x34);
                write_little_endian_bytes(op1.mem.displacement, 4);
            }
            else if (instruction == 0x58)
            {
                fprintf(file_out, "%c%c", 0x8F, 0x04);
                write_little_endian_bytes(op1.mem.displacement, 4);
            }
        }
        else if (op1.mem.index.reg == 255)
        {
            if (instruction == 0x50)
            {
                fprintf(file_out, "%c%c", 0xFF, get_mod_rm(MAX(op1.mem.base.reg == 5 ? 1 : 0, op1.mem.displacement == 0 ? 0: (op1.mem.displacement > 127 || op1.mem.displacement < -128 ? 2 : 1)), 6, op1.mem.base.reg));
                if (op1.mem.base.reg == 4)
                {
                    fprintf(file_out, "%c", 0x24);
                }
                if (op1.mem.displacement != 0 && op1.mem.displacement <= 127 && op1.mem.displacement >= -128)
                {
                    print_signed_integer_as_ascii(1, op1.mem.displacement);
                }
                else if (op1.mem.displacement != 0)
                {
                    print_signed_integer_as_ascii(4, op1.mem.displacement);
                }
                else if (op1.mem.base.reg == 5)
                {
                    fprintf(file_out, "%c", 0x00);
                }
            }
            else
            {
                fprintf(file_out, "%c%c", 0x8F, get_mod_rm(MAX(op1.mem.base.reg == 5 ? 1 : 0, op1.mem.displacement == 0 ? 0: (op1.mem.displacement > 127 || op1.mem.displacement < -128 ? 2 : 1)), 0, op1.mem.base.reg));
                if (op1.mem.base.reg == 4)
                {
                    fprintf(file_out, "%c", 0x24);
                }
                if (op1.mem.displacement != 0 && op1.mem.displacement <= 127 && op1.mem.displacement >= -128)
                {
                    print_signed_integer_as_ascii(1, op1.mem.displacement);
                }
                else if (op1.mem.displacement != 0)
                {
                    print_signed_integer_as_ascii(4, op1.mem.displacement);
                }
                else if (op1.mem.base.reg == 5)
                {
                    fprintf(file_out, "%c", 0x00);
                }
            }
        }
        else if (op1.mem.base.reg == 255)
        {
            if (instruction == 0x50)
            {
                if (op1.mem.scale == 1)
                {
                    fprintf(file_out, "%c%c", 0xFF, get_mod_rm(MAX(op1.mem.index.reg == 5 ? 1 : 0, op1.mem.displacement == 0 ? 0: (op1.mem.displacement > 127 || op1.mem.displacement < -128 ? 2 : 1)), 6, op1.mem.index.reg));
                    if (op1.mem.index.reg == 4)
                    {
                        fprintf(file_out, "%c", 0x24);
                    }
                    if (op1.mem.displacement != 0 && op1.mem.displacement <= 127 && op1.mem.displacement >= -128)
                    {
                        print_signed_integer_as_ascii(1, op1.mem.displacement);
                    }
                    else if (op1.mem.displacement != 0)
                    {
                        print_signed_integer_as_ascii(4, op1.mem.displacement);
                    }
                    else if (op1.mem.index.reg == 5)
                    {
                        fprintf(file_out, "%c", 0x00);
                    }
                }
                else
                {
                    int scale = op1.mem.scale;
                    switch (scale)
                    {
                    case 1:
                        scale = 0;
                        break;
                    case 2:
                        scale = 1;
                        break;
                    case 4:
                        scale = 2;
                        break;
                    case 8:
                        scale = 3;
                        break;
                    
                    default:
                        break;
                    }
                    fprintf(file_out, "%c%c%c", 0xFF, 0x34, get_mod_rm(scale, op1.mem.index.reg, 5));
                    print_signed_integer_as_ascii(4, op1.mem.displacement);
                }
                
            }
            else if (instruction == 0x58)
            {
                if (op1.mem.scale == 1)
                {
                    fprintf(file_out, "%c%c", 0x8F, get_mod_rm(MAX(op1.mem.index.reg == 5 ? 1 : 0, op1.mem.displacement == 0 ? 0: (op1.mem.displacement > 127 || op1.mem.displacement < -128 ? 2 : 1)), 0, op1.mem.index.reg));
                    if (op1.mem.index.reg == 4)
                    {
                        fprintf(file_out, "%c", 0x24);
                    }
                    if (op1.mem.displacement != 0 && op1.mem.displacement <= 127 && op1.mem.displacement >= -128)
                    {
                        print_signed_integer_as_ascii(1, op1.mem.displacement);
                    }
                    else if (op1.mem.displacement != 0)
                    {
                        print_signed_integer_as_ascii(4, op1.mem.displacement);
                    }
                    else if (op1.mem.index.reg == 5)
                    {
                        fprintf(file_out, "%c", 0x00);
                    }
                    
                }
                else
                {
                    int scale = op1.mem.scale;
                    switch (scale)
                    {
                    case 1:
                        scale = 0;
                        break;
                    case 2:
                        scale = 1;
                        break;
                    case 4:
                        scale = 2;
                        break;
                    case 8:
                        scale = 3;
                        break;
                    
                    default:
                        break;
                    }
                    fprintf(file_out, "%c%c%c", 0x8F, 0x04, get_mod_rm(scale, op1.mem.index.reg, 5));
                    print_signed_integer_as_ascii(4, op1.mem.displacement);
                }
            }
        }
        else
        {


            if (instruction == 0x50)
            {
                int scale = op1.mem.scale;
                    switch (scale)
                    {
                    case 1:
                        scale = 0;
                        break;
                    case 2:
                        scale = 1;
                        break;
                    case 4:
                        scale = 2;
                        break;
                    case 8:
                        scale = 3;
                        break;
                    
                    default:
                        break;
                    }
                fprintf(file_out, "%c%c%c", 0xFF, get_mod_rm(MAX(op1.mem.base.reg == 5 ? 1 : 0, op1.mem.displacement == 0 ? 0: (op1.mem.displacement > 127 || op1.mem.displacement < -128 ? 2 : 1)), 6, 4),
                            get_mod_rm(scale, op1.mem.index.reg, op1.mem.base.reg));


                if (op1.mem.displacement != 0 && op1.mem.displacement <= 127 && op1.mem.displacement >= -128)
                {
                    print_signed_integer_as_ascii(1, op1.mem.displacement);
                }
                else if (op1.mem.displacement != 0)
                {
                    print_signed_integer_as_ascii(4, op1.mem.displacement);
                }
                else if (op1.mem.base.reg == 5)
                {
                    fprintf(file_out, "%c", 0x00);
                }
            }
            else
            {
                int scale = op1.mem.scale;
                    switch (scale)
                    {
                    case 1:
                        scale = 0;
                        break;
                    case 2:
                        scale = 1;
                        break;
                    case 4:
                        scale = 2;
                        break;
                    case 8:
                        scale = 3;
                        break;
                    
                    default:
                        break;
                    }
                fprintf(file_out, "%c%c%c", 0x8F, get_mod_rm(MAX(op1.mem.base.reg == 5 ? 1 : 0, op1.mem.displacement == 0 ? 0 : (op1.mem.displacement > 127 || op1.mem.displacement < -128 ? 2 : 1)), 0, 4),
                            get_mod_rm(scale, op1.mem.index.reg, op1.mem.base.reg));


                if (op1.mem.displacement != 0 && op1.mem.displacement <= 127 && op1.mem.displacement >= -128)
                {
                    print_signed_integer_as_ascii(1, op1.mem.displacement);
                }
                else if (op1.mem.displacement != 0)
                {
                    print_signed_integer_as_ascii(4, op1.mem.displacement);
                }
                else if (op1.mem.base.reg == 5)
                {
                    fprintf(file_out, "%c", 0x00);
                }
            }
        }
    }

    return 1;
}

int push_pop_instruction_size(Instruction* inst)
{
    inst->type = INST_INSTRUCTION;
    Operand op1 = find_next_operand(OP_REG | OP_IMM | OP_MEM);
    inst->val.instruction.op1 = op1;
    offset++;

    return 1;
}