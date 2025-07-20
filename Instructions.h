/*
 * HASM - x86 Assembly Compiler
 * Instruction Parsing and Encoding Utilities
 * 
 * This file declares utility functions for:
 * - Parsing operands from assembly code
 * - Register lookup and validation
 * - Instruction encoding and size calculation
 * - Number conversion and byte manipulation
 */

#ifndef Instructions_H
#define Instructions_H

#include "assembler.h"

/* ==================== OPERAND PARSING ==================== */

/**
 * Parse the next operand from the token stream
 * @param allowed_operands Bit flags indicating which operand types are allowed
 * @return Parsed operand structure
 */
Operand find_next_operand(int allowed_operands);

/**
 * Look up a register by name and return its structure
 * @param reg Register name (e.g., "RAX", "EAX", "AL")
 * @return Register structure with size and register number
 */
Register find_register(const char* reg);

/* ==================== REGISTER MAP INITIALIZATION ==================== */

/**
 * Initialize the register lookup map
 * Sets up mappings from register names to register numbers and sizes
 */
void init_register_map();

/* ==================== INSTRUCTION ENCODING HELPERS ==================== */

/**
 * Encode unary instructions (one operand)
 * @param inst Instruction structure to encode
 * @param instruction Base opcode for the instruction
 * @param id Additional identifier for register-specific encoding
 * @return 0 on success
 */
int unary_instructions(Instruction* inst, __uint8_t instruction, __uint8_t id);

/**
 * Calculate size of unary instructions
 * @param inst Instruction structure
 * @param instruction Base opcode
 * @param id Additional identifier
 * @return Size in bytes
 */
int unary_instructions_size(Instruction* inst, __uint8_t instruction, __uint8_t id);

/**
 * Encode multi-purpose instructions (two operands)
 * @param inst Instruction structure to encode
 * @param instruction Base opcode
 * @param rax_imm_op Special opcode for RAX + immediate
 * @param id Additional identifier
 * @return 0 on success
 */
int multi_purpose_instruction(Instruction* inst, __uint8_t instruction, __uint8_t rax_imm_op, __uint8_t id);

/**
 * Calculate size of multi-purpose instructions
 * @param inst Instruction structure
 * @param instruction Base opcode
 * @return Size in bytes
 */
int multi_purpose_instruction_size(Instruction* inst, __uint8_t instruction);

/**
 * Encode jump instructions
 * @param inst Jump instruction structure
 * @param instruction Jump opcode
 * @return 0 on success
 */
int jump_instruction(Instruction* inst, __uint8_t instruction);

/**
 * Calculate size of jump instructions
 * @param inst Jump instruction structure
 * @return Size in bytes (2 for short jumps, 6 for long jumps)
 */
int jump_instruction_size(Instruction* inst);

/**
 * Encode push/pop instructions
 * @param inst Instruction structure
 * @param instruction Push/pop opcode
 * @return 0 on success
 */
int push_pop_instruction(Instruction* inst, __uint8_t instruction);

/**
 * Calculate size of push/pop instructions
 * @param inst Instruction structure
 * @return Size in bytes
 */
int push_pop_instruction_size(Instruction* inst);

/* ==================== NUMBER CONVERSION AND BYTE MANIPULATION ==================== */

/**
 * Convert a string representation of a number to decimal
 * Handles hex (0x), octal (0), and decimal numbers
 * @param input String to convert (modified in place)
 */
void convertToDecimalInPlace(char *input);

/**
 * Convert an integer to little-endian bytes
 * @param value Integer value to convert
 * @param buffer Output buffer for bytes
 * @param numBytes Number of bytes to write
 */
void intToBytes(unsigned long value, char *buffer, size_t numBytes);

/**
 * Print a signed integer as ASCII representation
 * Used for debugging and output formatting
 * @param n_bytes Number of bytes in the integer
 * @param num Integer value to print
 */
void print_signed_integer_as_ascii(int n_bytes, __int64_t num);

/**
 * Write a value in little-endian byte order to the output file
 * @param value Value to write
 * @param byte_count Number of bytes to write
 */
void write_little_endian_bytes(__uint64_t value, size_t byte_count);

/**
 * Generate ModR/M byte for x86 instruction encoding
 * @param mod Mod field (0-3)
 * @param reg Register field (0-7)
 * @param rm R/M field (0-7)
 * @return Combined ModR/M byte
 */
unsigned char get_mod_rm(unsigned char mod, unsigned char reg, unsigned char rm);

#endif