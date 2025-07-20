/*
 * HASM - x86 Assembly Compiler
 * Instruction Handler Function Declarations
 * 
 * This file declares all the instruction handler functions used by the assembler.
 * Each instruction has two handlers:
 * - *_handler: Generates the machine code for the instruction
 * - *_size_handler: Calculates the size of the instruction in bytes
 */

#ifndef InstructionHandlers_H
#define InstructionHandlers_H

#include "assembler.h"

/* ==================== DATA MOVEMENT INSTRUCTIONS ==================== */

/* MOV - Move data between registers, memory, and immediate values */
int MOV_handler(Instruction* instr);
int MOV_size_handler(Instruction* instr);

/* ==================== ARITHMETIC INSTRUCTIONS ==================== */

/* SUB - Subtract second operand from first operand */
int SUB_handler(Instruction* instr);
int SUB_size_handler(Instruction* instr);

/* ADD - Add two operands together */
int ADD_handler(Instruction* instr);
int ADD_size_handler(Instruction* instr);

/* ==================== LOGICAL INSTRUCTIONS ==================== */

/* OR - Bitwise OR operation */
int OR_handler(Instruction* instr);
int OR_size_handler(Instruction* instr);

/* ADC - Add with carry flag */
int ADC_handler(Instruction* instr);
int ADC_size_handler(Instruction* instr);

/* SBB - Subtract with borrow flag */
int SBB_handler(Instruction* instr);
int SBB_size_handler(Instruction* instr);

/* AND - Bitwise AND operation */
int AND_handler(Instruction* instr);
int AND_size_handler(Instruction* instr);

/* XOR - Bitwise XOR operation */
int XOR_handler(Instruction* instr);
int XOR_size_handler(Instruction* instr);

/* CMP - Compare two operands (sets flags) */
int CMP_handler(Instruction* instr);
int CMP_size_handler(Instruction* instr);

/* ==================== MULTIPLICATION AND DIVISION ==================== */

/* MUL - Unsigned multiplication */
int MUL_handler(Instruction* instr);
int MUL_size_handler(Instruction* instr);

/* IMUL - Signed multiplication */
int IMUL_handler(Instruction* instr);
int IMUL_size_handler(Instruction* instr);

/* DIV - Unsigned division */
int DIV_handler(Instruction* instr);
int DIV_size_handler(Instruction* instr);

/* IDIV - Signed division */
int IDIV_handler(Instruction* instr);
int IDIV_size_handler(Instruction* instr);

/* ==================== UNARY OPERATIONS ==================== */

/* NOT - Bitwise NOT (one's complement) */
int NOT_handler(Instruction* instr);
int NOT_size_handler(Instruction* instr);

/* NEG - Negate (two's complement) */
int NEG_handler(Instruction* instr);
int NEG_size_handler(Instruction* instr);

/* INC - Increment operand by 1 */
int INC_handler(Instruction* instr);
int INC_size_handler(Instruction* instr);

/* DEC - Decrement operand by 1 */
int DEC_handler(Instruction* instr);
int DEC_size_handler(Instruction* instr);

/* TEST - Test bits (sets flags like AND but doesn't store result) */
int TEST_handler(Instruction* instr);
int TEST_size_handler(Instruction* instr);

/* ==================== CONDITIONAL JUMP INSTRUCTIONS ==================== */

/* JO - Jump if overflow flag is set */
int JO_handler(Instruction* instr);
int JO_size_handler(Instruction* instr);

/* JNO - Jump if overflow flag is clear */
int JNO_handler(Instruction* instr);
int JNO_size_handler(Instruction* instr);

/* JB - Jump if below (unsigned comparison) */
int JB_handler(Instruction* instr);
int JB_size_handler(Instruction* instr);

/* JAE - Jump if above or equal (unsigned comparison) */
int JAE_handler(Instruction* instr);
int JAE_size_handler(Instruction* instr);

/* JE - Jump if equal (zero flag set) */
int JE_handler(Instruction* instr);
int JE_size_handler(Instruction* instr);

/* JNE - Jump if not equal (zero flag clear) */
int JNE_handler(Instruction* instr);
int JNE_size_handler(Instruction* instr);

/* JBE - Jump if below or equal (unsigned comparison) */
int JBE_handler(Instruction* instr);
int JBE_size_handler(Instruction* instr);

/* JA - Jump if above (unsigned comparison) */
int JA_handler(Instruction* instr);
int JA_size_handler(Instruction* instr);

/* JS - Jump if sign flag is set (negative) */
int JS_handler(Instruction* instr);
int JS_size_handler(Instruction* instr);

/* JNS - Jump if sign flag is clear (non-negative) */
int JNS_handler(Instruction* instr);
int JNS_size_handler(Instruction* instr);

/* JP - Jump if parity flag is set (even number of 1 bits) */
int JP_handler(Instruction* instr);
int JP_size_handler(Instruction* instr);

/* JNP - Jump if parity flag is clear (odd number of 1 bits) */
int JNP_handler(Instruction* instr);
int JNP_size_handler(Instruction* instr);

/* JL - Jump if less (signed comparison) */
int JL_handler(Instruction* instr);
int JL_size_handler(Instruction* instr);

/* JGE - Jump if greater or equal (signed comparison) */
int JGE_handler(Instruction* instr);
int JGE_size_handler(Instruction* instr);

/* JLE - Jump if less or equal (signed comparison) */
int JLE_handler(Instruction* instr);
int JLE_size_handler(Instruction* instr);

/* JG - Jump if greater (signed comparison) */
int JG_handler(Instruction* instr);
int JG_size_handler(Instruction* instr);

/* ==================== UNCONDITIONAL JUMP ==================== */

/* JMP - Unconditional jump */
int JMP_handler(Instruction* instr);
int JMP_size_handler(Instruction* instr);

/* ==================== SYSTEM INSTRUCTIONS ==================== */

/* INT - Software interrupt */
int INT_handler(Instruction* instr);
int INT_size_handler(Instruction* instr);

/* NOP - No operation (does nothing) */
int NOP_handler(Instruction* instr);
int NOP_size_handler(Instruction* instr);

/* SYSCALL - System call (Linux x86_64) */
int SYSCALL_handler(Instruction* instr);
int SYSCALL_size_handler(Instruction* instr);

/* ==================== ADDRESS CALCULATION ==================== */

/* LEA - Load effective address (calculate address without accessing memory) */
int LEA_handler(Instruction* instr);
int LEA_size_handler(Instruction* instr);

/* ==================== STACK OPERATIONS ==================== */

/* PUSH - Push value onto stack */
int PUSH_handler(Instruction* instr);
int PUSH_size_handler(Instruction* instr);

/* POP - Pop value from stack */
int POP_handler(Instruction* instr);
int POP_size_handler(Instruction* instr);

/* ==================== CONTROL FLOW ==================== */

/* WAIT - Wait for floating point operations to complete */
int WAIT_handler(Instruction* instr);
int WAIT_size_handler(Instruction* instr);

/* RET - Return from subroutine */
int RET_handler(Instruction* instr);
int RET_size_handler(Instruction* instr);

/* CALL - Call subroutine */
int CALL_handler(Instruction* instr);
int CALL_size_handler(Instruction* instr);

#endif