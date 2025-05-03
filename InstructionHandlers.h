
#ifndef InstructionHandlers_H
#define InstructionHandlers_H

#include "assembler.h"

int MOV_handler(Instruction* instr);
int MOV_size_handler(Instruction* instr);

int SUB_handler(Instruction* instr);
int SUB_size_handler(Instruction* instr);

int ADD_handler(Instruction* instr);
int ADD_size_handler(Instruction* instr);

int OR_handler(Instruction* instr);
int OR_size_handler(Instruction* instr);

int ADC_handler(Instruction* instr);
int ADC_size_handler(Instruction* instr);

int SBB_handler(Instruction* instr);
int SBB_size_handler(Instruction* instr);

int AND_handler(Instruction* instr);
int AND_size_handler(Instruction* instr);

int XOR_handler(Instruction* instr);
int XOR_size_handler(Instruction* instr);

int CMP_handler(Instruction* instr);
int CMP_size_handler(Instruction* instr);

int MUL_handler(Instruction* instr);
int MUL_size_handler(Instruction* instr);

int IMUL_handler(Instruction* instr);
int IMUL_size_handler(Instruction* instr);

int DIV_handler(Instruction* instr);
int DIV_size_handler(Instruction* instr);

int IDIV_handler(Instruction* instr);
int IDIV_size_handler(Instruction* instr);

int NOT_handler(Instruction* instr);
int NOT_size_handler(Instruction* instr);

int NEG_handler(Instruction* instr);
int NEG_size_handler(Instruction* instr);

int INC_handler(Instruction* instr);
int INC_size_handler(Instruction* instr);

int DEC_handler(Instruction* instr);
int DEC_size_handler(Instruction* instr);

int TEST_handler(Instruction* instr);
int TEST_size_handler(Instruction* instr);

int JO_handler(Instruction* instr);
int JO_size_handler(Instruction* instr);

int JNO_handler(Instruction* instr);
int JNO_size_handler(Instruction* instr);

int JB_handler(Instruction* instr);
int JB_size_handler(Instruction* instr);

int JAE_handler(Instruction* instr);
int JAE_size_handler(Instruction* instr);

int JE_handler(Instruction* instr);
int JE_size_handler(Instruction* instr);

int JNE_handler(Instruction* instr);
int JNE_size_handler(Instruction* instr);

int JBE_handler(Instruction* instr);
int JBE_size_handler(Instruction* instr);

int JA_handler(Instruction* instr);
int JA_size_handler(Instruction* instr);

int JS_handler(Instruction* instr);
int JS_size_handler(Instruction* instr);

int JNS_handler(Instruction* instr);
int JNS_size_handler(Instruction* instr);

int JP_handler(Instruction* instr);
int JP_size_handler(Instruction* instr);

int JNP_handler(Instruction* instr);
int JNP_size_handler(Instruction* instr);

int JL_handler(Instruction* instr);
int JL_size_handler(Instruction* instr);

int JGE_handler(Instruction* instr);
int JGE_size_handler(Instruction* instr);

int JLE_handler(Instruction* instr);
int JLE_size_handler(Instruction* instr);

int JG_handler(Instruction* instr);
int JG_size_handler(Instruction* instr);

int JMP_handler(Instruction* instr);
int JMP_size_handler(Instruction* instr);

int INT_handler(Instruction* instr);
int INT_size_handler(Instruction* instr);

int NOP_handler(Instruction* instr);
int NOP_size_handler(Instruction* instr);

int SYSCALL_handler(Instruction* instr);
int SYSCALL_size_handler(Instruction* instr);

int LEA_handler(Instruction* instr);
int LEA_size_handler(Instruction* instr);

int PUSH_handler(Instruction* instr);
int PUSH_size_handler(Instruction* instr);

int POP_handler(Instruction* instr);
int POP_size_handler(Instruction* instr);

int WAIT_handler(Instruction* instr);
int WAIT_size_handler(Instruction* instr);

int RET_handler(Instruction* instr);
int RET_size_handler(Instruction* instr);

int CALL_handler(Instruction* instr);
int CALL_size_handler(Instruction* instr);

#endif