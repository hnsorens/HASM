#ifndef Instructions_H
#define Instructions_H

#include "assembler.h"

Operand find_next_operand(int allowed_operands);
Register find_register(const char* reg);

void init_register_map();
int unary_instructions(Instruction* inst, __uint8_t instruction, __uint8_t id);
int unary_instructions_size(Instruction* inst, __uint8_t instruction, __uint8_t id);
int multi_purpose_instruction(Instruction* inst, __uint8_t instruction, __uint8_t rax_imm_op, __uint8_t id);
int multi_purpose_instruction_size(Instruction* inst, __uint8_t instruction);
int jump_instruction(Instruction* inst, __uint8_t instruction);
int jump_instruction_size(Instruction* inst);
int push_pop_instruction(Instruction* inst, __uint8_t instruction);
int push_pop_instruction_size(Instruction* inst);

void convertToDecimalInPlace(char *input);
void intToBytes(unsigned long value, char *buffer, size_t numBytes);
void print_signed_integer_as_ascii(int n_bytes, __int64_t num);
void write_little_endian_bytes(__uint64_t value, size_t byte_count);
unsigned char get_mod_rm(unsigned char mod, unsigned char reg, unsigned char rm);



#endif