/*
 * HASM - x86 Assembly Compiler
 * Implementation of core assembler functionality
 * 
 * This file contains:
 * - Global variable definitions
 * - Vector data structure implementation
 * - Instruction map initialization
 */

#include "assembler.h"

/* ==================== GLOBAL VARIABLES ==================== */

Vector tokens;                           /* Token list from lexical analysis */
Vector instructions;                     /* Instruction list from parsing */
InstructionEntry instruction_map[26*26*26] = {0}; /* Instruction handler map - 3-letter hash */
FILE* file_out = 0;                      /* Output file handle */
FILE* file = 0;                          /* Input file handle */
int global_offset = 0;                   /* Current memory offset for code generation */
int offset = 0;                          /* Current token position in parsing */
ASM_MODE mode = ASM_GLOBAL;              /* Current assembly mode/section */
char* begin_label_label = "";            /* Name of the BEGIN label */
int begin_label_instruction_index = -1;  /* Index of BEGIN label instruction */

#include "InstructionHandlers.h"

/* ==================== VECTOR IMPLEMENTATION ==================== */

/**
 * Initialize a vector with the specified initial capacity
 * @param vec Vector to initialize
 * @param capacity Initial capacity for the vector
 */
void vector_init(Vector *vec, size_t capacity) {
    vec->data = malloc(capacity * sizeof(void *));
    vec->size = 0;
    vec->capacity = capacity;
}

/**
 * Add an item to the end of a vector
 * Automatically expands the vector if it's full
 * @param vec Vector to add to
 * @param item Item to add
 */
void vector_push(Vector *vec, void *item) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;  /* Double the capacity when full */
        vec->data = realloc(vec->data, vec->capacity * sizeof(void *));
    }
    vec->data[vec->size++] = item;
}

/**
 * Free all memory associated with a vector
 * Frees both the vector structure and all items it contains
 * @param vec Vector to free
 */
void vector_free(Vector *vec) {
    for (size_t i = 0; i < vec->size; i++) free(vec->data[i]);  /* Free all items */
    free(vec->data);  /* Free the data array */
}

#include "InstructionHandlers.h"

/* ==================== INSTRUCTION MAP INITIALIZATION ==================== */

/**
 * Initialize the instruction handler map
 * Maps 3-letter instruction mnemonics to their handler functions
 * Uses a hash function based on the first 3 characters
 */
void init_instruction_map()
{
    memset(instruction_map, 0, sizeof(instruction_map));

    char* opcode_str = "";
    
    /* Macro to add an instruction to the map */
    #define ADD_INSTR(opcode) \
        opcode_str = #opcode; \
        instruction_map[abs(((opcode_str[0] - 'A') % 26) + ((opcode_str[1] - 'A') % 26) * 26 + ((opcode_str[2] - 'A') % 26) * 26 * 26)] = (InstructionEntry){opcode##_handler, opcode##_size_handler};

    /* Arithmetic and logical instructions */
    ADD_INSTR(SUB);   /* Subtraction */
    ADD_INSTR(MOV);   /* Move data */
    ADD_INSTR(OR);    /* Bitwise OR */
    ADD_INSTR(ADC);   /* Add with carry */
    ADD_INSTR(SBB);   /* Subtract with borrow */
    ADD_INSTR(AND);   /* Bitwise AND */
    ADD_INSTR(XOR);   /* Bitwise XOR */
    ADD_INSTR(CMP);   /* Compare */
    ADD_INSTR(ADD);   /* Addition */
    ADD_INSTR(MUL);   /* Unsigned multiplication */
    ADD_INSTR(IMUL);  /* Signed multiplication */
    ADD_INSTR(DIV);   /* Unsigned division */
    ADD_INSTR(IDIV);  /* Signed division */
    ADD_INSTR(NOT);   /* Bitwise NOT */
    ADD_INSTR(NEG);   /* Negate */
    ADD_INSTR(INC);   /* Increment */
    ADD_INSTR(DEC);   /* Decrement */
    ADD_INSTR(TEST);  /* Test bits */

    /* Conditional jump instructions */
    ADD_INSTR(JO);    /* Jump if overflow */
    ADD_INSTR(JNO);   /* Jump if not overflow */
    ADD_INSTR(JB);    /* Jump if below (unsigned) */
    ADD_INSTR(JAE);   /* Jump if above or equal (unsigned) */
    ADD_INSTR(JE);    /* Jump if equal */
    ADD_INSTR(JNE);   /* Jump if not equal */
    ADD_INSTR(JBE);   /* Jump if below or equal (unsigned) */
    ADD_INSTR(JA);    /* Jump if above (unsigned) */
    ADD_INSTR(JS);    /* Jump if sign */
    ADD_INSTR(JNS);   /* Jump if not sign */
    ADD_INSTR(JP);    /* Jump if parity */
    ADD_INSTR(JNP);   /* Jump if not parity */
    ADD_INSTR(JL);    /* Jump if less (signed) */
    ADD_INSTR(JGE);   /* Jump if greater or equal (signed) */
    ADD_INSTR(JLE);   /* Jump if less or equal (signed) */
    ADD_INSTR(JG);    /* Jump if greater (signed) */
    ADD_INSTR(JMP);   /* Unconditional jump */

    /* System and control instructions */
    ADD_INSTR(INT);   /* Interrupt */
    ADD_INSTR(NOP);   /* No operation */
    ADD_INSTR(SYSCALL); /* System call */
    ADD_INSTR(LEA);   /* Load effective address */
    ADD_INSTR(PUSH);  /* Push to stack */
    ADD_INSTR(POP);   /* Pop from stack */
    ADD_INSTR(WAIT);  /* Wait */
    ADD_INSTR(RET);   /* Return */
    ADD_INSTR(CALL);  /* Call subroutine */

    #undef ADD_INSTR
}
