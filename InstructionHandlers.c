#include "InstructionHandlers.h"

#include "Instructions.h"

#include "assembler.h"

int MOV_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x89, 0, 0);    }
int MOV_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x89);          }
int SUB_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x29, 0x2D, 5); }
int SUB_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x29);          }
int ADD_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x01, 0x05, 0); }
int ADD_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x01);          }
int OR_handler          (Instruction* instr){ return multi_purpose_instruction        (instr, 0x09, 0x0D, 1); }
int OR_size_handler     (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x09);          }
int ADC_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x11, 0x15, 2); }
int ADC_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x11);          }
int SBB_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x19, 0x1D, 3); }
int SBB_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x19);          }
int AND_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x21, 0x25, 4); }
int AND_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x21);          }
int XOR_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x31, 0x35, 6); }
int XOR_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x31);          }
int CMP_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x39, 0x3D, 7); }
int CMP_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x39);          }
int MUL_handler         (Instruction* instr){ return unary_instructions               (instr, 0xF7, 4);       }
int MUL_size_handler    (Instruction* instr){ return unary_instructions_size          (instr, 0xF7, 1);       }
int IMUL_handler        (Instruction* instr){ return unary_instructions               (instr, 0xF7, 5);       }
int IMUL_size_handler   (Instruction* instr){ return unary_instructions_size          (instr, 0xF7, 1);       }
int DIV_handler         (Instruction* instr){ return unary_instructions               (instr, 0xF7, 6);       }
int DIV_size_handler    (Instruction* instr){ return unary_instructions_size          (instr, 0xF7, 1);       }
int IDIV_handler        (Instruction* instr){ return unary_instructions               (instr, 0xF7, 7);       }
int IDIV_size_handler   (Instruction* instr){ return unary_instructions_size          (instr, 0xF7, 1);       }
int NOT_handler         (Instruction* instr){ return unary_instructions               (instr, 0xF7, 2);       }
int NOT_size_handler    (Instruction* instr){ return unary_instructions_size          (instr, 0xF7, 1);       }
int NEG_handler         (Instruction* instr){ return unary_instructions               (instr, 0xF7, 3);       } 
int NEG_size_handler    (Instruction* instr){ return unary_instructions_size          (instr, 0xF7, 1);       }
int INC_handler         (Instruction* instr){ return unary_instructions               (instr, 0xFF, 0);       }
int INC_size_handler    (Instruction* instr){ return unary_instructions_size          (instr, 0xFF, 1);       }
int DEC_handler         (Instruction* instr){ return unary_instructions               (instr, 0xFF, 1);       }
int DEC_size_handler    (Instruction* instr){ return unary_instructions_size          (instr, 0xFF, 1);       }
int TEST_handler        (Instruction* instr){ return multi_purpose_instruction        (instr, 0x85, 0xA9, 0); }
int TEST_size_handler   (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x85);          }
int JO_handler          (Instruction* instr){ return jump_instruction                 (instr, 0);             }
int JO_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }
int JNO_handler         (Instruction* instr){ return jump_instruction                 (instr, 1);             }
int JNO_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }
int JB_handler          (Instruction* instr){ return jump_instruction                 (instr, 2);             }
int JB_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }
int JAE_handler         (Instruction* instr){ return jump_instruction                 (instr, 3);             }
int JAE_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }
int JE_handler          (Instruction* instr){ return jump_instruction                 (instr, 4);             }
int JE_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }
int JNE_handler         (Instruction* instr){ return jump_instruction                 (instr, 5);             }
int JNE_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }
int JBE_handler         (Instruction* instr){ return jump_instruction                 (instr, 6);             }
int JBE_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }
int JA_handler          (Instruction* instr){ return jump_instruction                 (instr, 7);             }
int JA_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }
int JS_handler          (Instruction* instr){ return jump_instruction                 (instr, 8);             }
int JS_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }
int JNS_handler         (Instruction* instr){ return jump_instruction                 (instr, 9);             }
int JNS_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }
int JP_handler          (Instruction* instr){ return jump_instruction                 (instr, 10);            }
int JP_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }
int JNP_handler         (Instruction* instr){ return jump_instruction                 (instr, 11);            }
int JNP_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }
int JL_handler          (Instruction* instr){ return jump_instruction                 (instr, 12);            }
int JL_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }
int JGE_handler         (Instruction* instr){ return jump_instruction                 (instr, 13);            }
int JGE_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }
int JLE_handler         (Instruction* instr){ return jump_instruction                 (instr, 14);            }
int JLE_size_handler    (Instruction* instr){ return jump_instruction_size            (instr);                }
int JG_handler          (Instruction* instr){ return jump_instruction                 (instr, 15);            }
int JG_size_handler     (Instruction* instr){ return jump_instruction_size            (instr);                }
int LEA_handler         (Instruction* instr){ return multi_purpose_instruction        (instr, 0x8D, 0, 0);    }
int LEA_size_handler    (Instruction* instr){ return multi_purpose_instruction_size   (instr, 0x8D);          }
int PUSH_handler        (Instruction* instr){ return push_pop_instruction             (instr, 0x50);          }
int PUSH_size_handler   (Instruction* instr){ return push_pop_instruction_size        (instr);                }
int POP_handler         (Instruction* instr){ return push_pop_instruction             (instr, 0x58);          }
int POP_size_handler    (Instruction* instr){ return push_pop_instruction_size        (instr);                }


int INT_handler         (Instruction* instr)
{
    fprintf(file_out, "%c%c", 0xCD, (char)instr->val.instruction.op1.immediate);
    return 1;
}

int INT_size_handler    (Instruction* instr)
{
    instr->type = INST_INSTRUCTION;
    instr->size = 2;
    instr->val.instruction.keyword = "INT";
    instr->val.instruction.op1 = find_next_operand(OP_IMM);
    offset++;
    return 1;
}

int NOP_handler         (Instruction* instr)
{
    (void)instr;
    fprintf(file_out, "%c", 0x90);
    return 1;
}

int NOP_size_handler    (Instruction* instr)
{
    instr->type = INST_INSTRUCTION;
    instr->size = 1;
    instr->val.instruction.keyword = "NOP";
    offset++;
    return 1;
}

int SYSCALL_handler     (Instruction* instr)
{
    (void)instr;
    fprintf(file_out, "%c%c", 0x0F, 0x05);
    return 1;
}

int SYSCALL_size_handler(Instruction* instr)
{
    instr->type = INST_INSTRUCTION;
    instr->size = 2;
    instr->val.instruction.keyword = "SYSCALL";
    offset++;
    return 1;
}

int WAIT_handler(Instruction* instr)
{
    (void)instr;
    fprintf(file_out, "%c", 0x9B);
    return 1;
}

int WAIT_size_handler(Instruction* instr)
{
    instr->type = INST_INSTRUCTION;
    instr->size = 1;
    instr->val.instruction.keyword = "WAIT";
    offset++;
    return 1;
}

int RET_handler(Instruction* instr)
{
    (void)instr;
    fprintf(file_out, "%c", 0xC3);
    return 1;
}

int RET_size_handler(Instruction* instr)
{
    instr->type = INST_INSTRUCTION;
    instr->size = 1;
    instr->val.instruction.keyword = "RET";
    offset++;
    return 1;
}

int CALL_handler(Instruction* instr)
{
    for(int i = 0; i < (int)instructions.size; i++)
    {
        if (INSTRUCTION(i)->type == INST_LABEL && strcmp(INSTRUCTION(i)->val.label.label, instr->val.jmp.label) == 0)
        {
            instr->val.jmp.label_offset = &INSTRUCTION(i)->offset;
            break;
        }
    }
    int offset = (*instr->val.jmp.label_offset - instr->offset) - 5;
    fprintf(file_out, "%c", 0xE8);
    print_signed_integer_as_ascii(4, offset);
    return 1;
}

int CALL_size_handler(Instruction* instr)
{
    offset++;
    instr->val.jmp.label = TOKEN(offset)->content;
    offset++;
    instr->type = INST_INSTRUCTION;
    instr->size = 5;

    return 1;
}

int JMP_size_handler(Instruction* inst)
{
    return unary_instructions_size(inst, 0xFF, 4);
}

int JMP_handler(Instruction* inst)
{
    return unary_instructions(inst, 0xFF, 4);
}