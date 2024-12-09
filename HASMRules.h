#pragma once

#include "CompilerBuilder.h"




#define COMPILER HASM
createCompilerH(
    tokens(
        token(BYTE, "^BYTE")
        token(WORD, "^WORD")
        token(DWORD, "^DWORD")
        token(QWORD, "^QWORD")

        token(ROR, "^ROR")
        token(ROL, "^ROL")
        token(RCL, "^RCL")
        token(RCR, "^RCR")
        token(SHL, "^SHL")
        token(SAL, "^SAL")
        token(SHR, "^SHR")
        token(SAR, "^SAR")
        
        token(POP, "^POP")
        token(PUSH, "^PUSH")
        token(MOV, "^MOV")
        token(ADD, "^ADD")
        token(SUB, "^SUB")
        token(OR, "^OR")
        token(AND, "^AND")
        token(CMP, "^CMP")
        token(ADC, "^ADC")
        token(SBB, "^SBB")
        token(XOR, "^XOR")
        token(TEST, "^TEST")
        token(IMUL, "^IMUL")
        token(IDIV, "^IDIV")
        token(NOT, "^NOT")
        token(NEG, "^NEG")
        token(INC, "^INC")
        token(DEC, "^DEC")
        token(MUL, "^MUL")
        token(DIV, "^DIV")
        token(NOP, "^NOP")
        token(RET, "^RET")
        token(RAX, "^RAX")
        token(EAX, "^EAX")
        token(AX, "^AX")
        token(AL, "^AL")
        token(RBX, "^RBX")
        token(EBX, "^EBX")
        token(BX, "^BX")
        token(BL, "^BL")
        token(RCX, "^RCX")
        token(ECX, "^ECX")
        token(CX, "^CX")
        token(CL, "^CL")
        token(RDX, "^RDX")
        token(EDX, "^EDX")
        token(DX, "^DX")
        token(DL, "^DL")
        token(RSI, "^RSI")
        token(ESI, "^ESI")
        token(SI, "^SI")
        token(RDI, "^RDI")
        token(EDI, "^EDI")
        token(DI, "^DI")
        token(RBP, "^RBP")
        token(EBP, "^EBP")
        token(BP, "^BP")
        token(RSP, "^RSP")
        token(ESP, "^ESP")
        token(SP, "^SP")
        token(AH, "^AH")
        token(CH, "^CH")
        token(DH, "^DH")
        token(BH, "^BH")
        token(R8, "^R8")
        token(R9, "^R9")
        token(R10, "^R10")
        token(R11, "^R11")
        token(R12, "^R12")
        token(R13, "^R13")
        token(R14, "^R14")
        token(R15, "^R15")
        token(OPEN_BRACK, "^\\[")
        token(CLOSE_BRACK, "^\\]")
        token(PLUS, "^\\+")
        token(MINUS, "^\\-")
        token(COLON, "^\\:")
        token(MULTIPLY, "^\\*")
        token(IDENTIFIER, "^[a-zA-Z_][a-zA-Z0-9_]*")
        token(HEX_LITERAL, "^0x[0-9A-Za-z_]*")
        token(NUMBER_LITERAL, "^[0-9]+")
        token(WHITESPACE, "\\s+")
    )
    ignoreTokens(
        WHITESPACE
    )
    node(Root
        all_rule(
            Statement
        )
    )
    nodeNext(Statement
        any_rule(

            MOV_r_r_instruction,
            MOV_r_imm_instruction,
            MOV_r_direct_instruction,
            MOV_r_indirect_instruction,
            MOV_r_offset_instruction,
            MOV_r_indexed_instruction,
            MOV_r_scaled_instruction,
            MOV_r_complex_instruction,
            MOV_direct_r_instruction,
            MOV_indirect_r_instruction,
            MOV_offset_r_instruction,
            MOV_indexed_r_instruction,
            MOV_scaled_r_instruction,
            MOV_complex_r_instruction,

            r_instruction,
            indirect_instruction,
            index_instruction,
            scaled_instruction,
            complex_instruction,
            offset_instruction,
            
            pp_r_instruction,
            pp_indirect_instruction,
            pp_index_instruction,
            pp_scaled_instruction,
            pp_complex_instruction,
            pp_offset_instruction,

            bitwise_hex_r_instruction,
            bitwise_hex_indirect_instruction,
            bitwise_hex_index_instruction,
            bitwise_hex_scaled_instruction,
            bitwise_hex_complex_instruction,
            bitwise_hex_offset_instruction,

            bitwise_cl_r_instruction,
            bitwise_cl_indirect_instruction,
            bitwise_cl_index_instruction,
            bitwise_cl_scaled_instruction,
            bitwise_cl_complex_instruction,
            bitwise_cl_offset_instruction,
            RET_instruction,
            NOP_instruction,
            Label
        )
    )
    node(NOP_instruction
        all_rule(
            NOP
        )
    )
    node(RET_instruction
        all_rule(
            RET
        )
    )
    node(Plus_Minus
        any_rule(
            PLUS,
            MINUS
        )
        var(int, val)
    )
    node(Label
        all_rule(
            IDENTIFIER,
            COLON
        )
        var(int, ptr)
        var(char*, value)
    )
    node(Register64
        any_rule(
            RAX,
            RCX,
            RDX,
            RBX,
            RSP,
            RBP,
            RSI,
            RDI
        )
        var(int, reg_value)
    )
    node(Register32
        any_rule(
            EAX,
            ECX,
            EDX,
            EBX,
            ESP,
            EBP,
            ESI,
            EDI
        )
        var(int, reg_value)
    )
    node(Register16
        any_rule(
            AX,
            CX,
            DX,
            BX,
            SP,
            BP,
            SI,
            DI
        )
        var(int, reg_value)
    )
    node(Register8
        any_rule(
            AL,
            CL,
            DL,
            BL,
            AH,
            CH,
            DH,
            BH
        )
        var(int, reg_value)
    )
    node(Register
        any_rule(
            Register8,
            Register16,
            Register32,
            Register64
        )
        var(unsigned char, reg_value)
        var(int, reg_size)
    )
    node(Multi_Purpose_instruction
        any_rule(
            MOV,
            ADD,
            SUB,
            OR,
            AND,
            CMP,
            ADC,
            SBB,
            XOR,
            TEST
        )
        var(unsigned char, r)
        var(unsigned char, imm)
    )
    node(Bitwise_instruction
        any_rule(
            ROL,
            ROR,
            RCL,
            RCR,
            SHL,
            SAL,
            SHR,
            SAR
        )
        var(unsigned char, instruction)
        var(unsigned char, group)
    )
    node(Miscellaneous_Arithmetic_instruction
        any_rule(
            MUL,
            IMUL,
            DIV,
            IDIV,
            NOT,
            NEG
        )
        var(unsigned char, instruction)
        var(unsigned char, group)
    )
    node(Inc_Dec_instruction
        any_rule(
            INC,
            DEC
        )
        var(unsigned char, instruction)
        var(unsigned char, group)
    )
    node(Push_Pop_instruction
        any_rule(
            PUSH,
            POP
        )
        var(unsigned char, instruction)
        var(unsigned char, group)
    )
    node(unary_instruction
        any_rule(
            Miscellaneous_Arithmetic_instruction,
            Inc_Dec_instruction
        )
        var(unsigned char, instruction)
        var(unsigned char, group)
    )
    node(Size_Specifier
        any_rule(
            BYTE,
            WORD,
            DWORD,
            QWORD
        )
        var(int, size)
    )
    node(MOV_r_r_instruction
        all_rule(
            Multi_Purpose_instruction,
            Register,
            Register
        )
    )
    node(MOV_r_imm_instruction
        all_rule(
            Multi_Purpose_instruction,
            Register,
            HEX_LITERAL
        )
    )
    node(MOV_r_direct_instruction
        all_rule(
            Multi_Purpose_instruction,
            Register,
            OPEN_BRACK,
            HEX_LITERAL,
            CLOSE_BRACK
        )
    )
    node(MOV_r_indirect_instruction
        all_rule(
            Multi_Purpose_instruction,
            Register,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK
        )
    )
    node(MOV_r_offset_instruction
        all_rule(
             Multi_Purpose_instruction,
            Register,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK
        )
    )
    node(MOV_r_indexed_instruction
        all_rule(
            Multi_Purpose_instruction,
            Register,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            CLOSE_BRACK
        )
    )
    node(MOV_r_scaled_instruction
        all_rule(
            Multi_Purpose_instruction,
            Register,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            NUMBER_LITERAL,
            CLOSE_BRACK
        )
    )
    node(MOV_r_complex_instruction
        all_rule(
            Multi_Purpose_instruction,
            Register,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            NUMBER_LITERAL,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK
        )
    )
    node(MOV_direct_r_instruction
        all_rule(
            Multi_Purpose_instruction,
            OPEN_BRACK,
            HEX_LITERAL,
            CLOSE_BRACK,
            Register
        )
    )
    node(MOV_indirect_r_instruction
        all_rule(
            Multi_Purpose_instruction,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK,
            Register
        )
    )
    node(MOV_offset_r_instruction
        all_rule(
            Multi_Purpose_instruction,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK,
            Register
        )
    )
    node(MOV_indexed_r_instruction
        all_rule(
            Multi_Purpose_instruction,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            CLOSE_BRACK,
            Register
        )
    )
    node(MOV_scaled_r_instruction
        all_rule(
            Multi_Purpose_instruction,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            NUMBER_LITERAL,
            CLOSE_BRACK,
            Register
        )
    )
    node(MOV_complex_r_instruction
        all_rule(
            Multi_Purpose_instruction,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            NUMBER_LITERAL,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK,
            Register
        )
    )
    node(r_instruction
        all_rule(
            unary_instruction,
            Register
        )
    )
    node(indirect_instruction
        all_rule(
            unary_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK
        )
    )
    node(index_instruction
        all_rule(
            unary_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            CLOSE_BRACK
        )
    )
    node(scaled_instruction
        all_rule(
            unary_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            NUMBER_LITERAL,
            CLOSE_BRACK
        )
    )
    node(complex_instruction
        all_rule(
            unary_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            NUMBER_LITERAL,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK
        )
    )
    node(offset_instruction
        all_rule(
            unary_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK
        )
    )
    node(pp_r_instruction
        all_rule(
            Push_Pop_instruction,
            Register
        )
    )
    node(pp_indirect_instruction
        all_rule(
            Push_Pop_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK
        )
    )
    node(pp_index_instruction
        all_rule(
            Push_Pop_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            CLOSE_BRACK
        )
    )
    node(pp_scaled_instruction
        all_rule(
            Push_Pop_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            NUMBER_LITERAL,
            CLOSE_BRACK
        )
    )
    node(pp_complex_instruction
        all_rule(
            Push_Pop_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            NUMBER_LITERAL,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK
        )
    )
    node(pp_offset_instruction
        all_rule(
            Push_Pop_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK
        )
    )
    node(bitwise_hex_r_instruction
        all_rule(
            Bitwise_instruction,
            Register,
            HEX_LITERAL
        )
    )
    node(bitwise_hex_indirect_instruction
        all_rule(
            Bitwise_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK,
            HEX_LITERAL
        )
    )
    node(bitwise_hex_index_instruction
        all_rule(
            Bitwise_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            CLOSE_BRACK,
            HEX_LITERAL
        )
    )
    node(bitwise_hex_scaled_instruction
        all_rule(
            Bitwise_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            NUMBER_LITERAL,
            CLOSE_BRACK,
            HEX_LITERAL
        )
    )
    node(bitwise_hex_complex_instruction
        all_rule(
            Bitwise_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            NUMBER_LITERAL,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK,
            HEX_LITERAL
        )
    )
    node(bitwise_hex_offset_instruction
        all_rule(
            Bitwise_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK,
            HEX_LITERAL
        )
    )
    node(bitwise_cl_r_instruction
        all_rule(
            Bitwise_instruction,
            Register,
            CL
        )
    )
    node(bitwise_cl_indirect_instruction
        all_rule(
            Bitwise_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK,
            CL
        )
    )
    node(bitwise_cl_index_instruction
        all_rule(
            Bitwise_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            CLOSE_BRACK,
            CL
        )
    )
    node(bitwise_cl_scaled_instruction
        all_rule(
            Bitwise_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            NUMBER_LITERAL,
            CLOSE_BRACK,
            CL
        )
    )
    node(bitwise_cl_complex_instruction
        all_rule(
            Bitwise_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            NUMBER_LITERAL,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK,
            CL
        )
    )
    node(bitwise_cl_offset_instruction
        all_rule(
            Bitwise_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK,
            CL
        )
    )
    iterationStep(semantics)
    iterationStep(codegen)
    iterationStep(label_resolution)
)


