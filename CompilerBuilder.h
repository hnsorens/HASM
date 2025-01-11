/*
MIT License

Copyright (c) 2024 HnsorensSoftware

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define COMPILER

#define PARENS ()
#define AND(v_) && v_
#define OR(v_) || v_

#ifdef _MSC_VER // Microsoft compilers

#   define GET_ARG_COUNT(...)  INTERNAL_EXPAND_ARGS_PRIVATE(INTERNAL_ARGS_AUGMENTER(__VA_ARGS__))

#   define INTERNAL_ARGS_AUGMENTER(...) unused, __VA_ARGS__
#   define INTERNAL_EXPAND(x) x
#   define INTERNAL_EXPAND_ARGS_PRIVATE(...) INTERNAL_EXPAND(INTERNAL_GET_ARG_COUNT_PRIVATE(__VA_ARGS__, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#   define INTERNAL_GET_ARG_COUNT_PRIVATE(_1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, count, ...) count

#else // Non-Microsoft compilers

#define GET_ARG_COUNT(...) INTERNAL_GET_ARG_COUNT_PRIVATE(0, ## __VA_ARGS__, \
256, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, \
240, 239, 238, 237, 236, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, \
224, 223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, \
208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, 193, \
192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, \
176, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, \
160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, \
144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, \
128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, \
112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, \
95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, \
75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, \
55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, \
35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, \
15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define INTERNAL_GET_ARG_COUNT_PRIVATE( \
_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, \
_64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127, \
_128, _129, _130, _131, _132, _133, _134, _135, _136, _137, _138, _139, _140, _141, _142, _143, _144, _145, _146, _147, _148, _149, _150, _151, _152, _153, _154, _155, _156, _157, _158, _159, _160, _161, _162, _163, _164, _165, _166, _167, _168, _169, _170, _171, _172, _173, _174, _175, _176, _177, _178, _179, _180, _181, _182, _183, _184, _185, _186, _187, _188, _189, _190, _191, \
_192, _193, _194, _195, _196, _197, _198, _199, _200, _201, _202, _203, _204, _205, _206, _207, _208, _209, _210, _211, _212, _213, _214, _215, _216, _217, _218, _219, _220, _221, _222, _223, _224, _225, _226, _227, _228, _229, _230, _231, _232, _233, _234, _235, _236, _237, _238, _239, _240, _241, _242, _243, _244, _245, _246, _247, _248, _249, _250, _251, _252, _253, _254, _255, _256, count, ...) count

#endif

#pragma region INCREMENTS
#define inc_0 1
#define inc_1 2
#define inc_2 3
#define inc_3 4
#define inc_4 5
#define inc_5 6
#define inc_6 7
#define inc_7 8
#define inc_8 9
#define inc_9 10
#define inc_10 11
#define inc_11 12
#define inc_12 13
#define inc_13 14
#define inc_14 15
#define inc_15 16
#define inc_16 17
#define inc_17 18
#define inc_18 19
#define inc_19 20
#define inc_20 21
#define inc_21 22
#define inc_22 23
#define inc_23 24
#define inc_24 25
#define inc_25 26
#define inc_26 27
#define inc_27 28
#define inc_28 29
#define inc_29 30
#define inc_30 31
#define inc_31 32
#define inc_32 33
#define inc_33 34
#define inc_34 35
#define inc_35 36
#define inc_36 37
#define inc_37 38
#define inc_38 39
#define inc_39 40
#define inc_40 41
#define inc_41 42
#define inc_42 43
#define inc_43 44
#define inc_44 45
#define inc_45 46
#define inc_46 47
#define inc_47 48
#define inc_48 49
#define inc_49 50
#define inc_50 51
#define inc_51 52
#define inc_52 53
#define inc_53 54
#define inc_54 55
#define inc_55 56
#define inc_56 57
#define inc_57 58
#define inc_58 59
#define inc_59 60
#define inc_60 61
#define inc_61 62
#define inc_62 63
#define inc_63 64
#define inc_64 65
#define inc_65 66
#define inc_66 67
#define inc_67 68
#define inc_68 69
#define inc_69 70
#define inc_70 71
#define inc_71 72
#define inc_72 73
#define inc_73 74
#define inc_74 75
#define inc_75 76
#define inc_76 77
#define inc_77 78
#define inc_78 79
#define inc_79 80
#define inc_80 81
#define inc_81 82
#define inc_82 83
#define inc_83 84
#define inc_84 85
#define inc_85 86
#define inc_86 87
#define inc_87 88
#define inc_88 89
#define inc_89 90
#define inc_90 91
#define inc_91 92
#define inc_92 93
#define inc_93 94
#define inc_94 95
#define inc_95 96
#define inc_96 97
#define inc_97 98
#define inc_98 99
#define inc_99 100
#define inc_100 101
#define inc_101 102
#define inc_102 103
#define inc_103 104
#define inc_104 105
#define inc_105 106
#define inc_106 107
#define inc_107 108
#define inc_108 109
#define inc_109 110
#define inc_110 111
#define inc_111 112
#define inc_112 113
#define inc_113 114
#define inc_114 115
#define inc_115 116
#define inc_116 117
#define inc_117 118
#define inc_118 119
#define inc_119 120
#define inc_120 121
#define inc_121 122
#define inc_122 123
#define inc_123 124
#define inc_124 125
#define inc_125 126
#define inc_126 127
#define inc_127 128
#pragma endregion

#define createCompiler(contents_) CREATE_COMPILER_H_IMPL(COMPILER contents_)
#define recurse(name_) IT_IMPL(COMPILER, name_, NODE)
#define IT_IMPL(compilerName_, name_, node_) IT_IMPL_IMPL(compilerName_, name_, node_)
#define IT_IMPL_IMPL(compilerName_, name_, node_) void compilerName_##name_##node_(FILE* file, struct compilerName_##node_ * var_0, void (*continue_function)(FILE*, void*))

#define CREATE_COMPILER_C(name_, ...) MACRO_FOR_EACH(C_NODE__, __VA_ARGS__)


#define C_NODE__NODE_IMPL(placeholder, name_, ...) RUN_ITERATION_MACRO_FOR_EACH(DEFINE_ITERATION_FUNCTION, name_, __VA_ARGS__)
#define DEFINE_ITERATION_FUNCTION(dec_, name_, body_) DEFINE_ITERATION_FUNCTION_IMPL(COMPILER, DEC_##dec_, name_, body_) 
#define DEFINE_ITERATION_FUNCTION_IMPL(compilerName_, dec_, name_, body_) DEFINE_ITERATION_FUNCTION_IMPL_IMPL(compilerName_, dec_, name_, body_)
#define DEFINE_ITERATION_FUNCTION_IMPL_IMPL(compilerName_, dec_, name_, body_) void compilerName_##dec_##name_(FILE* file, struct compilerName_##name_ * var_0) body_
#define DEC_ITERATION_IMPL(name_) name_



#define CREATE_COMPILER_H_IMPL(name_, ...) CREATE_COMPILER_H_IMPL_IMPL(name_, __VA_ARGS__)
#define CREATE_COMPILER_H_IMPL_IMPL(name_, ...) \
FILE* name_##Out; \
char** name_##Contents; \
const char** readFileLines(FILE *file) { \
    size_t allocatedSize = 256; \
    const char **lines = (const char **)malloc(sizeof(char*) * allocatedSize); \
    if (lines == NULL) { \
        perror("Failed to allocate memory for lines"); \
        return NULL; \
    } \
    size_t lineCount = 0; \
    char line[1024]; \
    while (fgets(line, sizeof(line), file)) { \
        size_t len = strlen(line); \
        if (line[len - 1] == '\n') { \
            line[len - 1] = '\0'; \
        } \
        if (lineCount >= allocatedSize) { \
            allocatedSize *= 2; \
            const char **newLines = (const char **)realloc(lines, sizeof(char*) * allocatedSize); \
            if (newLines == NULL) { \
                perror("Failed to reallocate memory for lines"); \
                for (size_t i = 0; i < lineCount; i++) { \
                    free((void*)lines[i]); \
                } \
                free((void*)lines); \
                return NULL; \
            } \
            lines = newLines; \
        } \
        lines[lineCount] = strdup(line); \
        if (lines[lineCount] == NULL) { \
            perror("Failed to duplicate line"); \
            for (size_t i = 0; i < lineCount; i++) { \
                free((void*)lines[i]); \
            } \
            free((void*)lines); \
            return NULL; \
        } \
        lineCount++; \
    } \
    return lines; \
} \
typedef struct name_##GarbageCollector \
{ \
    void** ptrs; \
    int capacity; \
    int count; \
} name_##GarbageCollector; \
struct name_##GarbageCollector* name_##garbage; \
struct name_##GarbageCollector* name_##CreateGarbageCollector() \
{ \
    struct name_##GarbageCollector* collector = malloc(sizeof( name_##GarbageCollector)); \
    collector->count = 0; \
    collector->capacity = 256; \
    collector->ptrs = malloc(sizeof(void*) * collector->capacity); \
    return collector; \
} \
void* name_##AddToCollector(void* ptr) \
{ \
    name_##garbage->ptrs[name_##garbage->count++] = ptr; \
    if (name_##garbage->count == name_##garbage->capacity) \
    { \
        name_##garbage->capacity += 256; \
        name_##garbage->ptrs = realloc(name_##garbage->ptrs, sizeof(void*) * name_##garbage->capacity); \
    } \
    return ptr; \
} \
void name_##FreeAll() \
{ \
    for (int i = 0; i < name_##garbage->count; i++) \
    { \
        free(name_##garbage->ptrs[i]); \
    } \
} \
typedef struct name_##Token \
{ \
    int type; \
    char* value; \
    int line; \
    int column; \
    char* lineStr; \
} name_##Token; \
typedef struct name_##TokenBatch \
{ \
    name_##Token* tokens; \
    int token_on; \
    int token_count; \
    int token_capacity; \
} name_##TokenBatch; \
name_##TokenBatch* name_##create_token_batch() \
{ \
    name_##TokenBatch* batch = name_##AddToCollector(malloc(sizeof(name_##TokenBatch))); \
    batch->token_count = 0; \
    batch->token_capacity = 256; \
    batch->token_on = 0; \
    batch->tokens = malloc(sizeof(name_##Token) * batch->token_capacity); \
    return batch; \
} \
void name_##add_token(name_##TokenBatch* batch, name_##Token token) \
{ \
    if (batch->token_count == batch->token_capacity) \
    { \
        batch->token_capacity += 256; \
        batch->tokens = realloc(batch->tokens, sizeof(name_##Token) * batch->token_capacity); \
    } \
    batch->tokens[batch->token_count] = token; \
    batch->token_count++; \
} \
MACRO_FOR_EACH(H_TOKENS__, __VA_ARGS__) MACRO_FOR_EACH(H_IGNORE_TOKENS__, __VA_ARGS__) \
name_##TokenBatch* name_##tokenize(const char* code) \
{ \
    size_t codeLength = strlen(code); \
    size_t offset = 0; \
    name_##TokenBatch* tokens = name_##create_token_batch(); \
    int line = 1; \
    int column = 1; \
    while (offset < codeLength) \
    { \
        int matched = 0; \
        for (int i = 0; i < name_##token_count; i++) \
        { \
            regex_t regex; \
            regmatch_t match[1]; \
            if (regcomp(&regex, name_##token_patterns[i], REG_EXTENDED) == 0) \
            { \
                if (regexec(&regex, code + offset, 1, match, 0) == 0) \
                { \
                    if (name_##ignore_token(i)) \
                    { \
                        char* contents = strndup(code + offset, match[0].rm_eo); \
                        for (int j = 0; j < strlen(contents); j++) \
                        { \
                            if (contents[j] == '\n') \
                            { \
                                column = 1; \
                                line++; \
                            } \
                            else \
                            { \
                                column++; \
                            } \
                        } \
                        offset += match[0].rm_eo; \
                        matched = 1; \
                        regfree(&regex); \
                        break; \
                    } \
                    name_##Token token; \
                    token.type = (name_##TokenType)i; \
                    token.column = column; \
                    token.line = line; \
                    token.value = strndup(code + offset, match[0].rm_eo); \
                    name_##AddToCollector(token.value); \
                    name_##add_token(tokens, token); \
                    for (int j = 0; j < strlen(token.value); j++) \
                    { \
                        if (token.value[j] == '\n') \
                        { \
                            column = 1; \
                            line++; \
                        } \
                        else \
                        { \
                            column++; \
                        } \
                    } \
                    offset += match[0].rm_eo; \
                    matched = 1; \
                    regfree(&regex); \
                    break; \
                } \
            } \
            regfree(&regex); \
        } \
        if (!matched && offset < codeLength) \
        { \
            printf("Error: Invalid Token at offset %zu\n", offset); \
            break; \
        } \
    } \
    return tokens; \
} \
MACRO_FOR_EACH(H_NODE__, __VA_ARGS__) MACRO_NODE_FOR_EACH(TOKEN_H_ITERATION_MACRO__ ,H_EXPAND_TOKENS__ , XPAND(__VA_ARGS__), __VA_ARGS__) MACRO_NODE_FOR_EACH(H_ITERATION_MACRO__ ,H_EXPAND__ , XPAND(__VA_ARGS__), __VA_ARGS__)  MACRO_NODE_FOR_EACH(CONTINUE_H_ITERATION_MACRO__ ,H_EXPAND__ , XPAND(__VA_ARGS__), __VA_ARGS__) MACRO_FOR_EACH(H_NODE_CREATE__, __VA_ARGS__) MACRO_FOR_EACH(H_ITERATION_STEP__, __VA_ARGS__)  \
void Compile##name_(const char* in, const char* out) \
{ \
    name_##garbage = name_##CreateGarbageCollector(); \
    FILE* file = fopen(in, "rb"); \
    name_##Contents = readFileLines(file); \
    fseek(file, 0, SEEK_END); \
    long file_size = ftell(file); \
    fseek(file, 0, SEEK_SET); \
    char* source = name_##AddToCollector(malloc(file_size+1)); \
    if (!source) \
    { \
        printf("Memory allocation failed!"); \
        exit(1); \
    } \
    fread(source, 1, file_size, file); \
    source[file_size] = '\0'; \
    fclose(file); \
    struct name_##TokenBatch* tokens = name_##tokenize(source); \
    struct name_##Root* root = name_##CreateRoot(tokens); \
    if (tokens->token_on != tokens->token_count) \
    { \
        printf("Syntax Error!\n"); \
        int line_from = 0; \
        int current_line = tokens->tokens[tokens->token_on].line; \
        if (current_line - 4 > 0) \
        { \
            line_from = current_line - 4; \
        } \
        for (int i = line_from; i < current_line; i++) \
        { \
            printf("\nLine %i: %s", i, name_##Contents[i]); \
        } \
        printf(" <--- Junk Line\n"); \
        exit(1); \
    } \
    name_##Out = fopen(out, "w"); \
    MACRO_FOR_EACH(H_ITERATION_STEP_CALL__, __VA_ARGS__) \
    free(tokens->tokens); \
    name_##FreeAll(); \
    free(name_##garbage->ptrs); \
    free(name_##garbage); \
    fclose(name_##Out); \
}

#define continue_it() continue_function(file, var_0)

#define GET_TOKEN_IMPL(token, str) ,token

#define NOTHING(...)
#define H_DECLARE_ITERATION(n_, contents_)  H_DECLARE_ITERATION_IMPL(n_, contents_)
#define H_DECLARE_ITERATION_IMPL(n_, name_, ...) H_DECLARE_ITERATION_IMPL_IMPL(RULE(__VA_ARGS__), name_ MACRO2_FOR_EACH(H_GET_ITERATION_NAME__, E##n_))
#define H_DECLARE_ITERATION_IMPL_IMPL(n_, contents_) DECLARE_ITERATION_FUNCTIONS(n_, contents_)
#define DECLARE_ITERATION_FUNCTIONS(n_, name_, ...) RUN_X_X_MACRO_FOR_EACH(DECLARE_ITERATION_FUNCTION, GET_##n_, name_, __VA_ARGS__)
#define DECLARE_ITERATION_FUNCTION(rule_, name_, iteration_step_) DECLARE_ITERATION_FUNCTION_IMPL( COMPILER , rule_, name_, iteration_step_)
#define DECLARE_ITERATION_FUNCTION_IMPL(compilerName_, rule_, name_, iteration_step_) DECLARE_ITERATION_FUNCTION_IMPL_IMPL(compilerName_, FUNCTION__##rule_, rule_, name_, iteration_step_) 
#define DECLARE_ITERATION_FUNCTION_IMPL_IMPL(compilerName_, rule_macro_, rule_, name_, iteration_step_) \
void compilerName_##iteration_step_##name_##ContinueVoid(FILE* file, void * var_0); \
void compilerName_##iteration_step_##name_(FILE* file, struct compilerName_##name_* var_0, void (*continue_func)(FILE* file, void* var));


#define TOKEN_H_DECLARE_ITERATION(n_, contents_)  TOKEN_H_DECLARE_ITERATION_IMPL(n_, contents_)
#define TOKEN_H_DECLARE_ITERATION_IMPL(n_, ...) TOKEN_H_DECLARE_ITERATION_IMPL_IMPL(TOKEN(__VA_ARGS__) MACRO2_FOR_EACH(H_GET_ITERATION_NAME__, E##n_) )
#define TOKEN_H_DECLARE_ITERATION_IMPL_IMPL(contents_) TOKEN_H_DECLARE_ITERATION_IMPL_IMPL_IMPL(contents_)
#define TOKEN_H_DECLARE_ITERATION_IMPL_IMPL_IMPL(n_, ...) RUN_X_X_MACRO_FOR_EACH(ITERATION_STEP_FOR_TOKENS, n_, 0, __VA_ARGS__)
#define ITERATION_STEP_FOR_TOKENS(n_, placeholder, iteration_step_) ITERATION_STEP_FOR_TOKENS_IMPL(iteration_step_, 0 GET_##n_)
#define ITERATION_STEP_FOR_TOKENS_IMPL(iteration_step_, content_) ITERATION_STEP_FOR_TOKENS_IMPL_IMPL(iteration_step_, content_)
#define ITERATION_STEP_FOR_TOKENS_IMPL_IMPL(iteration_step_, placeholder, ...)  RUN_X_MACRO_FOR_EACH(DEFINE_ITERATION_TOKEN_FUNCTION, iteration_step_, __VA_ARGS__)
#define DEFINE_ITERATION_TOKEN_FUNCTION(iteration_step_, name_) DEFINE_ITERATION_TOKEN_FUNCTION_IMPL(COMPILER, iteration_step_, name_)
#define DEFINE_ITERATION_TOKEN_FUNCTION_IMPL(compilerName_, iteration_step_, name_) DEFINE_ITERATION_TOKEN_FUNCTION_IMPL_IMPL(compilerName_, iteration_step_, name_)
#define DEFINE_ITERATION_TOKEN_FUNCTION_IMPL_IMPL(compilerName_, iteration_step_, name_) \
void compilerName_##iteration_step_##name_##ContinueVoid(FILE* file, void * var_0) {} \
void compilerName_##iteration_step_##name_(FILE* file, struct compilerName_##name_ * var_0, void (*continue_func)(FILE* file, void* var)) {}


#define CONTINUE_H_DECLARE_ITERATION(n_, contents_)  CONTINUE_H_DECLARE_ITERATION_IMPL(n_, contents_)
#define CONTINUE_H_DECLARE_ITERATION_IMPL(n_, name_, ...) CONTINUE_H_DECLARE_ITERATION_IMPL_IMPL(RULE(__VA_ARGS__), name_ MACRO2_FOR_EACH(H_GET_ITERATION_NAME__, E##n_) )
#define CONTINUE_H_DECLARE_ITERATION_IMPL_IMPL(n_, contents_) CONTINUE_DECLARE_ITERATION_FUNCTIONS(n_, contents_)
#define CONTINUE_DECLARE_ITERATION_FUNCTIONS(n_, name_, ...) RUN_X_X_MACRO_FOR_EACH(CONTINUE_DECLARE_ITERATION_FUNCTION, GET_##n_, name_, __VA_ARGS__)
#define CONTINUE_DECLARE_ITERATION_FUNCTION(rule_, name_, iteration_step_) CONTINUE_DECLARE_ITERATION_FUNCTION_IMPL( COMPILER , rule_, name_, iteration_step_)
#define CONTINUE_DECLARE_ITERATION_FUNCTION_IMPL(compilerName_, rule_, name_, iteration_step_) CONTINUE_DECLARE_ITERATION_FUNCTION_IMPL_IMPL(compilerName_, FUNCTION__##rule_, rule_, name_, iteration_step_) 
#define CONTINUE_DECLARE_ITERATION_FUNCTION_IMPL_IMPL(compilerName_, rule_macro_, rule_, name_, iteration_step_) \
void compilerName_##iteration_step_##name_##Continue(FILE* file, struct compilerName_##name_* var_0) \
{ \
    rule_macro_(COMPILER, iteration_step_, EXPAND__##rule_) \
} \
void compilerName_##iteration_step_##name_##ContinueVoid(FILE* file, void* var_0) \
{ \
    compilerName_##iteration_step_##name_##Continue(file, (struct compilerName_##name_*)var_0); \
}

#define NEXT_CONTINUE_H_DECLARE_ITERATION(n_, contents_)  NEXT_CONTINUE_H_DECLARE_ITERATION_IMPL(n_, contents_)
#define NEXT_CONTINUE_H_DECLARE_ITERATION_IMPL(n_, name_, ...) NEXT_CONTINUE_H_DECLARE_ITERATION_IMPL_IMPL(RULE(__VA_ARGS__), name_ MACRO2_FOR_EACH(H_GET_ITERATION_NAME__, E##n_)  )
#define NEXT_CONTINUE_H_DECLARE_ITERATION_IMPL_IMPL(n_, contents_) NEXT_CONTINUE_DECLARE_ITERATION_FUNCTIONS(n_, contents_)
#define NEXT_CONTINUE_DECLARE_ITERATION_FUNCTIONS(n_, name_, ...) RUN_X_X_MACRO_FOR_EACH(NEXT_CONTINUE_DECLARE_ITERATION_FUNCTION, GET_##n_, name_, __VA_ARGS__)
#define NEXT_CONTINUE_DECLARE_ITERATION_FUNCTION(rule_, name_, iteration_step_) NEXT_CONTINUE_DECLARE_ITERATION_FUNCTION_IMPL( COMPILER , rule_, name_, iteration_step_)
#define NEXT_CONTINUE_DECLARE_ITERATION_FUNCTION_IMPL(compilerName_, rule_, name_, iteration_step_) NEXT_CONTINUE_DECLARE_ITERATION_FUNCTION_IMPL_IMPL(compilerName_, FUNCTION__##rule_, rule_, name_, iteration_step_) 
#define NEXT_CONTINUE_DECLARE_ITERATION_FUNCTION_IMPL_IMPL(compilerName_, rule_macro_, rule_, name_, iteration_step_) \
void compilerName_##iteration_step_##name_##Continue(FILE* file, struct compilerName_##name_* var_0) \
{ \
    rule_macro_(COMPILER, iteration_step_, EXPAND__##rule_) \
    if (var_0->next) \
    { \
        compilerName_##iteration_step_##name_(file, var_0->next, compilerName_##iteration_step_##name_##ContinueVoid); \
    } \
} \
void compilerName_##iteration_step_##name_##ContinueVoid(FILE* file, void* var_0) \
{ \
    compilerName_##iteration_step_##name_##Continue(file, (struct compilerName_##name_*)var_0); \
}



#define EXPAND__ANY_RULE_ITERATION(...) __VA_ARGS__
#define FUNCTION__ANY_RULE_ITERATION(...) FUNCTION_INTERIOR__ANY_RULE_ITERATION
#define FUNCTION_INTERIOR__ANY_RULE_ITERATION(compilerName_, iteration_step_, ...) \
switch(var_0->var_index) \
{ \
    INDEXED_X_RUN_MACRO_FOR_EACH(ANY_RULE_CONTINUE_CASE, iteration_step_, __VA_ARGS__) \
} \

#define ANY_RULE_CONTINUE_CASE(rule_, iteration_step_, n_) ANY_RULE_CONTINUE_CASE_IMPL(COMPILER, rule_, iteration_step_, n_)
#define ANY_RULE_CONTINUE_CASE_IMPL(compilerName_, rule_, iteration_step_, n_) ANY_RULE_CONTINUE_CASE_IMPL_IMPL(compilerName_, rule_, iteration_step_, n_)
#define ANY_RULE_CONTINUE_CASE_IMPL_IMPL(compilerName_, rule_, iteration_step_, n_) \
case n_: \
compilerName_##iteration_step_##rule_(file, var_0->var.var_##n_, compilerName_##iteration_step_##rule_##ContinueVoid); \
break;


#define EXPAND__ALL_RULE_ITERATION(...) __VA_ARGS__
#define FUNCTION__ALL_RULE_ITERATION(...) FUNCTION_INTERIOR__ALL_RULE_ITERATION
#define FUNCTION_INTERIOR__ALL_RULE_ITERATION(compilerName_, iteration_step_, ...) INDEXED_X_RUN_MACRO_FOR_EACH(ALL_RULE_CONTINUE_CASE, iteration_step_, __VA_ARGS__)

#define ALL_RULE_CONTINUE_CASE(rule_, iteration_step_, n_) ALL_RULE_CONTINUE_CASE_IMPL(COMPILER, rule_, iteration_step_, n_)
#define ALL_RULE_CONTINUE_CASE_IMPL(compilerName_, rule_, iteration_step_, n_) ALL_RULE_CONTINUE_CASE_IMPL_IMPL(compilerName_, rule_, iteration_step_, n_)
#define ALL_RULE_CONTINUE_CASE_IMPL_IMPL(compilerName_, rule_, iteration_step_, n_) \
compilerName_##iteration_step_##rule_(file, var_0->var_##n_, compilerName_##iteration_step_##rule_##ContinueVoid);

#define EXPAND_CONTENT(content_) EXPAND_CONTENT_IMPL(content_)
#define EXPAND_CONTENT_IMPL(...) __VA_ARGS__
#define EXPAND(...) __VA_ARGS__

#define GET_RULE(...) MACRO2_FOR_EACH(GET_RULE__, __VA_ARGS__)
#define GET_TOKEN(...) MACRO2_FOR_EACH(GET_TOKEN__, __VA_ARGS__)
#define GET_TOKEN__TOKEN_IMPL(token_, str_) ,token_
 

#define tokens(contents_) ,TOKENS_IMPL(COMPILER contents_)
#define H_TOKENS__TOKENS_IMPL(compilerName_, ...) \
typedef enum \
{ \
    MACRO2_FOR_EACH(ENUM__, __VA_ARGS__) \
} compilerName_##TokenType; \
const char* compilerName_##token_patterns[] = { \
    MACRO2_FOR_EACH(STR__, __VA_ARGS__) \
}; \
int compilerName_##token_count = GET_ARG_COUNT(__VA_ARGS__); \
MACRO2_FOR_EACH(TOKEN_RULE__, __VA_ARGS__)
#define H_IGNORE_TOKENS__TOKENS_IMPL(placeholder_, ...)
#define H_ITERATION_STEP__TOKENS_IMPL(placeholder_, ...)
#define H_ITERATION_STEP_CALL__TOKENS_IMPL(placeholder_, ...)
#define H_NODE__TOKENS_IMPL(placeholder_, ...)
#define H_NODE_CREATE__TOKENS_IMPL(placeholder_, ...)
#define H_EXPAND__TOKENS_IMPL(placeholder, ...) 
#define H_EXPAND_TOKENS__TOKENS_IMPL(placeholder, ...) __VA_ARGS__
#define H_GET_ITERATION_NAME__TOKENS_IMPL(placeholder, ...)
#define TOKEN_H_GET_ITERATION_NAME__TOKENS_IMPL(placeholder, ...) ,__VA_ARGS__
#define H_ITERATION_MACRO__TOKENS_IMPL(placeholder, ...) NOTHING
#define CONTINUE_H_ITERATION_MACRO__TOKENS_IMPL(placeholder, ...) NOTHING
#define TOKEN_H_ITERATION_MACRO__TOKENS_IMPL(placeholder, ...) TOKEN_H_DECLARE_ITERATION

#define ignoreTokens(...) ,IGNORE_TOKENS_IMPL(__VA_ARGS__)
#define H_TOKENS__IGNORE_TOKENS_IMPL(...)
#define H_IGNORE_TOKENS__IGNORE_TOKENS_IMPL(...) H_IGNORE_TOKENS__IGNORE_TOKENS_IMPL_IMPL(COMPILER, __VA_ARGS__)
#define H_IGNORE_TOKENS__IGNORE_TOKENS_IMPL_IMPL(compilerName_, ...) H_IGNORE_TOKENS__IGNORE_TOKENS_IMPL_IMPL_IMPL(compilerName_, __VA_ARGS__)
#define H_IGNORE_TOKENS__IGNORE_TOKENS_IMPL_IMPL_IMPL(compilerName_, ...) \
int compilerName_##ignore_token(int i) \
{ \
    if (0 \
        RUN_MACRO_FOR_EACH(TOKEN_OR, __VA_ARGS__) \
    ) \
    { \
        return 1; \
    } \
    return 0; \
}
#define H_ITERATION_STEP__IGNORE_TOKENS_IMPL(...)
#define H_ITERATION_STEP_CALL__IGNORE_TOKENS_IMPL(...)
#define H_NODE__IGNORE_TOKENS_IMPL(...)
#define H_NODE_CREATE__IGNORE_TOKENS_IMPL(...)
#define H_EXPAND__IGNORE_TOKENS_IMPL(...)
#define H_EXPAND_TOKENS__IGNORE_TOKENS_IMPL(...)
#define H_GET_ITERATION_NAME__IGNORE_TOKENS_IMPL(...)
#define TOKEN_H_GET_ITERATION_NAME__IGNORE_TOKENS_IMPL(...)
#define H_ITERATION_MACRO__IGNORE_TOKENS_IMPL(...) NOTHING
#define CONTINUE_H_ITERATION_MACRO__IGNORE_TOKENS_IMPL(...) NOTHING
#define TOKEN_H_ITERATION_MACRO__IGNORE_TOKENS_IMPL(...) NOTHING

#define recurseStep(name_) ,ITERATION_STEP_IMPL(COMPILER, name_)
#define H_TOKENS__ITERATION_STEP_IMPL(compilerName_, name_)
#define H_IGNORE_TOKENS__ITERATION_STEP_IMPL(compilerName_, name_)
#define H_ITERATION_STEP__ITERATION_STEP_IMPL(compilerName_, name_)
#define H_ITERATION_STEP_CALL__ITERATION_STEP_IMPL(compilerName_, name_) compilerName_##name_##Root(compilerName_##Out, root, compilerName_##name_##Root##ContinueVoid);
#define H_NODE__ITERATION_STEP_IMPL(compilerName_, name_)
#define H_NODE_CREATE__ITERATION_STEP_IMPL(compilerName_, name_)
#define H_EXPAND__ITERATION_STEP_IMPL(compilerName_, name_)
#define H_EXPAND_TOKENS__ITERATION_STEP_IMPL(compilerName_, name_)
#define H_GET_ITERATION_NAME__ITERATION_STEP_IMPL(compilerName_, name_) ,name_
#define TOKEN_H_GET_ITERATION_NAME__ITERATION_STEP_IMPL(compilerName_, name_)
#define H_ITERATION_MACRO__ITERATION_STEP_IMPL(compilerName_, name_) NOTHING
#define CONTINUE_H_ITERATION_MACRO__ITERATION_STEP_IMPL(compilerName_, name_) NOTHING
#define TOKEN_H_ITERATION_MACRO__ITERATION_STEP_IMPL(compilerName_, name_) NOTHING


#define node(contents_) ,NODE_IMPL(COMPILER, contents_)
#define H_TOKENS__NODE_IMPL(compilerName_, name_, ...)
#define H_IGNORE_TOKENS__NODE_IMPL(compilerName_, name_, ...)
#define H_ITERATION_STEP__NODE_IMPL(compilerName_, name_, ...)
#define H_ITERATION_STEP_CALL__NODE_IMPL(compilerName_, name_, ...)
#define H_NODE__NODE_IMPL(compilerName_, name_, ...) \
typedef struct compilerName_##name_ \
{ \
    MACRO2_FOR_EACH(VAR_DECLARE__, __VA_ARGS__) \
    MACRO2_FOR_EACH(INDEX_VAR__, __VA_ARGS__) \
    MACRO2_FOR_EACH(UNION_START__, __VA_ARGS__) \
    MACRO2_FOR_EACH(UNION__, __VA_ARGS__) \
    MACRO2_FOR_EACH(UNION_END__, __VA_ARGS__) \
} compilerName_##name_; \
struct compilerName_##name_* compilerName_##Create##name_(struct compilerName_##TokenBatch* batch);
#define H_NODE_CREATE__NODE_IMPL(compilerName_, name_, ...) \
struct compilerName_##name_ * compilerName_##Create##name_(struct compilerName_##TokenBatch* batch) \
{ \
    int current_token = batch->token_on; \
    int end_token = current_token; \
    struct compilerName_##name_ * var_0 = (void*)0; \
    MACRO2_FOR_EACH(CREATE__, __VA_ARGS__) \
    MACRO2_FOR_EACH(CREATE_MALLOC__, __VA_ARGS__) \
    MACRO2_FOR_EACH(CREATE_CHECK_ALL__, __VA_ARGS__) \
    MACRO2_FOR_EACH(CREATE_END__, __VA_ARGS__) \
}

#define H_EXPAND__NODE_IMPL(compilerName_, name_, ...) name_, __VA_ARGS__
#define H_EXPAND_TOKENS__NODE_IMPL(compilerName_, name_, ...)
#define H_GET_ITERATION_NAME__NODE_IMPL(compilerName_, name_, ...)
#define TOKEN_H_GET_ITERATION_NAME__NODE_IMPL(compilerName_, name_, ...)
#define H_ITERATION_MACRO__NODE_IMPL(compilerName_, name_, ...) H_DECLARE_ITERATION
#define CONTINUE_H_ITERATION_MACRO__NODE_IMPL(compilerName_, name_, ...) CONTINUE_H_DECLARE_ITERATION
#define TOKEN_H_ITERATION_MACRO__NODE_IMPL(compilerName_, name_, ...) NOTHING
    

#define nodeNext(contents_) ,NODE_NEXT_IMPL(COMPILER, contents_)
#define H_TOKENS__NODE_NEXT_IMPL(compilerName_, name_, ...)
#define H_IGNORE_TOKENS__NODE_NEXT_IMPL(compilerName_, name_, ...)
#define H_ITERATION_STEP__NODE_NEXT_IMPL(compilerName_, name_, ...)
#define H_ITERATION_STEP_CALL__NODE_NEXT_IMPL(compilerName_, name_, ...)
#define H_NODE__NODE_NEXT_IMPL(compilerName_, name_, ...) \
typedef struct compilerName_##name_ \
{ \
    MACRO2_FOR_EACH(VAR_DECLARE__, __VA_ARGS__) \
    MACRO2_FOR_EACH(INDEX_VAR__, __VA_ARGS__) \
    MACRO2_FOR_EACH(UNION_START__, __VA_ARGS__) \
    MACRO2_FOR_EACH(UNION__, __VA_ARGS__) \
    MACRO2_FOR_EACH(UNION_END__, __VA_ARGS__) \
    struct compilerName_##name_ * next; \
} compilerName_##name_; \
struct compilerName_##name_* compilerName_##Create##name_(struct compilerName_##TokenBatch* batch);
#define H_NODE_CREATE__NODE_NEXT_IMPL(compilerName_, name_, ...) \
struct compilerName_##name_ * compilerName_##Create##name_(struct compilerName_##TokenBatch* batch) \
{ \
    int current_token = batch->token_on; \
    int end_token = current_token; \
    struct compilerName_##name_ * var_0 = (void*)0; \
    struct compilerName_##name_ * (*func)(struct compilerName_##TokenBatch*) = compilerName_##Create##name_; \
    MACRO2_FOR_EACH(CREATE__, __VA_ARGS__) \
    MACRO2_FOR_EACH(CREATE_MALLOC__, __VA_ARGS__) \
    MACRO2_FOR_EACH(NEXT_CREATE_CHECK_ALL__, __VA_ARGS__) \
    MACRO2_FOR_EACH(NEXT_CREATE_END__, __VA_ARGS__) \
}

#define H_EXPAND__NODE_NEXT_IMPL(compilerName_, name_, ...) name_, __VA_ARGS__
#define H_EXPAND_TOKENS__NODE_NEXT_IMPL(compilerName_, name_, ...)
#define H_GET_ITERATION_NAME__NODE_NEXT_IMPL(compilerName_, name_, ...)
#define TOKEN_H_GET_ITERATION_NAME__NODE_NEXT_IMPL(compilerName_, name_, ...)
#define H_ITERATION_MACRO__NODE_NEXT_IMPL(compilerName_, name_, ...) H_DECLARE_ITERATION
#define CONTINUE_H_ITERATION_MACRO__NODE_NEXT_IMPL(compilerName_, name_, ...) NEXT_CONTINUE_H_DECLARE_ITERATION
#define TOKEN_H_ITERATION_MACRO__NODE_NEXT_IMPL(compilerName_, name_, ...) TOKEN_H_DECLARE_ITERATION

#define dep_token(name_, str_) ,TOKEN_IMPL(name_, "^$a")
#define token(name_, str_) ,TOKEN_IMPL(name_, str_)
#define ENUM__TOKEN_IMPL(name_, str_) ENUM__TOKEN_IMPL_IMPL(COMPILER, name_, str_)
#define ENUM__TOKEN_IMPL_IMPL(compilerName_, name_, str_) ENUM__TOKEN_IMPL_IMPL_IMPL(compilerName_, name_, str_)
#define ENUM__TOKEN_IMPL_IMPL_IMPL(compilerName_, name_, str_) compilerName_##TOKEN_##name_,

#define STR__TOKEN_IMPL(name_, str_) str_,
#define TOKEN_RULE__TOKEN_IMPL(name_, str_) TOKEN_RULE__TOKEN_IMPL_IMPL(COMPILER, name_, str_)
#define TOKEN_RULE__TOKEN_IMPL_IMPL(compilerName_, name_, str_) TOKEN_RULE__TOKEN_IMPL_IMPL_IMPL(compilerName_, name_, str_)
#define TOKEN_RULE__TOKEN_IMPL_IMPL_IMPL(compilerName_, name_, str_) \
typedef struct compilerName_##name_ \
{ \
    struct compilerName_##Token* token; \
} compilerName_##name_; \
struct compilerName_##name_ * compilerName_##Create##name_(struct compilerName_##TokenBatch* batch) \
{ \
    struct compilerName_##Token* token = &batch->tokens[batch->token_on]; \
    if (token->type == compilerName_##TOKEN_##name_) \
    { \
        compilerName_##name_ * var_0 = compilerName_##AddToCollector(malloc(sizeof(struct compilerName_##name_))); \
        var_0->token = token; \
        batch->token_on++; \
        return var_0; \
    } \
    return (void*)0; \
}



#define TOKEN_OR(v_) TOKEN_OR_IMPL(COMPILER, v_)
#define TOKEN_OR_IMPL(compilerName_, v_) TOKEN_OR_IMPL_IMPL(compilerName_, v_)
#define TOKEN_OR_IMPL_IMPL(compilerName_, v_) || i == compilerName_##TOKEN_##v_



#define allRule(...) ,ALL_RULE_IMPL(__VA_ARGS__)
#define UNION__ALL_RULE_IMPL(...) INDEXED_RUN_MACRO_FOR_EACH(UNION_RULE, __VA_ARGS__)
#define VAR_DECLARE__ALL_RULE_IMPL(...)
#define UNION_START__ALL_RULE_IMPL(...)
#define UNION_END__ALL_RULE_IMPL(...)
#define INDEX_VAR__ALL_RULE_IMPL(...)
#define CREATE_MALLOC__ALL_RULE_IMPL(...) CREATE_MALLOC__ALL_RULE_IMPL_IMPL(COMPILER, ...)
#define CREATE_MALLOC__ALL_RULE_IMPL_IMPL(compilerName_, ...) CREATE_MALLOC__ALL_RULE_IMPL_IMPL_IMPL(compilerName_, __VA_ARGS__)
#define CREATE_MALLOC__ALL_RULE_IMPL_IMPL_IMPL(compilerName_, ...) var_0 = compilerName_##AddToCollector(malloc(sizeof(*var_0)));


#define CREATE_END__ALL_RULE_IMPL(...) return var_0;
#define NEXT_CREATE_END__ALL_RULE_IMPL(...) var_0->next = func(batch); return var_0;
#define CREATE__ALL_RULE_IMPL(...) INDEXED_RUN_MACRO_FOR_EACH(ALL_CREATE_CHECK_NODE, __VA_ARGS__)
#define CREATE_CHECK_ALL__ALL_RULE_IMPL(...) INDEXED_RUN_MACRO_FOR_EACH(ALL_SET_NODE, __VA_ARGS__)
#define NEXT_CREATE_CHECK_ALL__ALL_RULE_IMPL(...) INDEXED_RUN_MACRO_FOR_EACH(ALL_SET_NODE, __VA_ARGS__)
#define GET_RULE__ALL_RULE_IMPL(...) ALL_RULE_ITERATION(__VA_ARGS__)

#define ALL_CREATE_CHECK_NODE(name_, n_) ALL_CREATE_CHECK_NODE_IMPL(COMPILER, name_, n_)
#define ALL_CREATE_CHECK_NODE_IMPL(compilerName_, name_, n_) ALL_CREATE_CHECK_NODE_IMPL_IMPL(compilerName_, name_, n_)
#define ALL_CREATE_CHECK_NODE_IMPL_IMPL(compilerName_, name_, n_) struct compilerName_##name_ * var_##n_ = compilerName_##Create##name_(batch); if (!var_##n_) {batch->token_on = current_token; return (void*)(0);}

#define ALL_SET_NODE(name_, n_) var_0->var_##n_ = var_##n_;


#define anyRule(...) ,ANY_RULE_IMPL(__VA_ARGS__)
#define UNION__ANY_RULE_IMPL(...) INDEXED_RUN_MACRO_FOR_EACH(UNION_RULE, __VA_ARGS__)
#define VAR_DECLARE__ANY_RULE_IMPL(...)
#define UNION_START__ANY_RULE_IMPL(...) union {
#define UNION_END__ANY_RULE_IMPL(...) } var;
#define INDEX_VAR__ANY_RULE_IMPL(...) int var_index;
#define CREATE_MALLOC__ANY_RULE_IMPL(...)
#define CREATE_END__ANY_RULE_IMPL(...) batch->token_on = end_token; return var_0;
#define NEXT_CREATE_END__ANY_RULE_IMPL(...) batch->token_on = end_token;  return var_0;
#define CREATE__ANY_RULE_IMPL(...)
#define CREATE_CHECK_ALL__ANY_RULE_IMPL(...) INDEXED_RUN_MACRO_FOR_EACH(ANY_SET_NODE, __VA_ARGS__)
#define NEXT_CREATE_CHECK_ALL__ANY_RULE_IMPL(...) INDEXED_RUN_MACRO_FOR_EACH(NEXT_ANY_SET_NODE, __VA_ARGS__)
#define GET_RULE__ANY_RULE_IMPL(...) ANY_RULE_ITERATION(__VA_ARGS__)

#define ANY_SET_NODE(name_, n_) ANY_SET_NODE_IMPL(COMPILER, name_, n_)
#define ANY_SET_NODE_IMPL(compilerName_, name_, n_) ANY_SET_NODE_IMPL_IMPL(compilerName_, name_, n_)
#define ANY_SET_NODE_IMPL_IMPL(compilerName_, name_, n_) \
batch->token_on = current_token; \
struct compilerName_##name_ * var_##n_ = compilerName_##Create##name_(batch); \
if (var_##n_ && !var_0) \
{ \
    var_0 = compilerName_##AddToCollector(malloc(sizeof(*var_0))); \
    var_0->var_index = n_; \
    var_0->var.var_##n_ = var_##n_; \
    end_token = batch->token_on; \
}

#define NEXT_ANY_SET_NODE(name_, n_) NEXT_ANY_SET_NODE_IMPL(COMPILER, name_, n_)
#define NEXT_ANY_SET_NODE_IMPL(compilerName_, name_, n_) NEXT_ANY_SET_NODE_IMPL_IMPL(compilerName_, name_, n_)
#define NEXT_ANY_SET_NODE_IMPL_IMPL(compilerName_, name_, n_) \
batch->token_on = current_token; \
struct compilerName_##name_ * var_##n_ = compilerName_##Create##name_(batch); \
if (var_##n_ && !var_0) \
{ \
    var_0 = compilerName_##AddToCollector(malloc(sizeof(*var_0))); \
    var_0->var_index = n_; \
    var_0->var.var_##n_ = var_##n_; \
    var_0->next = func(batch); \
    end_token = batch->token_on; \
}

#define var(type_, name_) ,VAR_IMPL(type_, name_)
#define UNION__VAR_IMPL(type_, name_)
#define VAR_DECLARE__VAR_IMPL(type_, name_) type_ name_;
#define UNION_START__VAR_IMPL(type_, name_)
#define UNION_END__VAR_IMPL(type_, name_)
#define INDEX_VAR__VAR_IMPL(type_, name_)
#define CREATE_MALLOC__VAR_IMPL(type_, name_)
#define CREATE_END__VAR_IMPL(type_, name_)
#define NEXT_CREATE_END__VAR_IMPL(type_, name_)
#define CREATE__VAR_IMPL(type_, name_)
#define CREATE_CHECK_ALL__VAR_IMPL(type_, name_)
#define NEXT_CREATE_CHECK_ALL__VAR_IMPL(type_, name_)
#define GET_RULE__VAR_IMPL(type_, name_)

#define ENUM_RULE(name_, n_) name_##_##n_,
#define UNION_RULE(name_, n_) UNION_RULE_IMPL(COMPILER, name_, n_)
#define UNION_RULE_IMPL(compilerName_, name_, n_) UNION_RULE_IMPL_IMPL(compilerName_, name_, n_)
#define UNION_RULE_IMPL_IMPL(compilerName_, name_, n_) struct compilerName_##name_ * var##_##n_;



#define MACRO_EXPAND(...) MACRO_EXPAND4(MACRO_EXPAND4(MACRO_EXPAND4(MACRO_EXPAND4(__VA_ARGS__))))
#define MACRO_EXPAND4(...) MACRO_EXPAND3(MACRO_EXPAND3(MACRO_EXPAND3(MACRO_EXPAND3(__VA_ARGS__))))
#define MACRO_EXPAND3(...) MACRO_EXPAND2(MACRO_EXPAND2(MACRO_EXPAND2(MACRO_EXPAND2(__VA_ARGS__))))
#define MACRO_EXPAND2(...) MACRO_EXPAND1(MACRO_EXPAND1(MACRO_EXPAND1(MACRO_EXPAND1(__VA_ARGS__))))
#define MACRO_EXPAND1(...) __VA_ARGS__

#define MACRO_FOR_EACH(macro, ...)                                    \
  __VA_OPT__(MACRO_EXPAND(MACRO_FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define MACRO_FOR_EACH_HELPER(macro, a1, ...)                         \
  macro##a1                                                     \
  __VA_OPT__(MACRO_FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define MACRO_FOR_EACH_AGAIN() MACRO_FOR_EACH_HELPER

#define MACRO_NODE_EXPAND(...)  MACRO_NODE_EXPAND4(MACRO_NODE_EXPAND4(MACRO_NODE_EXPAND4(MACRO_NODE_EXPAND4(__VA_ARGS__))))
#define MACRO_NODE_EXPAND4(...) MACRO_NODE_EXPAND3(MACRO_NODE_EXPAND3(MACRO_NODE_EXPAND3(MACRO_NODE_EXPAND3(__VA_ARGS__))))
#define MACRO_NODE_EXPAND3(...) MACRO_NODE_EXPAND2(MACRO_NODE_EXPAND2(MACRO_NODE_EXPAND2(MACRO_NODE_EXPAND2(__VA_ARGS__))))
#define MACRO_NODE_EXPAND2(...) MACRO_NODE_EXPAND1(MACRO_NODE_EXPAND1(MACRO_NODE_EXPAND1(MACRO_NODE_EXPAND1(__VA_ARGS__))))
#define MACRO_NODE_EXPAND1(...) __VA_ARGS__

#define MACRO_NODE_FOR_EACH(out_macro, in_macro, n, ...)                                    \
  __VA_OPT__(MACRO_NODE_EXPAND(MACRO_NODE_FOR_EACH_HELPER(out_macro, in_macro, n, __VA_ARGS__)))
#define MACRO_NODE_FOR_EACH_HELPER(out_macro, in_macro, n, a1, ...)                         \
  MACRO_NODE_FOR_EACH_IMPL(out_macro##a1, n, in_macro, a1)  \
  __VA_OPT__(MACRO_NODE_FOR_EACH_AGAIN PARENS (out_macro, in_macro, n, __VA_ARGS__))
#define MACRO_NODE_FOR_EACH_AGAIN() MACRO_NODE_FOR_EACH_HELPER
#define MACRO_NODE_FOR_EACH_IMPL(out_macro, n, in_macro, a1) out_macro(n, in_macro##a1)                                                     

#define MACRO2_EXPAND(...) MACRO2_EXPAND4(MACRO2_EXPAND4(MACRO2_EXPAND4(MACRO2_EXPAND4(__VA_ARGS__))))
#define MACRO2_EXPAND4(...) MACRO2_EXPAND3(MACRO2_EXPAND3(MACRO2_EXPAND3(MACRO2_EXPAND3(__VA_ARGS__))))
#define MACRO2_EXPAND3(...) MACRO2_EXPAND2(MACRO2_EXPAND2(MACRO2_EXPAND2(MACRO2_EXPAND2(__VA_ARGS__))))
#define MACRO2_EXPAND2(...) MACRO2_EXPAND1(MACRO2_EXPAND1(MACRO2_EXPAND1(MACRO2_EXPAND1(__VA_ARGS__))))
#define MACRO2_EXPAND1(...) __VA_ARGS__

#define MACRO2_FOR_EACH(macro, ...)                                    \
  __VA_OPT__(MACRO2_EXPAND(MACRO2_FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define MACRO2_FOR_EACH_HELPER(macro, a1, ...)                         \
  macro##a1                                                     \
  __VA_OPT__(MACRO2_FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define MACRO2_FOR_EACH_AGAIN() MACRO2_FOR_EACH_HELPER


#define RUN_MACRO_EXPAND(...) RUN_MACRO_EXPAND4(RUN_MACRO_EXPAND4(RUN_MACRO_EXPAND4(RUN_MACRO_EXPAND4(__VA_ARGS__))))
#define RUN_MACRO_EXPAND4(...) RUN_MACRO_EXPAND3(RUN_MACRO_EXPAND3(RUN_MACRO_EXPAND3(RUN_MACRO_EXPAND3(__VA_ARGS__))))
#define RUN_MACRO_EXPAND3(...) RUN_MACRO_EXPAND2(RUN_MACRO_EXPAND2(RUN_MACRO_EXPAND2(RUN_MACRO_EXPAND2(__VA_ARGS__))))
#define RUN_MACRO_EXPAND2(...) RUN_MACRO_EXPAND1(RUN_MACRO_EXPAND1(RUN_MACRO_EXPAND1(RUN_MACRO_EXPAND1(__VA_ARGS__))))
#define RUN_MACRO_EXPAND1(...) __VA_ARGS__

#define RUN_MACRO_FOR_EACH(macro, ...)                                    \
  __VA_OPT__(RUN_MACRO_EXPAND(RUN_MACRO_FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define RUN_MACRO_FOR_EACH_HELPER(macro, a1, ...)                         \
  macro(a1)                                                     \
  __VA_OPT__(RUN_MACRO_FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define RUN_MACRO_FOR_EACH_AGAIN() RUN_MACRO_FOR_EACH_HELPER

#define RUN_ITERATION_MACRO_EXPAND(...)  RUN_ITERATION_MACRO_EXPAND4(RUN_ITERATION_MACRO_EXPAND4(RUN_ITERATION_MACRO_EXPAND4(RUN_ITERATION_MACRO_EXPAND4(__VA_ARGS__))))
#define RUN_ITERATION_MACRO_EXPAND4(...) RUN_ITERATION_MACRO_EXPAND3(RUN_ITERATION_MACRO_EXPAND3(RUN_ITERATION_MACRO_EXPAND3(RUN_ITERATION_MACRO_EXPAND3(__VA_ARGS__))))
#define RUN_ITERATION_MACRO_EXPAND3(...) RUN_ITERATION_MACRO_EXPAND2(RUN_ITERATION_MACRO_EXPAND2(RUN_ITERATION_MACRO_EXPAND2(RUN_ITERATION_MACRO_EXPAND2(__VA_ARGS__))))
#define RUN_ITERATION_MACRO_EXPAND2(...) RUN_ITERATION_MACRO_EXPAND1(RUN_ITERATION_MACRO_EXPAND1(RUN_ITERATION_MACRO_EXPAND1(RUN_ITERATION_MACRO_EXPAND1(__VA_ARGS__))))
#define RUN_ITERATION_MACRO_EXPAND1(...) __VA_ARGS__

#define RUN_ITERATION_MACRO_FOR_EACH(macro, name_, ...)                                    \
  __VA_OPT__(RUN_ITERATION_MACRO_EXPAND(RUN_ITERATION_MACRO_FOR_EACH_HELPER(macro, name_, __VA_ARGS__)))
#define RUN_ITERATION_MACRO_FOR_EACH_HELPER(macro, name_, a1, a2, ...)                         \
  macro(a1, name_, a2)                                                     \
  __VA_OPT__(RUN_ITERATION_MACRO_FOR_EACH_AGAIN PARENS (macro, name_, __VA_ARGS__))
#define RUN_ITERATION_MACRO_FOR_EACH_AGAIN() RUN_ITERATION_MACRO_FOR_EACH_HELPER

#define RUN_X_X_MACRO_EXPAND(...)  RUN_X_X_MACRO_EXPAND4(RUN_X_X_MACRO_EXPAND4(RUN_X_X_MACRO_EXPAND4(RUN_X_X_MACRO_EXPAND4(__VA_ARGS__))))
#define RUN_X_X_MACRO_EXPAND4(...) RUN_X_X_MACRO_EXPAND3(RUN_X_X_MACRO_EXPAND3(RUN_X_X_MACRO_EXPAND3(RUN_X_X_MACRO_EXPAND3(__VA_ARGS__))))
#define RUN_X_X_MACRO_EXPAND3(...) RUN_X_X_MACRO_EXPAND2(RUN_X_X_MACRO_EXPAND2(RUN_X_X_MACRO_EXPAND2(RUN_X_X_MACRO_EXPAND2(__VA_ARGS__))))
#define RUN_X_X_MACRO_EXPAND2(...) RUN_X_X_MACRO_EXPAND1(RUN_X_X_MACRO_EXPAND1(RUN_X_X_MACRO_EXPAND1(RUN_X_X_MACRO_EXPAND1(__VA_ARGS__))))
#define RUN_X_X_MACRO_EXPAND1(...) __VA_ARGS__

#define RUN_X_X_MACRO_FOR_EACH(macro, x1, x2, ...)                                    \
  __VA_OPT__(RUN_X_X_MACRO_EXPAND(RUN_X_X_MACRO_FOR_EACH_HELPER(macro, x1, x2, __VA_ARGS__)))
#define RUN_X_X_MACRO_FOR_EACH_HELPER(macro, x1, x2, a1, ...)                         \
  macro(x1, x2, a1)                                                     \
  __VA_OPT__(RUN_X_X_MACRO_FOR_EACH_AGAIN PARENS (macro, x1, x2, __VA_ARGS__))
#define RUN_X_X_MACRO_FOR_EACH_AGAIN() RUN_X_X_MACRO_FOR_EACH_HELPER

#define RUN_X_MACRO_EXPAND(...)  RUN_X_MACRO_EXPAND4(RUN_X_MACRO_EXPAND4(RUN_X_MACRO_EXPAND4(RUN_X_MACRO_EXPAND4(__VA_ARGS__))))
#define RUN_X_MACRO_EXPAND4(...) RUN_X_MACRO_EXPAND3(RUN_X_MACRO_EXPAND3(RUN_X_MACRO_EXPAND3(RUN_X_MACRO_EXPAND3(__VA_ARGS__))))
#define RUN_X_MACRO_EXPAND3(...) RUN_X_MACRO_EXPAND2(RUN_X_MACRO_EXPAND2(RUN_X_MACRO_EXPAND2(RUN_X_MACRO_EXPAND2(__VA_ARGS__))))
#define RUN_X_MACRO_EXPAND2(...) RUN_X_MACRO_EXPAND1(RUN_X_MACRO_EXPAND1(RUN_X_MACRO_EXPAND1(RUN_X_MACRO_EXPAND1(__VA_ARGS__))))
#define RUN_X_MACRO_EXPAND1(...) __VA_ARGS__

#define RUN_X_MACRO_FOR_EACH(macro, x1, ...)                                    \
  __VA_OPT__(RUN_X_MACRO_EXPAND(RUN_X_MACRO_FOR_EACH_HELPER(macro, x1, __VA_ARGS__)))
#define RUN_X_MACRO_FOR_EACH_HELPER(macro, x1, a1, ...)                         \
  macro(x1, a1)                                                     \
  __VA_OPT__(RUN_X_MACRO_FOR_EACH_AGAIN PARENS (macro, x1, __VA_ARGS__))
#define RUN_X_MACRO_FOR_EACH_AGAIN() RUN_X_MACRO_FOR_EACH_HELPER

#define INDEXED_RUN_MACRO_EXPAND(...)  INDEXED_RUN_MACRO_EXPAND4(INDEXED_RUN_MACRO_EXPAND4(INDEXED_RUN_MACRO_EXPAND4(INDEXED_RUN_MACRO_EXPAND4(__VA_ARGS__))))
#define INDEXED_RUN_MACRO_EXPAND4(...) INDEXED_RUN_MACRO_EXPAND3(INDEXED_RUN_MACRO_EXPAND3(INDEXED_RUN_MACRO_EXPAND3(INDEXED_RUN_MACRO_EXPAND3(__VA_ARGS__))))
#define INDEXED_RUN_MACRO_EXPAND3(...) INDEXED_RUN_MACRO_EXPAND2(INDEXED_RUN_MACRO_EXPAND2(INDEXED_RUN_MACRO_EXPAND2(INDEXED_RUN_MACRO_EXPAND2(__VA_ARGS__))))
#define INDEXED_RUN_MACRO_EXPAND2(...) INDEXED_RUN_MACRO_EXPAND1(INDEXED_RUN_MACRO_EXPAND1(INDEXED_RUN_MACRO_EXPAND1(INDEXED_RUN_MACRO_EXPAND1(__VA_ARGS__))))
#define INDEXED_RUN_MACRO_EXPAND1(...) __VA_ARGS__

#define INDEXED_RUN_MACRO_FOR_EACH(macro, ...)                                    \
  __VA_OPT__(INDEXED_RUN_MACRO_EXPAND(INDEXED_RUN_MACRO_FOR_EACH_HELPER(macro, 1, __VA_ARGS__)))
#define INDEXED_RUN_MACRO_FOR_EACH_HELPER(macro, n, a1, ...)                         \
  macro(a1,n)                                                     \
  __VA_OPT__(INDEXED_RUN_MACRO_FOR_EACH_AGAIN PARENS (macro, inc_##n, __VA_ARGS__))
#define INDEXED_RUN_MACRO_FOR_EACH_AGAIN() INDEXED_RUN_MACRO_FOR_EACH_HELPER

#define INDEXED_X_RUN_MACRO_EXPAND(...)  INDEXED_X_RUN_MACRO_EXPAND4(INDEXED_X_RUN_MACRO_EXPAND4(INDEXED_X_RUN_MACRO_EXPAND4(INDEXED_X_RUN_MACRO_EXPAND4(__VA_ARGS__))))
#define INDEXED_X_RUN_MACRO_EXPAND4(...) INDEXED_X_RUN_MACRO_EXPAND3(INDEXED_X_RUN_MACRO_EXPAND3(INDEXED_X_RUN_MACRO_EXPAND3(INDEXED_X_RUN_MACRO_EXPAND3(__VA_ARGS__))))
#define INDEXED_X_RUN_MACRO_EXPAND3(...) INDEXED_X_RUN_MACRO_EXPAND2(INDEXED_X_RUN_MACRO_EXPAND2(INDEXED_X_RUN_MACRO_EXPAND2(INDEXED_X_RUN_MACRO_EXPAND2(__VA_ARGS__))))
#define INDEXED_X_RUN_MACRO_EXPAND2(...) INDEXED_X_RUN_MACRO_EXPAND1(INDEXED_X_RUN_MACRO_EXPAND1(INDEXED_X_RUN_MACRO_EXPAND1(INDEXED_X_RUN_MACRO_EXPAND1(__VA_ARGS__))))
#define INDEXED_X_RUN_MACRO_EXPAND1(...) __VA_ARGS__

#define INDEXED_X_RUN_MACRO_FOR_EACH(macro, x, ...)                                    \
  __VA_OPT__(INDEXED_X_RUN_MACRO_EXPAND(INDEXED_X_RUN_MACRO_FOR_EACH_HELPER(macro, x, 1, __VA_ARGS__)))
#define INDEXED_X_RUN_MACRO_FOR_EACH_HELPER(macro, x, n, a1, ...)                         \
  macro(a1,x,n)                                                     \
  __VA_OPT__(INDEXED_X_RUN_MACRO_FOR_EACH_AGAIN PARENS (macro, x, inc_##n, __VA_ARGS__))
#define INDEXED_X_RUN_MACRO_FOR_EACH_AGAIN() INDEXED_X_RUN_MACRO_FOR_EACH_HELPER