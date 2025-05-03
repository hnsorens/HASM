#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "elf.h"

// Macros
#define INSTRUCTION(n) ((Instruction*)instructions.data[n])
#define TOKEN(n) ((Token*)tokens.data[n])
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define OP_REG 1
#define OP_IMM 2
#define OP_MEM 4
#define OP_IDT 8

// Vectors
typedef struct {
    void **data;      // Stores any type
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector* vec, size_t capacity);
void vector_push(Vector* vec, void* item);
void vector_free(Vector* vec);


void init_instruction_map();

typedef struct
{
    char* content;
    int line;
    int line_pos;
    int file_pos;
} Token;

typedef struct
{
    __uint8_t size;
    __uint8_t reg;
} Register;

typedef enum
{
    OPERAND_REGISTER,
    OPERAND_IMMEDIATE,
    OPERAND_MEMORY,
    OPERAND_IDENTIFIER
} OperandType;

typedef struct
{
    OperandType type;
    union
    {
        __int64_t immediate;
        Register reg;
        struct
        {
            int size;
            Register base;
            Register index;
            int scale;
            __int64_t displacement;
        } mem;
        struct
        {
            const char* var_name;
        } idt;
    };
} Operand;

typedef struct
{
    enum
    {
        INST_LABEL,
        INST_INSTRUCTION,
        INST_JUMP,
        INST_VARIABLE
    } type;
    int offset;
    int size;
    union
    {
        struct{
            char* label;
        } label;
        struct 
        {   
            char* keyword;
            Operand op1;
            Operand op2;
        } instruction;
        struct
        {
            char* keyword;
            char* label;
            int* label_offset;
        } jmp;
        struct
        {
            int is_constant;
            int64_t constant;
            const char* var_name;
            char* contents;
        } var;
    } val;
} Instruction;

// Instruction Map
typedef struct {
    int (*handler)(Instruction*);
    int (*size_handler)(Instruction*);
} InstructionEntry;


typedef enum
{
    ASM_TEXT,
    ASM_DATA,
    ASM_BSS,
    ASM_GLOBAL
} ASM_MODE;

extern Vector tokens;
extern Vector instructions;
extern InstructionEntry instruction_map[26*26*26];
extern FILE* file_out;
extern int global_offset;
extern int offset;
extern ASM_MODE mode;
extern char* begin_label_label;
extern int begin_label_instruction_index;
extern FILE* file;


#endif