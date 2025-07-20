/*
 * HASM - x86 Assembly Compiler
 * Instruction Handler Implementations
 * 
 * This file contains the actual implementations of all instruction handlers.
 * Each instruction has two functions:
 * - *_handler: Generates the machine code bytes for the instruction
 * - *_size_handler: Calculates the instruction size and parses operands
 */

#include "InstructionHandlers.h"
#include "Instructions.h"
#include "assembler.h"

/* ==================== DATA MOVEMENT INSTRUCTIONS ==================== */

/* MOV - Move data between registers, memory, and immediate values */
int MOV_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x89, 0, 0);    }
int MOV_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x89);          }

/* ==================== ARITHMETIC INSTRUCTIONS ==================== */

/* SUB - Subtract second operand from first operand */
int SUB_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x29, 0x2D, 5); }
int SUB_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x29);          }

/* ADD - Add two operands together */
int ADD_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x01, 0x05, 0); }
int ADD_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x01);          }

/* ==================== LOGICAL INSTRUCTIONS ==================== */

/* OR - Bitwise OR operation */
int OR_handler          (Instruction* instr){ return multi_purpose_instruction        (instr, 0x09, 0x0D, 1); }
int OR_size_handler     (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x09);          }

/* ADC - Add with carry flag */
int ADC_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x11, 0x15, 2); }
int ADC_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x11);          }

/* SBB - Subtract with borrow flag */
int SBB_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x19, 0x1D, 3); }
int SBB_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x19);          }

/* AND - Bitwise AND operation */
int AND_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x21, 0x25, 4); }
int AND_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x21);          }

/* XOR - Bitwise XOR operation */
int XOR_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x31, 0x35, 6); }
int XOR_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x31);          }

/* CMP - Compare two operands (sets flags) */
int CMP_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x39, 0x3D, 7); }
int CMP_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x39);          }

/* ==================== MULTIPLICATION AND DIVISION ==================== */

/* MUL - Unsigned multiplication */
int MUL_handler         (Instruction* instr){ return unary_instructions               (instr, 0xF7, 4);       }
int MUL_size_handler    (Instruction* instr){ return unary_instructions_size          (instr, 0xF7, 1);       }

/* IMUL - Signed multiplication */
int IMUL_handler        (Instruction* instr){ return unary_instructions               (instr, 0xF7, 5);       }
int IMUL_size_handler   (Instruction* instr){ return unary_instructions_size          (instr, 0xF7, 1);       }

/* DIV - Unsigned division */
int DIV_handler         (Instruction* instr){ return unary_instructions               (instr, 0xF7, 6);       }
int DIV_size_handler    (Instruction* instr){ return unary_instructions_size          (instr, 0xF7, 1);       }

/* IDIV - Signed division */
int IDIV_handler        (Instruction* instr){ return unary_instructions               (instr, 0xF7, 7);       }
int IDIV_size_handler   (Instruction* instr){ return unary_instructions_size          (instr, 0xF7, 1);       }

/* ==================== UNARY OPERATIONS ==================== */

/* NOT - Bitwise NOT (one's complement) */
int NOT_handler         (Instruction* instr){ return unary_instructions               (instr, 0xF7, 2);       }
int NOT_size_handler    (Instruction* instr){ return unary_instructions_size          (instr, 0xF7, 1);       }

/* NEG - Negate (two's complement) */
int NEG_handler         (Instruction* instr){ return unary_instructions               (instr, 0xF7, 3);       } 
int NEG_size_handler    (Instruction* instr){ return unary_instructions_size          (instr, 0xF7, 1);       }

/* INC - Increment operand by 1 */
int INC_handler         (Instruction* instr){ return unary_instructions               (instr, 0xFF, 0);       }
int INC_size_handler    (Instruction* instr){ return unary_instructions_size          (instr, 0xFF, 1);       }

/* DEC - Decrement operand by 1 */
int DEC_handler         (Instruction* instr){ return unary_instructions               (instr, 0xFF, 1);       }
int DEC_size_handler    (Instruction* instr){ return unary_instructions_size          (instr, 0xFF, 1);       }

/* TEST - Test bits (sets flags like AND but doesn't store result) */
int TEST_handler        (Instruction* instr){ return multi_purpose_instruction        (instr, 0x85, 0xA9, 0); }
int TEST_size_handler   (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x85);          }

/* ==================== CONDITIONAL JUMP INSTRUCTIONS ==================== */

/* JO - Jump if overflow flag is set */
int JO_handler          (Instruction* instr){ return jump_instruction                 (instr, 0);             }
int JO_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JNO - Jump if overflow flag is clear */
int JNO_handler         (Instruction* instr){ return jump_instruction                 (instr, 1);             }
int JNO_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JB - Jump if below (unsigned comparison) */
int JB_handler          (Instruction* instr){ return jump_instruction                 (instr, 2);             }
int JB_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JAE - Jump if above or equal (unsigned comparison) */
int JAE_handler         (Instruction* instr){ return jump_instruction                 (instr, 3);             }
int JAE_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JE - Jump if equal (zero flag set) */
int JE_handler          (Instruction* instr){ return jump_instruction                 (instr, 4);             }
int JE_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JNE - Jump if not equal (zero flag clear) */
int JNE_handler         (Instruction* instr){ return jump_instruction                 (instr, 5);             }
int JNE_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JBE - Jump if below or equal (unsigned comparison) */
int JBE_handler         (Instruction* instr){ return jump_instruction                 (instr, 6);             }
int JBE_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JA - Jump if above (unsigned comparison) */
int JA_handler          (Instruction* instr){ return jump_instruction                 (instr, 7);             }
int JA_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JS - Jump if sign flag is set (negative) */
int JS_handler          (Instruction* instr){ return jump_instruction                 (instr, 8);             }
int JS_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JNS - Jump if sign flag is clear (non-negative) */
int JNS_handler         (Instruction* instr){ return jump_instruction                 (instr, 9);             }
int JNS_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JP - Jump if parity flag is set (even number of 1 bits) */
int JP_handler          (Instruction* instr){ return jump_instruction                 (instr, 10);            }
int JP_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JNP - Jump if parity flag is clear (odd number of 1 bits) */
int JNP_handler         (Instruction* instr){ return jump_instruction                 (instr, 11);            }
int JNP_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JL - Jump if less (signed comparison) */
int JL_handler          (Instruction* instr){ return jump_instruction                 (instr, 12);            }
int JL_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JGE - Jump if greater or equal (signed comparison) */
int JGE_handler         (Instruction* instr){ return jump_instruction                 (instr, 13);            }
int JGE_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JLE - Jump if less or equal (signed comparison) */
int JLE_handler         (Instruction* instr){ return jump_instruction                 (instr, 14);            }
int JLE_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }

/* JG - Jump if greater (signed comparison) */
int JG_handler          (Instruction* instr){ return jump_instruction                 (instr, 15);            }
int JG_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }

/* ==================== ADDRESS CALCULATION ==================== */

/* LEA - Load effective address (calculate address without accessing memory) */
int LEA_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x8D, 0, 0);    }
int LEA_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x8D);          }

/* ==================== STACK OPERATIONS ==================== */

/* PUSH - Push value onto stack */
int PUSH_handler        (Instruction* instr){ return push_pop_instruction             (instr, 0x50);          }
int PUSH_size_handler   (Instruction* instr){ return push_pop_instruction_size        (instr);                }

/* POP - Pop value from stack */
int POP_handler         (Instruction* instr){ return push_pop_instruction             (instr, 0x58);          }
int POP_size_handler    (Instruction* instr){ return push_pop_instruction_size        (instr);                }

/* ==================== SYSTEM INSTRUCTIONS ==================== */

/**
 * INT - Software interrupt
 * Generates the INT instruction bytes: 0xCD followed by the interrupt number
 */
int INT_handler         (Instruction* instr)
{
    fprintf(file_out, "%c%c", 0xCD, (char)instr->val.instruction.op1.immediate);
    return 1;
}

/**
 * INT size handler - Parse interrupt number and calculate size
 */
int INT_size_handler    (Instruction* instr)
{
    instr->type = INST_INSTRUCTION;
    instr->size = 2;  /* INT instruction is always 2 bytes */
    instr->val.instruction.keyword = "INT";
    instr->val.instruction.op1 = find_next_operand(OP_IMM);  /* Parse immediate value */
    offset++;
    return 1;
}

/**
 * NOP - No operation (does nothing)
 * Generates the NOP instruction byte: 0x90
 */
int NOP_handler         (Instruction* instr)
{
    (void)instr;
    fprintf(file_out, "%c", 0x90);
    return 1;
}

/**
 * NOP size handler - NOP is always 1 byte
 */
int NOP_size_handler    (Instruction* instr)
{
    instr->type = INST_INSTRUCTION;
    instr->size = 1;  /* NOP is always 1 byte */
    instr->val.instruction.keyword = "NOP";
    offset++;
    return 1;
}

/**
 * SYSCALL - System call (Linux x86_64)
 * Generates the SYSCALL instruction bytes: 0x0F 0x05
 */
int SYSCALL_handler     (Instruction* instr)
{
    (void)instr;
    fprintf(file_out, "%c%c", 0x0F, 0x05);
    return 1;
}

/**
 * SYSCALL size handler - SYSCALL is always 2 bytes
 */
int SYSCALL_size_handler(Instruction* instr)
{
    instr->type = INST_INSTRUCTION;
    instr->size = 2;  /* SYSCALL is always 2 bytes */
    instr->val.instruction.keyword = "SYSCALL";
    offset++;
    return 1;
}

/**
 * WAIT - Wait for floating point operations to complete
 * Generates the WAIT instruction byte: 0x9B
 */
int WAIT_handler(Instruction* instr)
{
    (void)instr;
    fprintf(file_out, "%c", 0x9B);
    return 1;
}

/**
 * WAIT size handler - WAIT is always 1 byte
 */
int WAIT_size_handler(Instruction* instr)
{
    instr->type = INST_INSTRUCTION;
    instr->size = 1;  /* WAIT is always 1 byte */
    instr->val.instruction.keyword = "WAIT";
    offset++;
    return 1;
}

/**
 * RET - Return from subroutine
 * Generates the RET instruction byte: 0xC3
 */
int RET_handler(Instruction* instr)
{
    (void)instr;
    fprintf(file_out, "%c", 0xC3);
    return 1;
}

/**
 * RET size handler - RET is always 1 byte
 */
int RET_size_handler(Instruction* instr)
{
    instr->type = INST_INSTRUCTION;
    instr->size = 1;  /* RET is always 1 byte */
    instr->val.instruction.keyword = "RET";
    offset++;
    return 1;
}

/**
 * CALL - Call subroutine
 * Resolves label offset and generates CALL instruction with relative address
 */
int CALL_handler(Instruction* instr)
{
    /* Find the target label and get its offset */
    for(int i = 0; i < (int)instructions.size; i++)
    {
        if (INSTRUCTION(i)->type == INST_LABEL && strcmp(INSTRUCTION(i)->val.label.label, instr->val.jmp.label) == 0)
        {
            instr->val.jmp.label_offset = &INSTRUCTION(i)->offset;
            break;
        }
    }
    /* Calculate relative offset for CALL instruction */
    int offset = (*instr->val.jmp.label_offset - instr->offset) - 5;
    fprintf(file_out, "%c", 0xE8);  /* CALL opcode */
    print_signed_integer_as_ascii(4, offset);  /* Write 4-byte relative offset */
    return 1;
}

/**
 * CALL size handler - Parse call target and calculate size
 */
int CALL_size_handler(Instruction* instr)
{
    offset++;
    instr->val.jmp.label = TOKEN(offset)->content;  /* Get target label name */
    offset++;
    instr->type = INST_INSTRUCTION;
    instr->size = 5;  /* CALL is 5 bytes (1 byte opcode + 4 bytes offset) */

    return 1;
}

/**
 * JMP size handler - Calculate size for jump instruction
 * Uses unary instruction size calculation with opcode 0xFF and reg field 4
 */
int JMP_size_handler(Instruction* inst)
{
    return unary_instructions_size(inst, 0xFF, 4);
}

/**
 * JMP - Unconditional jump
 * Uses unary instruction encoding with opcode 0xFF and reg field 4
 */
int JMP_handler(Instruction* inst)
{
    return unary_instructions(inst, 0xFF, 4);
}