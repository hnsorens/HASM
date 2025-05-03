#include "assembler.h"

Vector tokens;
Vector instructions;
InstructionEntry instruction_map[26*26*26] = {0};
FILE* file_out = 0;
FILE* file = 0;
int global_offset = 0;
int offset = 0;
ASM_MODE mode = ASM_GLOBAL;
char* begin_label_label = "";
int begin_label_instruction_index = -1;

#include "InstructionHandlers.h"

// Vectors
void vector_init(Vector *vec, size_t capacity) {
    vec->data = malloc(capacity * sizeof(void *));
    vec->size = 0;
    vec->capacity = capacity;
}

void vector_push(Vector *vec, void *item) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, vec->capacity * sizeof(void *));
    }
    vec->data[vec->size++] = item;
}

void vector_free(Vector *vec) {
    for (size_t i = 0; i < vec->size; i++) free(vec->data[i]);
    free(vec->data);
}

#include "InstructionHandlers.h"

// Instruction Map
void init_instruction_map()
{
    memset(instruction_map, 0, sizeof(instruction_map));

    char* opcode_str = "";
    #define ADD_INSTR(opcode) \
        opcode_str = #opcode; \
        instruction_map[abs(((opcode_str[0] - 'A') % 26) + ((opcode_str[1] - 'A') % 26) * 26 + ((opcode_str[2] - 'A') % 26) * 26 * 26)] = (InstructionEntry){opcode##_handler, opcode##_size_handler};

    ADD_INSTR(SUB);
    ADD_INSTR(MOV);
    ADD_INSTR(OR);
    ADD_INSTR(ADC);
    ADD_INSTR(SBB);
    ADD_INSTR(AND);
    ADD_INSTR(XOR);
    ADD_INSTR(CMP);
    ADD_INSTR(ADD);
    ADD_INSTR(MUL);
    ADD_INSTR(IMUL);
    ADD_INSTR(DIV);
    ADD_INSTR(IDIV);
    ADD_INSTR(NOT);
    ADD_INSTR(NEG);
    ADD_INSTR(INC);
    ADD_INSTR(DEC);
    ADD_INSTR(TEST);
    ADD_INSTR(JO);
    ADD_INSTR(JNO);
    ADD_INSTR(JB);
    ADD_INSTR(JAE);
    ADD_INSTR(JE);
    ADD_INSTR(JNE);
    ADD_INSTR(JBE);
    ADD_INSTR(JA);
    ADD_INSTR(JS);
    ADD_INSTR(JNS);
    ADD_INSTR(JP);
    ADD_INSTR(JNP);
    ADD_INSTR(JL);
    ADD_INSTR(JGE);
    ADD_INSTR(JLE);
    ADD_INSTR(JG);
    ADD_INSTR(JMP);
    ADD_INSTR(INT);
    ADD_INSTR(NOP);
    ADD_INSTR(SYSCALL);
    ADD_INSTR(LEA);
    ADD_INSTR(PUSH);
    ADD_INSTR(POP);
    ADD_INSTR(WAIT);
    ADD_INSTR(RET);
    ADD_INSTR(CALL);

    #undef ADD_INSTR
}
