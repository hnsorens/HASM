#pragma once

// https://www.felixcloutier.com/x86/

#include "CompilerBuilder.h"
#include "elf.h"


long beggining_offset = 0;
char* beggining_label = 0;

#define COMPILER HASM
createCompiler(
    tokens(
        token(COMMENT, "^;[^\\\n]*")
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
        token(BINARY_LITERAL, "^0b[01]*")
        token(NUMBER_LITERAL, "^[0-9]+")
        token(STRING_LITERAL, "^\"[^\"]*\"")
        token(CHAR_LITERAL, "^'.'")
        token(WHITESPACE, "\\s+")
    )
    ignoreTokens(
        COMMENT,
        WHITESPACE        
    )
    node(imm
        anyRule(
            HEX_LITERAL,
            NUMBER_LITERAL,
            BINARY_LITERAL
        )
        var(long, value)
    )
    node(Root
        allRule(
            Statement
        )
    )
    nodeNext(Statement
        anyRule(
            Global,
            Section_Data,
            Section_Text
        )
    )
    node(Section_Data
        allRule(
            SECTION,
            SECTION_DATA,
            Section_Data_Statement
        )
    )
    node(Section_Text
        allRule(
            SECTION,
            SECTION_TEXT,
            Section_Text_Statement
        )
    )
    node(Global
        allRule(
            GLOBAL,
            IDENTIFIER
        )
        var(Elf64_Ehdr, ehdr)
        var(Elf64_Phdr, phdr)
    )
    nodeNext(Section_Text_Statement
        anyRule(
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
        anyRule(
            Variable
        )
    )
    node(Plus_Minus
        anyRule(
            PLUS,
            MINUS
        )
        var(int, val)
    )
    node(Label
        allRule(
            IDENTIFIER,
            COLON
        )
        var(int, ptr)
        var(char*, value)
    )
    node(Register64
        anyRule(
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
        anyRule(
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
        anyRule(
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
        anyRule(
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
        anyRule(
            Register8,
            Register16,
            Register32,
            Register64
        )
        var(unsigned char, reg_value)
        var(int, reg_size)
    )
    node(Multi_Purpose_instruction
        anyRule(
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
        anyRule(
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
        anyRule(
            Multi_Purpose_instruction,
            LEA
        )
        var(unsigned char, r)
        var(unsigned char, imm)
    )
    node(Jump_instruction
        anyRule(
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
        anyRule(
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
        anyRule(
            INC,
            DEC
        )
        var(unsigned char, instruction)
        var(unsigned char, group)
    )
    node(Push_Pop_instruction
        anyRule(
            PUSH,
            POP
        )
        var(unsigned char, instruction)
        var(unsigned char, group)
    )
    node(unary_instruction
        anyRule(
            Miscellaneous_Arithmetic_instruction,
            Inc_Dec_instruction
        )
        var(unsigned char, instruction)
        var(unsigned char, group)
    )
    node(Size_Specifier
        anyRule(
            BYTE,
            WORD,
            DWORD,
            QWORD
        )
        var(int, size)
    )
    node(MOV_r_r_instruction
        allRule(
            Multi_Purpose_instruction,
            Register,
            Register
        )
    )
    node(IMM_Identifier
        anyRule(
            IDENTIFIER,
            imm
        )
        var(long, value)
    )
    node(MOV_r_imm_instruction
        allRule(
            Multi_Purpose_instruction_no_xchg,
            Register,
            IMM_Identifier
        )
    )
    node(MOV_r_direct_instruction
        allRule(
            Multi_Purpose_instruction_w_lea,
            Register,
            OPEN_BRACK,
            imm,
            CLOSE_BRACK
        )
    )
    node(MOV_r_indirect_instruction
        allRule(
            Multi_Purpose_instruction_w_lea,
            Register,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK
        )
    )
    node(MOV_r_offset_instruction
        allRule(
            Multi_Purpose_instruction_w_lea,
            Register,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            imm,
            CLOSE_BRACK
        )
    )
    node(MOV_r_indexed_instruction
        allRule(
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
        allRule(
            Multi_Purpose_instruction_w_lea,
            Register,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            imm,
            CLOSE_BRACK
        )
    )
    node(MOV_r_complex_instruction
        allRule(
            Multi_Purpose_instruction_w_lea,
            Register,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            imm,
            Plus_Minus,
            imm,
            CLOSE_BRACK
        )
    )
    node(MOV_direct_r_instruction
        allRule(
            Multi_Purpose_instruction,
            OPEN_BRACK,
            imm,
            CLOSE_BRACK,
            Register
        )
    )
    node(MOV_indirect_r_instruction
        allRule(
            Multi_Purpose_instruction,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK,
            Register
        )
    )
    node(MOV_offset_r_instruction
        allRule(
            Multi_Purpose_instruction,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            imm,
            CLOSE_BRACK,
            Register
        )
    )
    node(MOV_indexed_r_instruction
        allRule(
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
        allRule(
            Multi_Purpose_instruction,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            imm,
            CLOSE_BRACK,
            Register
        )
    )
    node(MOV_complex_r_instruction
        allRule(
            Multi_Purpose_instruction,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            imm,
            Plus_Minus,
            imm,
            CLOSE_BRACK,
            Register
        )
    )
    node(r_instruction
        allRule(
            unary_instruction,
            Register
        )
    )
    node(indirect_instruction
        allRule(
            unary_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK
        )
    )
    node(index_instruction
        allRule(
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
        allRule(
            unary_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            imm,
            CLOSE_BRACK
        )
    )
    node(complex_instruction
        allRule(
            unary_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            imm,
            Plus_Minus,
            imm,
            CLOSE_BRACK
        )
    )
    node(offset_instruction
        allRule(
            unary_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            imm,
            CLOSE_BRACK
        )
    )
    node(pp_r_instruction
        allRule(
            Push_Pop_instruction,
            Register
        )
    )
    node(pp_indirect_instruction
        allRule(
            Push_Pop_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK
        )
    )
    node(pp_index_instruction
        allRule(
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
        allRule(
            Push_Pop_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            imm,
            CLOSE_BRACK
        )
    )
    node(pp_complex_instruction
        allRule(
            Push_Pop_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            imm,
            Plus_Minus,
            imm,
            CLOSE_BRACK
        )
    )
    node(pp_offset_instruction
        allRule(
            Push_Pop_instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            imm,
            CLOSE_BRACK
        )
    )
    node(jump_label
        allRule(
            Jump_instruction,
            IDENTIFIER
        )
        var(long, ptr)
    )
    node(syscall_instruction
        allRule(
            SYSCALL
        )
    )
    node(Directive
        anyRule(
            DB,
            DW,
            DD,
            DQ
        )
        var(int, size)
    )
    node(Variable
        allRule(
            IDENTIFIER,
            Directive,
            Variable_Value
        )
    )
    node(Variable_Value
        anyRule(
            Variable_Value_DB,
            Variable_Value_DW,
            Variable_Value_DD,
            Variable_Value_DQ
        )
    )
    nodeNext(Variable_Value_DB
        anyRule(
            STRING_LITERAL,
            CHAR_LITERAL,
            imm
        )
    )
    nodeNext(Variable_Value_DW
        anyRule(
            STRING_LITERAL,
            CHAR_LITERAL,
            imm
        )
    )
    nodeNext(Variable_Value_DD
        anyRule(
            STRING_LITERAL,
            CHAR_LITERAL,
            imm
        )
    )
    nodeNext(Variable_Value_DQ
        anyRule(
            STRING_LITERAL,
            CHAR_LITERAL,
            imm
        )
    )

    node(NOP_instruction
        anyRule(
            NOP
        )
    )

    node(RET_instruction
        anyRule(
            RET
        )
    )

    node(INT_instruction
        allRule(
            INT,
            imm
        )
    )

    node(WAIT_instruction
        anyRule(
            WAIT
        )
    )


    node(jmp_register
        anyRule(
            Register16,
            Register64
        )
    )
    node(jmp_r_instruction
        allRule(
            JMP,
            Register
        )
    )
    node(jmp_indirect_instruction
        allRule(
            JMP,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK
        )
    )
    node(jmp_index_instruction
        allRule(
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
        allRule(
            JMP,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            imm,
            CLOSE_BRACK
        )
    )
    node(jmp_complex_instruction
        allRule(
            JMP,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            MULTIPLY,
            imm,
            Plus_Minus,
            imm,
            CLOSE_BRACK
        )
    )
    node(jmp_offset_instruction
        allRule(
            JMP,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            imm,
            CLOSE_BRACK
        )
    )
    node(jmp_label
        allRule(
            JMP,
            IDENTIFIER
        )
        var(long, ptr)
    )
    node(call_label
        allRule(
            CALL,
            IDENTIFIER
        )
        var(long, ptr)
    )


    iterationStep(semantics)
    iterationStep(codegen)
    iterationStep(label_resolution)
)
