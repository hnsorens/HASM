
// #include "Parser.h"
#include <stdlib.h>
#include <stdio.h>
// #include "HASMGenerationPipeline.h"

int main(int argc, const char* argv[])
{
    // CompileHASM(argv[1], "OUTPUT.txt");
    // filename = malloc(strlen(argv[1]));
    // memcpy(filename, argv[1], strlen(argv[1]));

    // FILE* file = fopen(argv[1], "rb");
    // if (!file)
    // {
    //     perror("Error opening file");
    //     return 1;
    // }

    // fseek(file, 0, SEEK_END);
    // long file_size = ftell(file);
    // fseek(file, 0, SEEK_SET);

    // char* source = (char*)malloc(file_size + 1);
    // if (!source)
    // {
    //     perror("Memory Allocation failed");
    //     fclose(file);
    //     return 0;
    // }

    // fread(source, 1, file_size, file);
    // source[file_size] = '\0';

    // fclose(file);

    // struct TokenBatch* tokens = tokenize(source);

    // for (int i = 0; i < tokens->token_count; i++)
    // {
    //     printf("Token: %d, Value: '%s', Line: %d, Column: %d\n", tokens->tokens[i].type, tokens->tokens[i].value, tokens->tokens[i].line, tokens->tokens[i].column);
    // }

    // struct Code* code = Create_Code(tokens);
    // semantic_Code(code);

    // printf("SEMANTICS COMPLETE\n");

    FILE* o_file = fopen("OUTPUT.txt", "w");
    fprintf(o_file, "HELLO WORLD");
    // gen_code_Code(o_file, code);
    // gen_code_Code(o_file, code);

    // print_Code(0, code);

    // cleanup_batch(tokens);

    fclose(o_file);

    return 0;
}