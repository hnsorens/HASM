/*
 * HASM - x86 Assembly Compiler
 * Main header file containing core data structures and declarations
 * 
 * This file defines the fundamental data structures used throughout the assembler:
 * - Tokens for lexical analysis
 * - Instructions for syntax and semantic analysis
 * - Operands for instruction encoding
 * - Vectors for dynamic memory management
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "elf.h"

/* ==================== MACROS ==================== */

/* Convenience macros for accessing vector elements */
#define INSTRUCTION(n) ((Instruction*)instructions.data[n])  /* Get instruction at index n */
#define TOKEN(n) ((Token*)tokens.data[n])                    /* Get token at index n */
#define MAX(a, b) ((a) > (b) ? (a) : (b))                   /* Maximum of two values */

/* Operand type flags for instruction encoding */
#define OP_REG 1   /* Register operand */
#define OP_IMM 2   /* Immediate operand */
#define OP_MEM 4   /* Memory operand */
#define OP_IDT 8   /* Identifier operand */

/* ==================== VECTOR IMPLEMENTATION ==================== */

/**
 * Dynamic array implementation for storing any type of data
 * Used for tokens, instructions, and other collections
 */
typedef struct {
    void **data;      /* Stores any type - array of pointers */
    size_t size;      /* Current number of elements */
    size_t capacity;  /* Maximum number of elements before reallocation */
} Vector;

/* Vector operations */
void vector_init(Vector* vec, size_t capacity);  /* Initialize vector with given capacity */
void vector_push(Vector* vec, void* item);       /* Add item to end of vector */
void vector_free(Vector* vec);                   /* Free vector memory */

/* ==================== INSTRUCTION MAP ==================== */

void init_instruction_map();  /* Initialize the instruction handler map */

/* ==================== TOKEN STRUCTURE ==================== */

/**
 * Represents a single token from lexical analysis
 * Contains the token content and its position in the source file
 */
typedef struct
{
    char* content;    /* Token text content */
    int line;         /* Line number in source file */
    int line_pos;     /* Position within the line */
    int file_pos;     /* Position in entire file */
} Token;

/* ==================== REGISTER STRUCTURE ==================== */

/**
 * Represents an x86 register with its size and register number
 */
typedef struct
{
    __uint8_t size;   /* Register size in bytes (1, 2, 4, 8) */
    __uint8_t reg;    /* Register number/identifier */
} Register;

/* ==================== OPERAND TYPES ==================== */

/**
 * Types of operands that can appear in assembly instructions
 */
typedef enum
{
    OPERAND_REGISTER,   /* Register operand (e.g., RAX, EAX) */
    OPERAND_IMMEDIATE,  /* Immediate value (e.g., 42, 0x100) */
    OPERAND_MEMORY,     /* Memory reference (e.g., [RAX], [RAX+4]) */
    OPERAND_IDENTIFIER  /* Variable or label name */
} OperandType;

/* ==================== OPERAND STRUCTURE ==================== */

/**
 * Represents an operand in an assembly instruction
 * Can be a register, immediate value, memory reference, or identifier
 */
typedef struct
{
    OperandType type;  /* Type of this operand */
    union
    {
        __int64_t immediate;  /* For immediate values */
        Register reg;         /* For register operands */
        struct
        {
            int size;                    /* Memory operand size */
            Register base;               /* Base register */
            Register index;              /* Index register */
            int scale;                   /* Scale factor (1, 2, 4, 8) */
            __int64_t displacement;      /* Displacement/offset */
        } mem;                           /* For memory operands */
        struct
        {
            const char* var_name;        /* Variable or label name */
        } idt;                           /* For identifier operands */
    };
} Operand;

/* ==================== INSTRUCTION STRUCTURE ==================== */

/**
 * Represents a single assembly instruction or directive
 * Can be a label, instruction, jump, or variable declaration
 */
typedef struct
{
    enum
    {
        INST_LABEL,      /* Label definition (e.g., start:) */
        INST_INSTRUCTION, /* Regular instruction (e.g., MOV, ADD) */
        INST_JUMP,       /* Jump instruction (e.g., JMP, JZ) */
        INST_VARIABLE    /* Variable declaration (e.g., var: DB 1) */
    } type;
    int offset;          /* Memory offset where this instruction will be placed */
    int size;            /* Size of the instruction in bytes */
    union
    {
        struct{
            char* label;  /* Label name */
        } label;
        struct 
        {   
            char* keyword;  /* Instruction mnemonic */
            Operand op1;    /* First operand */
            Operand op2;    /* Second operand */
        } instruction;
        struct
        {
            char* keyword;      /* Jump instruction mnemonic */
            char* label;        /* Target label name */
            int* label_offset;  /* Pointer to target label's offset */
        } jmp;
        struct
        {
            int is_constant;        /* Whether this is a constant value */
            int64_t constant;       /* Constant value if applicable */
            const char* var_name;   /* Variable name */
            char* contents;         /* Variable data contents */
        } var;
    } val;
} Instruction;

/* ==================== INSTRUCTION MAP ENTRY ==================== */

/**
 * Entry in the instruction handler map
 * Contains function pointers for instruction execution and size calculation
 */
typedef struct {
    int (*handler)(Instruction*);      /* Function to execute instruction */
    int (*size_handler)(Instruction*); /* Function to calculate instruction size */
} InstructionEntry;

/* ==================== ASSEMBLY MODES ==================== */

/**
 * Different sections/modes in assembly code
 */
typedef enum
{
    ASM_TEXT,   /* Code section (.text) */
    ASM_DATA,   /* Data section (.data) */
    ASM_BSS,    /* Uninitialized data section (.bss) */
    ASM_GLOBAL  /* Global symbol declarations */
} ASM_MODE;

/* ==================== GLOBAL VARIABLES ==================== */

extern Vector tokens;                           /* Token list from lexical analysis */
extern Vector instructions;                     /* Instruction list from parsing */
extern InstructionEntry instruction_map[26*26*26]; /* Instruction handler map */
extern FILE* file_out;                          /* Output file handle */
extern int global_offset;                       /* Current memory offset */
extern int offset;                              /* Current token position */
extern ASM_MODE mode;                           /* Current assembly mode */
extern char* begin_label_label;                 /* Name of the BEGIN label */
extern int begin_label_instruction_index;       /* Index of BEGIN label instruction */
extern FILE* file;                              /* Input file handle */

#endif