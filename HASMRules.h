#pragma once

// https://www.felixcloutier.com/x86/

#include "CompilerBuilder.h"
#include "elf.h"


long beggining_offset = 0;
char* beggining_label = 0;

#define COMPILER HASM
createCompilerH(
    tokens(
        token(ADC, "^ADC")
        token(SBB, "^SBB")
        token(LEA, "^LEA")
        token(CALL, "^CALL")
        token(JMP, "^JMP")
        token(XCHG, "^XCHG")
        token(TEST, "^TEST")

        token(SECTION, "^SECTION")
        token(GLOBAL, "^GLOBAL")
        token(SECTION_TEXT, "^\\.text")
        token(SECTION_DATA, "^\\.data")
        token(SYSCALL, "^SYSCALL")
        token(BYTE, "^BYTE")
        token(WORD, "^WORD")
        token(DWORD, "^DWORD")
        token(QWORD, "^QWORD")
        token(JO, "^JO")
        token(JNO, "^JNO")
        token(JBE, "^JBE")
        token(JB, "^JB")
        token(JAE, "^JAE")
        token(JNE, "^JNE")
        token(JE, "^JE")
        token(JA, "^JA")
        token(JS, "^JS")
        token(JNS, "^JNS")
        token(JP, "^JP")
        token(JNP, "^JNP")
        token(JLE, "^JLE")
        token(JL, "^JL")
        token(JGE, "^JGE")
        token(JG, "^JG")
        token(WAIT, "^WAIT")
        token(NOP, "^NOP")
        token(RET, "^RET")
        token(INT, "^INT")
        token(POP, "^POP")
        token(PUSH, "^PUSH")
        token(MOV, "^MOV")
        token(ADD, "^ADD")
        token(SUB, "^SUB")
        token(OR, "^OR")
        token(AND, "^AND")
        token(CMP, "^CMP")
        token(XOR, "^XOR")
        token(IMUL, "^IMUL")
        token(IDIV, "^IDIV")
        token(NOT, "^NOT")
        token(NEG, "^NEG")
        token(INC, "^INC")
        token(DEC, "^DEC")
        token(MUL, "^MUL")
        token(DIV, "^DIV")
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
        token(DB, "^DB")
        token(DW, "^DW")
        token(DD, "^DD")
        token(DQ, "^DQ")
        token(OPEN_BRACK, "^\\[")
        token(CLOSE_BRACK, "^\\]")
        token(PLUS, "^\\+")
        token(MINUS, "^\\-")
        token(COLON, "^\\:")
        token(MULTIPLY, "^\\*")
        token(IDENTIFIER, "^[a-zA-Z_][a-zA-Z0-9_]*")
        token(HEX_LITERAL, "^0x[0-9A-Za-z_]*")
        token(NUMBER_LITERAL, "^[0-9]+")
        token(STRING_LITERAL, "^\"[^\"]*\"")
        token(CHAR_LITERAL, "^'.'")
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
            Global,
            Section_Data,
            Section_Text
        )
    )
    node(Section_Data
        all_rule(
            SECTION,
            SECTION_DATA,
            Section_Data_Statement
        )
    )
    node(Section_Text
        all_rule(
            SECTION,
            SECTION_TEXT,
            Section_Text_Statement
        )
    )
    node(Global
        all_rule(
            GLOBAL,
            IDENTIFIER
        )
        var(Elf64_Ehdr, ehdr)
        var(Elf64_Phdr, phdr)
    )
    nodeNext(Section_Text_Statement
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

            jmp_r_instruction,
            jmp_indirect_instruction,
            jmp_index_instruction,
            jmp_scaled_instruction,
            jmp_complex_instruction,
            jmp_offset_instruction,

            pp_r_instruction,
            pp_indirect_instruction,
            pp_index_instruction,
            pp_scaled_instruction,
            pp_complex_instruction,
            pp_offset_instruction,
            Label,
            jump_label,
            jmp_label,
            syscall_instruction,
            NOP_instruction,
            RET_instruction,
            INT_instruction,
            call_label,
            WAIT_instruction
        )
    )
    nodeNext(Section_Data_Statement
        any_rule(
            Variable
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
            XCHG,
            TEST
        )
        var(unsigned char, r)
        var(unsigned char, imm)
    )
    node(Multi_Purpose_instruction_no_xchg
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
    node(Multi_Purpose_instruction_w_lea
        any_rule(
            Multi_Purpose_instruction,
            LEA
        )
        var(unsigned char, r)
        var(unsigned char, imm)
    )
    node(Jump_instruction
        any_rule(
            JO,
            JNO,
            JB,
            JAE,
            JE,
            JNE,
            JBE,
            JA,
            JS,
            JNS,
            JP,
            JNP,
            JL,
            JGE,
            JLE,
            JG
        )
        var(unsigned char, instruction)
        var(long, ptr)
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
    node(Hex_Identifier
        any_rule(
            IDENTIFIER,
            HEX_LITERAL
        )
        var(long, value)
    )
    node(MOV_r_imm_instruction
        all_rule(
            Multi_Purpose_instruction_no_xchg,
            Register,
            Hex_Identifier
        )
    )
    node(MOV_r_direct_instruction
        all_rule(
            Multi_Purpose_instruction_w_lea,
            Register,
            OPEN_BRACK,
            HEX_LITERAL,
            CLOSE_BRACK
        )
    )
    node(MOV_r_indirect_instruction
        all_rule(
            Multi_Purpose_instruction_w_lea,
            Register,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK
        )
    )
    node(MOV_r_offset_instruction
        all_rule(
            Multi_Purpose_instruction_w_lea,
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
            Multi_Purpose_instruction_w_lea,
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
            Multi_Purpose_instruction_w_lea,
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
            Multi_Purpose_instruction_w_lea,
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
    node(jump_label
        all_rule(
            Jump_instruction,
            IDENTIFIER
        )
        var(long, ptr)
    )
    node(syscall_instruction
        all_rule(
            SYSCALL
        )
    )
    node(Directive
        any_rule(
            DB,
            DW,
            DD,
            DQ
        )
        var(int, size)
    )
    node(Variable
        all_rule(
            IDENTIFIER,
            Directive,
            Variable_Value
        )
    )
    node(Variable_Value
        any_rule(
            Variable_Value_DB,
            Variable_Value_DW,
            Variable_Value_DD,
            Variable_Value_DQ
        )
    )
    nodeNext(Variable_Value_DB
        any_rule(
            STRING_LITERAL,
            CHAR_LITERAL,
            NUMBER_LITERAL,
            HEX_LITERAL
        )
    )
    nodeNext(Variable_Value_DW
        any_rule(
            STRING_LITERAL,
            CHAR_LITERAL,
            NUMBER_LITERAL,
            HEX_LITERAL
        )
    )
    nodeNext(Variable_Value_DD
        any_rule(
            STRING_LITERAL,
            CHAR_LITERAL,
            NUMBER_LITERAL,
            HEX_LITERAL
        )
    )
    nodeNext(Variable_Value_DQ
        any_rule(
            STRING_LITERAL,
            CHAR_LITERAL,
            NUMBER_LITERAL,
            HEX_LITERAL
        )
    )

    node(NOP_instruction
        any_rule(
            NOP
        )
    )

    node(RET_instruction
        any_rule(
            RET
        )
    )

    node(INT_instruction
        all_rule(
            INT,
            HEX_LITERAL
        )
    )

    node(WAIT_instruction
        any_rule(
            WAIT
        )
    )


    node(jmp_register
        any_rule(
            Register16,
            Register64
        )
    )
    node(jmp_r_instruction
        all_rule(
            JMP,
            Register
        )
    )
    node(jmp_indirect_instruction
        all_rule(
            JMP,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK
        )
    )
    node(jmp_index_instruction
        all_rule(
            JMP,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            CLOSE_BRACK
        )
    )
    node(jmp_scaled_instruction
        all_rule(
            JMP,
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
    node(jmp_complex_instruction
        all_rule(
            JMP,
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
    node(jmp_offset_instruction
        all_rule(
            JMP,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK
        )
    )
    node(jmp_label
        all_rule(
            JMP,
            IDENTIFIER
        )
        var(long, ptr)
    )
    node(call_label
        all_rule(
            CALL,
            IDENTIFIER
        )
        var(long, ptr)
    )


    iterationStep(semantics)
    iterationStep(codegen)
    iterationStep(label_resolution)
)
