#include "assembler.h"
#include "Instructions.h"


// ----------------------------------- PARSING ---------------------------------


int is_symbol(char c) {
    return (c == '+' || c == '-' || c == '[' || c == ']' || c == ',' || c == '*' || c == ';' || c == ':');
}


int run_keyword(const char* keyword, Instruction* instruction)
{
    return instruction_map[abs(((keyword[0] - 'A') % 26) + ((keyword[1] - 'A') % 26) * 26 + ((keyword[2] - 'A') % 26) * 26 * 26)].handler(instruction);
}

int run_keyword_size(char* keyword)
{

    Instruction* instruction = (Instruction*)malloc(sizeof(Instruction));
    if (offset+1 < (int)tokens.size && TOKEN(offset+1)->content[0] == ':')
    {
        if (strcmp(TOKEN(offset)->content, begin_label_label) == 0)
        {
            begin_label_instruction_index = instructions.size;
        }
        offset+=2;
        instruction->type = INST_LABEL;
        instruction->val.label.label = keyword;
        instruction->size = 0;
    }
    else
    {
        instruction->val.instruction.keyword = keyword;
        instruction_map[abs(((keyword[0] - 'A') % 26) + ((keyword[1] - 'A') % 26) * 26 + ((keyword[2] - 'A') % 26) * 26 * 26)].size_handler(instruction);
    }
    instruction->offset = global_offset;
    global_offset += instruction->size;
    vector_push(&instructions, instruction);
    return 1;
}





int is_var_type(const char* str)
{
    if (strcmp(str, "DB") == 0 || 
    strcmp(str, "DW") == 0 ||
    strcmp(str, "DD") == 0 ||
    strcmp(str, "DQ") == 0)
    {
        return 1;
    }
    return 0;
}

void parse_variable()
{
    // char[1024] variable;
    const char* var_name = TOKEN(offset)->content;
    offset+=2; //for :
    char* var_type;

    Instruction* inst = (Instruction*)malloc(sizeof(Instruction));
    inst->type = INST_VARIABLE;
    inst->val.var.var_name = var_name;

    inst->size = 0;

    do
    {
        int times = 1;
        if (strcmp(TOKEN(offset)->content, "TIMES") == 0)
        {
            times = atoi(TOKEN(offset+1)->content);
            offset+= 2;
        }
        int saved_offset = offset;

        var_type = TOKEN(offset)->content;
        int type_size = 1;
    
        inst->val.var.is_constant = 0;
        if (strcmp(var_type, "DB") == 0)
        {
            type_size = 1;
        }
        else if (strcmp(var_type, "DW") == 0)
        {
            type_size = 2;
        }
        else if (strcmp(var_type, "DD") == 0)
        {
            type_size = 4;
        }
        else if (strcmp(var_type, "DQ") == 0)
        {
            type_size = 8;
        }
        else
        {
            break;
        }

        for (int i = 0; i < times; i++)
        {
            offset = saved_offset;
        
            int cont = 1;
            do
            {
                offset++;
                if (TOKEN(offset)->content[0] == '"')
                {
                    int string_length = strlen(TOKEN(offset)->content) - 1;

                    if (inst->size == 0)
                    {
                        inst->val.var.contents = (char*)malloc(string_length * type_size);
                        memset(inst->val.var.contents, 0, string_length * type_size);
                    }
                    else
                    {
                        inst->val.var.contents = (char*)realloc(inst->val.var.contents, inst->size + (string_length * type_size));
                        memset(inst->val.var.contents + inst->size, 0, (string_length * type_size));
                    }

                    for (int i = 1; i < string_length + 1; i++)
                    {
                        inst->val.var.contents[inst->size + (i * type_size)] = TOKEN(offset)->content[i];
                    }
                    inst->size += type_size * string_length;
                }
                else if (TOKEN(offset)->content[0] == '\'')
                {
                    if (inst->size == 0)
                    {
                        inst->val.var.contents = (char*)malloc(type_size);
                        memset(inst->val.var.contents, 0, type_size);
                    }
                    else
                    {
                        inst->val.var.contents = (char*)realloc(inst->val.var.contents, inst->size + type_size);
                        memset(inst->val.var.contents+inst->size, 0, type_size);
                    }

                    inst->val.var.contents[inst->size] = TOKEN(offset)->content[1];
                    inst->size += type_size;
                }
                else
                {
                    if (inst->size == 0)
                    {
                        inst->val.var.contents = (char*)malloc(type_size);
                        memset(inst->val.var.contents, 0, type_size);
                    }
                    else
                    {
                        inst->val.var.contents = (char*)realloc(inst->val.var.contents, inst->size + type_size);
                        memset(inst->val.var.contents + inst->size, 0, type_size);
                    }

                    intToBytes(atoi(TOKEN(offset)->content), inst->val.var.contents + inst->size, type_size);
                    inst->size += type_size;
                }

                if (offset + 1 < (int)tokens.size && TOKEN(offset+1)->content[0] == ',')
                {
                    cont = 1;
                }
                else
                {
                    cont = 0;
                }

                offset++;


            } while (cont);

        }
        var_type = TOKEN(offset)->content;
        
 
    } while (is_var_type(var_type));

    inst->offset = global_offset;
    global_offset += inst->size;
    
    vector_push(&instructions, inst);

}

int line_number = 0;
int column = 0;
int char_index = 0;
int last_column = 0;

Token* create_token(char* content)
{
    Token* token = (Token*)malloc(sizeof(Token));

    token->content = content;
    token->line = line_number;
    token->line_pos = column;
    token->file_pos = char_index;

    return token;
}

char file_fgetc(FILE* file)
{
    char c = fgetc(file);
    if (c == '\n')
    {
        line_number++;
        last_column = column;
        column = -1;
    }
    column++;
    char_index++;
    return c;
}

char file_ungetc(char c, FILE* file)
{
    column--;
    char_index--;
    ungetc(c, file);
    if (c == '\n')
    {
        column = last_column;
        line_number--;
    }
    return c;
}

void lexical_analysis(FILE* file)
{
    vector_init(&tokens, 10);  // Initialize the dynamic vector
    char buffer[1024];     // Buffer to hold the current token
    size_t buffer_index = 0;
    char c;
    int in_comment = 0;

    int working_on_string = 0;
    int string_size = 0;
    char string[512];

    int char_step = 0;

    while ((c = file_fgetc(file)) != EOF) {
        // Handle comments: skip everything after ';' in the same line
        if (c == ';') {
            in_comment = 1;
        }

        if (char_step == 0 && c == '\'')
        {
            buffer[0] = '\'';
            char_step = 1;
        }
        else if (char_step > 0 && char_step < 4)
        {
            buffer[0] = c;
            char_step++;
        }
        else
        {
            char_step = 0;
        }

        if (working_on_string == 0 && c == '"')
        {
            string[0] = '"';
            string_size = 1;
            working_on_string = 1;
            continue;
        }
        else if (working_on_string)
        {
            if (c == '"')
            {
                string[string_size] = '"';
                string[string_size+1] = '\0';
                vector_push(&tokens, create_token(strdup(string)));
                string_size = 0;
                working_on_string = 0;
                continue;
            }
            string[string_size] = c;
            string_size++;
            continue;
        }

        // If we're inside a comment, skip characters until the end of the line
        if (in_comment) {
            if (c == '\n') {
                in_comment = 0; // End of comment (newline)
            }
            continue; // Skip the character in the comment
        }

        // Skip whitespace, and print the token when we encounter whitespace or symbols
        if (isspace(c)) {
            if (buffer_index > 0) {
                buffer[buffer_index] = '\0';
                vector_push(&tokens, create_token(strdup(buffer)));
                buffer_index = 0;
            }
        }
        // Handle symbols directly
        else if (is_symbol(c)) {
            if (buffer_index > 0) {
                buffer[buffer_index] = '\0';
                vector_push(&tokens, create_token(strdup(buffer)));
                buffer_index = 0;
            }
            char symbol[2] = {c, '\0'};
            vector_push(&tokens, create_token(strdup(symbol)));
        }
        // Handle numbers (digits)
        else if (isdigit(c)) {
            buffer[buffer_index++] = c;

            char next_c = file_fgetc(file);
            while ((isdigit(next_c) || isalpha(next_c)) && !is_symbol(next_c)) {
                buffer[buffer_index++] = next_c;
                next_c = file_fgetc(file);
            }
            file_ungetc(next_c, file);
            buffer[buffer_index++] = '\0';
            convertToDecimalInPlace(buffer);
            vector_push(&tokens, create_token(strdup(buffer)));
            buffer_index = 0;
        }
        // Handle words (letters or underscores)
        else if (isalpha(c) || c == '_') {
            buffer[buffer_index++] = c;
            while (isalnum(c = file_fgetc(file)) || c == '_') {
                buffer[buffer_index++] = c;
            }
            file_ungetc(c, file);  // Push back the non-alphanumeric character
            buffer[buffer_index] = '\0';
            vector_push(&tokens, create_token(strdup(buffer)));
            buffer_index = 0;
        }
    }
}

void syntax_analysis()
{
    while (offset < (int)tokens.size)
    {
        if (strcmp(TOKEN(offset)->content, "SECTION") == 0)
        {
            if (strcmp(TOKEN(offset+1)->content, "DATA") == 0)
            {
                mode = ASM_DATA;
            }
            else if (strcmp(TOKEN(offset+1)->content, "TEXT") == 0)
            {
                mode = ASM_TEXT;
            }

            offset += 2;
        }
        else
        {
            switch (mode)
            {
            case ASM_DATA:
                parse_variable();
                break;
            case ASM_TEXT:
                run_keyword_size(TOKEN(offset)->content);
                break;
            case ASM_BSS:
                
            //idk
                break;
            case ASM_GLOBAL:
                if (strcmp(TOKEN(offset)->content, "GLOBAL") == 0)
                {
                    begin_label_label = TOKEN(offset+1)->content;
                    offset += 2;
                }
                break;
            
            default:
                break;
            }
        }
    }
}

void semantic_analysis()
{
    for (int i = 0; i < (int)instructions.size; i++)
    {
        if (INSTRUCTION(i)->type == INST_LABEL)
        {
            for (int i2 = 0; i2 < (int)instructions.size; i2++)
            {
                if (INSTRUCTION(i2)->type == INST_JUMP && strcmp(INSTRUCTION(i2)->val.jmp.label, INSTRUCTION(i)->val.label.label) == 0)
                {
                    INSTRUCTION(i2)->val.jmp.label_offset = &INSTRUCTION(i)->offset;
                }
            }
        }
    }

    int updated_jumps = 0;
    do
    {
        updated_jumps = 0;
        int updated_jump_offset = 0;
        
        for (int i = 0; i < (int)instructions.size; i++)
        {
            if (INSTRUCTION(i)->type == INST_JUMP)
            {
                if (INSTRUCTION(i)->size == 2)
                {
                    int offset = (*INSTRUCTION(i)->val.jmp.label_offset - INSTRUCTION(i)->offset)-2;
                    if (offset > 127-4)
                    {
                        INSTRUCTION(i)->size = 6;
                        INSTRUCTION(i)->offset += updated_jump_offset*4;
                        updated_jump_offset++;
                        updated_jumps++;
                    }
                    else if (offset < -128-4)
                    {
                        INSTRUCTION(i)->size = 6;
                        INSTRUCTION(i)->offset += updated_jump_offset*4;
                        updated_jump_offset++;
                        updated_jumps++;
                    }
                    else
                    {
                        INSTRUCTION(i)->offset += updated_jump_offset*4;
                    }
                }
                else if (INSTRUCTION(i)->size == 6)
                {
                    int offset = (*INSTRUCTION(i)->val.jmp.label_offset - INSTRUCTION(i)->offset)-6;
                    if (offset <= 127-4 && offset >= 0)
                    {
                        INSTRUCTION(i)->size = 2;
                        INSTRUCTION(i)->offset += updated_jump_offset*4;
                        updated_jump_offset--;
                        updated_jumps++;
                    }
                    else if (offset >= -128-4 && offset <= 0)
                    {
                        INSTRUCTION(i)->size = 2;
                        INSTRUCTION(i)->offset += updated_jump_offset*4;
                        updated_jump_offset--;
                        updated_jumps++;
                    }
                    else
                    {
                        INSTRUCTION(i)->offset += updated_jump_offset*4;
                    }
                }


                
            }
            else
            {
                INSTRUCTION(i)->offset += updated_jump_offset*4;
            }
        }
    } while (updated_jumps != 0);
}

void code_generation()
{
    if (begin_label_instruction_index != -1)
    {
        Elf64_Ehdr ehdr = (Elf64_Ehdr) {
            .e_ident = {
                ELFMAG0,
                ELFMAG1,
                ELFMAG2,
                ELFMAG3,
                ELFCLASS64,
                ELFDATA2LSB,
                EV_CURRENT,
                ELFOSABI_SYSV,
                0, 0, 0, 0, 0, 0, 0
            },
            .e_type = ET_EXEC,
            .e_machine = EM_X86_64,
            .e_entry = 0x400078 + INSTRUCTION(begin_label_instruction_index)->offset, // filled in later
            .e_phoff = 64,
            .e_shoff = 0,
            .e_flags = 0,
            .e_ehsize = 64,
            .e_phentsize = 56,
            .e_phnum = 1,
            .e_shentsize = 0,
            .e_shnum = 0,
            .e_shstrndx = SHN_UNDEF
        };
        fwrite(&ehdr, 1, sizeof(ehdr), file_out);
    
        
        Elf64_Phdr phdr = (Elf64_Phdr) {
            .p_type = PT_LOAD,
            .p_offset = 0x78, // 64 + 56
            .p_vaddr = 0x400078,
            .p_paddr = 0x400078,
            .p_filesz = global_offset, // filled in later
            .p_memsz = global_offset, // filled in later
            .p_flags = PF_X | PF_R,
            .p_align = 0x8
        };
        fwrite(&phdr, 1, sizeof(phdr), file_out);
    }

    for (int i = 0; i < (int)instructions.size; i++)
    {
        switch (INSTRUCTION(i)->type)
        {
        case INST_INSTRUCTION:
            run_keyword(INSTRUCTION(i)->val.instruction.keyword, INSTRUCTION(i));
            break;
        case INST_JUMP:
            run_keyword(INSTRUCTION(i)->val.jmp.keyword, INSTRUCTION(i));
            break;
        case INST_LABEL:
            // dont need to do anything on a label
            break;
        case INST_VARIABLE:
            for (int i2 = 0; i2 < INSTRUCTION(i)->size; i2++)
            {
                fprintf(file_out, "%c", INSTRUCTION(i)->val.var.contents[i2]);
            }
        
        default:
            break;
        }
    }
}

void parse_token(FILE *file) {
    
    lexical_analysis(file);
    syntax_analysis();
    semantic_analysis();
    code_generation();

    vector_free(&tokens);
}

char* replace_ext_with_o(const char* filename) {
    // Find last '.' and last '/'
    const char* last_dot = strrchr(filename, '.');
    const char* last_slash = strrchr(filename, '/');

    // Only consider dots after the last slash (true file extension)
    const char* ext_start = NULL;
    if (last_dot) {
        if (!last_slash || last_dot > last_slash) {
            ext_start = last_dot;
        }
    }

    // Calculate base length (up to extension or full length)
    size_t base_len = ext_start ? (size_t)(ext_start - filename) : strlen(filename);

    // Allocate new string (base + .o + null terminator)
    char* new_name = malloc(base_len + 3);
    if (!new_name) return NULL;

    // Copy base and append .o
    memcpy(new_name, filename, base_len);
    strcpy(new_name + base_len, ".o");

    return new_name;
}


int main(int argc, const char* argv[]) {
    if (argc <= 1)
    {
        printf("Please provide an input file!\n");
        return 1;
    }
    const char *filename = argv[1];  // Replace with your file's path
    file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    if (argc == 4 && strcmp(argv[2], "-o") == 0)
    {
        file_out = fopen(argv[3], "w");
    }
    else
    {
        file_out = fopen(replace_ext_with_o(argv[1]), "w");
    }


    vector_init(&instructions, 10);
    init_instruction_map();
    init_register_map();
    parse_token(file);
    
    fclose(file);
    fclose(file_out);
    return 0;
}
