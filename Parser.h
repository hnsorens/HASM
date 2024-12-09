#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <regex.h>
#include <string.h>

const char* filename;

typedef struct Scope_Table
{
    void** data;
    int size;
    int capacity;
} Scope_Table;

struct Scope_Table* Init_Scope_Table()
{
    struct Scope_Table* array = malloc(sizeof(Scope_Table));
    array->capacity = 128;
    array->size = 0;
    array->data = (void**)malloc(array->capacity * sizeof(void*));
    return array;
}

void Add_Scope_Table(struct Scope_Table* array, void* p)
{
    if (array->capacity == array->size)
    {
        array->capacity += 128;
        array->data = (void**)realloc(array->data, array->capacity * sizeof(void*));
    }
    array->data[array->size++] = p;
}
void print_white(int num)
{
    for (int i = 0; i < num; i++)
    {
        printf("| ");
    }
}

#define PARENS ()

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

#define RULE_EXPAND_0(rule, macro) 
#define RULE_EXPAND_1(rule, macro, _1) macro##_RULE_IMPL(_1, rule, 1)
#define RULE_EXPAND_2(rule, macro, _1, _2) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2)
#define RULE_EXPAND_3(rule, macro, _1, _2, _3) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3)
#define RULE_EXPAND_4(rule, macro, _1, _2, _3, _4) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4)
#define RULE_EXPAND_5(rule, macro, _1, _2, _3, _4, _5) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5)
#define RULE_EXPAND_6(rule, macro, _1, _2, _3, _4, _5, _6) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6)
#define RULE_EXPAND_7(rule, macro, _1, _2, _3, _4, _5, _6, _7) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7)
#define RULE_EXPAND_8(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8)
#define RULE_EXPAND_9(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9)
#define RULE_EXPAND_10(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10)
#define RULE_EXPAND_11(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11)
#define RULE_EXPAND_12(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12)
#define RULE_EXPAND_13(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13)
#define RULE_EXPAND_14(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14)
#define RULE_EXPAND_15(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15)
#define RULE_EXPAND_16(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16)
#define RULE_EXPAND_17(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17)
#define RULE_EXPAND_18(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18)
#define RULE_EXPAND_19(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19)
#define RULE_EXPAND_20(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19) macro##_RULE_IMPL(_20, rule, 20)
#define RULE_EXPAND_21(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19) macro##_RULE_IMPL(_20, rule, 20) macro##_RULE_IMPL(_21, rule, 21)
#define RULE_EXPAND_22(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19) macro##_RULE_IMPL(_20, rule, 20) macro##_RULE_IMPL(_21, rule, 21) macro##_RULE_IMPL(_22, rule, 22)
#define RULE_EXPAND_23(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19) macro##_RULE_IMPL(_20, rule, 20) macro##_RULE_IMPL(_21, rule, 21) macro##_RULE_IMPL(_22, rule, 22) macro##_RULE_IMPL(_23, rule, 23)
#define RULE_EXPAND_24(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19) macro##_RULE_IMPL(_20, rule, 20) macro##_RULE_IMPL(_21, rule, 21) macro##_RULE_IMPL(_22, rule, 22) macro##_RULE_IMPL(_23, rule, 23) macro##_RULE_IMPL(_24, rule, 24)
#define RULE_EXPAND_25(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19) macro##_RULE_IMPL(_20, rule, 20) macro##_RULE_IMPL(_21, rule, 21) macro##_RULE_IMPL(_22, rule, 22) macro##_RULE_IMPL(_23, rule, 23) macro##_RULE_IMPL(_24, rule, 24) macro##_RULE_IMPL(_25, rule, 25)
#define RULE_EXPAND_26(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19) macro##_RULE_IMPL(_20, rule, 20) macro##_RULE_IMPL(_21, rule, 21) macro##_RULE_IMPL(_22, rule, 22) macro##_RULE_IMPL(_23, rule, 23) macro##_RULE_IMPL(_24, rule, 24) macro##_RULE_IMPL(_25, rule, 25) macro##_RULE_IMPL(_26, rule, 26)
#define RULE_EXPAND_27(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19) macro##_RULE_IMPL(_20, rule, 20) macro##_RULE_IMPL(_21, rule, 21) macro##_RULE_IMPL(_22, rule, 22) macro##_RULE_IMPL(_23, rule, 23) macro##_RULE_IMPL(_24, rule, 24) macro##_RULE_IMPL(_25, rule, 25) macro##_RULE_IMPL(_26, rule, 26) macro##_RULE_IMPL(_27, rule, 27)
#define RULE_EXPAND_28(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19) macro##_RULE_IMPL(_20, rule, 20) macro##_RULE_IMPL(_21, rule, 21) macro##_RULE_IMPL(_22, rule, 22) macro##_RULE_IMPL(_23, rule, 23) macro##_RULE_IMPL(_24, rule, 24) macro##_RULE_IMPL(_25, rule, 25) macro##_RULE_IMPL(_26, rule, 26) macro##_RULE_IMPL(_27, rule, 27) macro##_RULE_IMPL(_28, rule, 28)
#define RULE_EXPAND_29(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19) macro##_RULE_IMPL(_20, rule, 20) macro##_RULE_IMPL(_21, rule, 21) macro##_RULE_IMPL(_22, rule, 22) macro##_RULE_IMPL(_23, rule, 23) macro##_RULE_IMPL(_24, rule, 24) macro##_RULE_IMPL(_25, rule, 25) macro##_RULE_IMPL(_26, rule, 26) macro##_RULE_IMPL(_27, rule, 27) macro##_RULE_IMPL(_28, rule, 28) macro##_RULE_IMPL(_29, rule, 29)
#define RULE_EXPAND_30(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19) macro##_RULE_IMPL(_20, rule, 20) macro##_RULE_IMPL(_21, rule, 21) macro##_RULE_IMPL(_22, rule, 22) macro##_RULE_IMPL(_23, rule, 23) macro##_RULE_IMPL(_24, rule, 24) macro##_RULE_IMPL(_25, rule, 25) macro##_RULE_IMPL(_26, rule, 26) macro##_RULE_IMPL(_27, rule, 27) macro##_RULE_IMPL(_28, rule, 28) macro##_RULE_IMPL(_29, rule, 29) macro##_RULE_IMPL(_30, rule, 30)
#define RULE_EXPAND_31(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19) macro##_RULE_IMPL(_20, rule, 20) macro##_RULE_IMPL(_21, rule, 21) macro##_RULE_IMPL(_22, rule, 22) macro##_RULE_IMPL(_23, rule, 23) macro##_RULE_IMPL(_24, rule, 24) macro##_RULE_IMPL(_25, rule, 25) macro##_RULE_IMPL(_26, rule, 26) macro##_RULE_IMPL(_27, rule, 27) macro##_RULE_IMPL(_28, rule, 28) macro##_RULE_IMPL(_29, rule, 29) macro##_RULE_IMPL(_30, rule, 30) macro##_RULE_IMPL(_31, rule, 31)
#define RULE_EXPAND_32(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) macro##_RULE_IMPL(_1, rule, 1) macro##_RULE_IMPL(_2, rule, 2) macro##_RULE_IMPL(_3, rule, 3) macro##_RULE_IMPL(_4, rule, 4) macro##_RULE_IMPL(_5, rule, 5) macro##_RULE_IMPL(_6, rule, 6) macro##_RULE_IMPL(_7, rule, 7) macro##_RULE_IMPL(_8, rule, 8) macro##_RULE_IMPL(_9, rule, 9) macro##_RULE_IMPL(_10, rule, 10) macro##_RULE_IMPL(_11, rule, 11) macro##_RULE_IMPL(_12, rule, 12) macro##_RULE_IMPL(_13, rule, 13) macro##_RULE_IMPL(_14, rule, 14) macro##_RULE_IMPL(_15, rule, 15) macro##_RULE_IMPL(_16, rule, 16) macro##_RULE_IMPL(_17, rule, 17) macro##_RULE_IMPL(_18, rule, 18) macro##_RULE_IMPL(_19, rule, 19) macro##_RULE_IMPL(_20, rule, 20) macro##_RULE_IMPL(_21, rule, 21) macro##_RULE_IMPL(_22, rule, 22) macro##_RULE_IMPL(_23, rule, 23) macro##_RULE_IMPL(_24, rule, 24) macro##_RULE_IMPL(_25, rule, 25) macro##_RULE_IMPL(_26, rule, 26) macro##_RULE_IMPL(_27, rule, 27) macro##_RULE_IMPL(_28, rule, 28) macro##_RULE_IMPL(_29, rule, 29) macro##_RULE_IMPL(_30, rule, 30) macro##_RULE_IMPL(_31, rule, 31) macro##_RULE_IMPL(_32, rule, 32) 
#define RULE_EXPAND_33(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) macro##_RULE_IMPL(_1, rule, 1)macro##_RULE_IMPL(_2, rule, 2)macro##_RULE_IMPL(_3, rule, 3)macro##_RULE_IMPL(_4, rule, 4)macro##_RULE_IMPL(_5, rule, 5)macro##_RULE_IMPL(_6, rule, 6)macro##_RULE_IMPL(_7, rule, 7)macro##_RULE_IMPL(_8, rule, 8)macro##_RULE_IMPL(_9, rule, 9)macro##_RULE_IMPL(_10, rule, 10)macro##_RULE_IMPL(_11, rule, 11)macro##_RULE_IMPL(_12, rule, 12)macro##_RULE_IMPL(_13, rule, 13)macro##_RULE_IMPL(_14, rule, 14)macro##_RULE_IMPL(_15, rule, 15)macro##_RULE_IMPL(_16, rule, 16)macro##_RULE_IMPL(_17, rule, 17)macro##_RULE_IMPL(_18, rule, 18)macro##_RULE_IMPL(_19, rule, 19)macro##_RULE_IMPL(_20, rule, 20)macro##_RULE_IMPL(_21, rule, 21)macro##_RULE_IMPL(_22, rule, 22)macro##_RULE_IMPL(_23, rule, 23)macro##_RULE_IMPL(_24, rule, 24)macro##_RULE_IMPL(_25, rule, 25)macro##_RULE_IMPL(_26, rule, 26)macro##_RULE_IMPL(_27, rule, 27)macro##_RULE_IMPL(_28, rule, 28)macro##_RULE_IMPL(_29, rule, 29)macro##_RULE_IMPL(_30, rule, 30)macro##_RULE_IMPL(_31, rule, 31)macro##_RULE_IMPL(_32, rule, 32)macro##_RULE_IMPL(_33, rule, 33)
#define RULE_EXPAND_34(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) macro##_RULE_IMPL(_1, rule, 1)macro##_RULE_IMPL(_2, rule, 2)macro##_RULE_IMPL(_3, rule, 3)macro##_RULE_IMPL(_4, rule, 4)macro##_RULE_IMPL(_5, rule, 5)macro##_RULE_IMPL(_6, rule, 6)macro##_RULE_IMPL(_7, rule, 7)macro##_RULE_IMPL(_8, rule, 8)macro##_RULE_IMPL(_9, rule, 9)macro##_RULE_IMPL(_10, rule, 10)macro##_RULE_IMPL(_11, rule, 11)macro##_RULE_IMPL(_12, rule, 12)macro##_RULE_IMPL(_13, rule, 13)macro##_RULE_IMPL(_14, rule, 14)macro##_RULE_IMPL(_15, rule, 15)macro##_RULE_IMPL(_16, rule, 16)macro##_RULE_IMPL(_17, rule, 17)macro##_RULE_IMPL(_18, rule, 18)macro##_RULE_IMPL(_19, rule, 19)macro##_RULE_IMPL(_20, rule, 20)macro##_RULE_IMPL(_21, rule, 21)macro##_RULE_IMPL(_22, rule, 22)macro##_RULE_IMPL(_23, rule, 23)macro##_RULE_IMPL(_24, rule, 24)macro##_RULE_IMPL(_25, rule, 25)macro##_RULE_IMPL(_26, rule, 26)macro##_RULE_IMPL(_27, rule, 27)macro##_RULE_IMPL(_28, rule, 28)macro##_RULE_IMPL(_29, rule, 29)macro##_RULE_IMPL(_30, rule, 30)macro##_RULE_IMPL(_31, rule, 31)macro##_RULE_IMPL(_32, rule, 32)macro##_RULE_IMPL(_33, rule, 33)macro##_RULE_IMPL(_34, rule, 34)
#define RULE_EXPAND_35(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) macro##_RULE_IMPL(_1, rule, 1)macro##_RULE_IMPL(_2, rule, 2)macro##_RULE_IMPL(_3, rule, 3)macro##_RULE_IMPL(_4, rule, 4)macro##_RULE_IMPL(_5, rule, 5)macro##_RULE_IMPL(_6, rule, 6)macro##_RULE_IMPL(_7, rule, 7)macro##_RULE_IMPL(_8, rule, 8)macro##_RULE_IMPL(_9, rule, 9)macro##_RULE_IMPL(_10, rule, 10)macro##_RULE_IMPL(_11, rule, 11)macro##_RULE_IMPL(_12, rule, 12)macro##_RULE_IMPL(_13, rule, 13)macro##_RULE_IMPL(_14, rule, 14)macro##_RULE_IMPL(_15, rule, 15)macro##_RULE_IMPL(_16, rule, 16)macro##_RULE_IMPL(_17, rule, 17)macro##_RULE_IMPL(_18, rule, 18)macro##_RULE_IMPL(_19, rule, 19)macro##_RULE_IMPL(_20, rule, 20)macro##_RULE_IMPL(_21, rule, 21)macro##_RULE_IMPL(_22, rule, 22)macro##_RULE_IMPL(_23, rule, 23)macro##_RULE_IMPL(_24, rule, 24)macro##_RULE_IMPL(_25, rule, 25)macro##_RULE_IMPL(_26, rule, 26)macro##_RULE_IMPL(_27, rule, 27)macro##_RULE_IMPL(_28, rule, 28)macro##_RULE_IMPL(_29, rule, 29)macro##_RULE_IMPL(_30, rule, 30)macro##_RULE_IMPL(_31, rule, 31)macro##_RULE_IMPL(_32, rule, 32)macro##_RULE_IMPL(_33, rule, 33)macro##_RULE_IMPL(_34, rule, 34)macro##_RULE_IMPL(_35, rule, 35)
#define RULE_EXPAND_36(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) macro##_RULE_IMPL(_1, rule, 1)macro##_RULE_IMPL(_2, rule, 2)macro##_RULE_IMPL(_3, rule, 3)macro##_RULE_IMPL(_4, rule, 4)macro##_RULE_IMPL(_5, rule, 5)macro##_RULE_IMPL(_6, rule, 6)macro##_RULE_IMPL(_7, rule, 7)macro##_RULE_IMPL(_8, rule, 8)macro##_RULE_IMPL(_9, rule, 9)macro##_RULE_IMPL(_10, rule, 10)macro##_RULE_IMPL(_11, rule, 11)macro##_RULE_IMPL(_12, rule, 12)macro##_RULE_IMPL(_13, rule, 13)macro##_RULE_IMPL(_14, rule, 14)macro##_RULE_IMPL(_15, rule, 15)macro##_RULE_IMPL(_16, rule, 16)macro##_RULE_IMPL(_17, rule, 17)macro##_RULE_IMPL(_18, rule, 18)macro##_RULE_IMPL(_19, rule, 19)macro##_RULE_IMPL(_20, rule, 20)macro##_RULE_IMPL(_21, rule, 21)macro##_RULE_IMPL(_22, rule, 22)macro##_RULE_IMPL(_23, rule, 23)macro##_RULE_IMPL(_24, rule, 24)macro##_RULE_IMPL(_25, rule, 25)macro##_RULE_IMPL(_26, rule, 26)macro##_RULE_IMPL(_27, rule, 27)macro##_RULE_IMPL(_28, rule, 28)macro##_RULE_IMPL(_29, rule, 29)macro##_RULE_IMPL(_30, rule, 30)macro##_RULE_IMPL(_31, rule, 31)macro##_RULE_IMPL(_32, rule, 32)macro##_RULE_IMPL(_33, rule, 33)macro##_RULE_IMPL(_34, rule, 34)macro##_RULE_IMPL(_35, rule, 35)macro##_RULE_IMPL(_36, rule, 36)
#define RULE_EXPAND_37(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) macro##_RULE_IMPL(_1, rule, 1)macro##_RULE_IMPL(_2, rule, 2)macro##_RULE_IMPL(_3, rule, 3)macro##_RULE_IMPL(_4, rule, 4)macro##_RULE_IMPL(_5, rule, 5)macro##_RULE_IMPL(_6, rule, 6)macro##_RULE_IMPL(_7, rule, 7)macro##_RULE_IMPL(_8, rule, 8)macro##_RULE_IMPL(_9, rule, 9)macro##_RULE_IMPL(_10, rule, 10)macro##_RULE_IMPL(_11, rule, 11)macro##_RULE_IMPL(_12, rule, 12)macro##_RULE_IMPL(_13, rule, 13)macro##_RULE_IMPL(_14, rule, 14)macro##_RULE_IMPL(_15, rule, 15)macro##_RULE_IMPL(_16, rule, 16)macro##_RULE_IMPL(_17, rule, 17)macro##_RULE_IMPL(_18, rule, 18)macro##_RULE_IMPL(_19, rule, 19)macro##_RULE_IMPL(_20, rule, 20)macro##_RULE_IMPL(_21, rule, 21)macro##_RULE_IMPL(_22, rule, 22)macro##_RULE_IMPL(_23, rule, 23)macro##_RULE_IMPL(_24, rule, 24)macro##_RULE_IMPL(_25, rule, 25)macro##_RULE_IMPL(_26, rule, 26)macro##_RULE_IMPL(_27, rule, 27)macro##_RULE_IMPL(_28, rule, 28)macro##_RULE_IMPL(_29, rule, 29)macro##_RULE_IMPL(_30, rule, 30)macro##_RULE_IMPL(_31, rule, 31)macro##_RULE_IMPL(_32, rule, 32)macro##_RULE_IMPL(_33, rule, 33)macro##_RULE_IMPL(_34, rule, 34)macro##_RULE_IMPL(_35, rule, 35)macro##_RULE_IMPL(_36, rule, 36)macro##_RULE_IMPL(_37, rule, 37)
#define RULE_EXPAND_38(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) macro##_RULE_IMPL(_1, rule, 1)macro##_RULE_IMPL(_2, rule, 2)macro##_RULE_IMPL(_3, rule, 3)macro##_RULE_IMPL(_4, rule, 4)macro##_RULE_IMPL(_5, rule, 5)macro##_RULE_IMPL(_6, rule, 6)macro##_RULE_IMPL(_7, rule, 7)macro##_RULE_IMPL(_8, rule, 8)macro##_RULE_IMPL(_9, rule, 9)macro##_RULE_IMPL(_10, rule, 10)macro##_RULE_IMPL(_11, rule, 11)macro##_RULE_IMPL(_12, rule, 12)macro##_RULE_IMPL(_13, rule, 13)macro##_RULE_IMPL(_14, rule, 14)macro##_RULE_IMPL(_15, rule, 15)macro##_RULE_IMPL(_16, rule, 16)macro##_RULE_IMPL(_17, rule, 17)macro##_RULE_IMPL(_18, rule, 18)macro##_RULE_IMPL(_19, rule, 19)macro##_RULE_IMPL(_20, rule, 20)macro##_RULE_IMPL(_21, rule, 21)macro##_RULE_IMPL(_22, rule, 22)macro##_RULE_IMPL(_23, rule, 23)macro##_RULE_IMPL(_24, rule, 24)macro##_RULE_IMPL(_25, rule, 25)macro##_RULE_IMPL(_26, rule, 26)macro##_RULE_IMPL(_27, rule, 27)macro##_RULE_IMPL(_28, rule, 28)macro##_RULE_IMPL(_29, rule, 29)macro##_RULE_IMPL(_30, rule, 30)macro##_RULE_IMPL(_31, rule, 31)macro##_RULE_IMPL(_32, rule, 32)macro##_RULE_IMPL(_33, rule, 33)macro##_RULE_IMPL(_34, rule, 34)macro##_RULE_IMPL(_35, rule, 35)macro##_RULE_IMPL(_36, rule, 36)macro##_RULE_IMPL(_37, rule, 37)macro##_RULE_IMPL(_38, rule, 38)
#define RULE_EXPAND_39(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39) macro##_RULE_IMPL(_1, rule, 1)macro##_RULE_IMPL(_2, rule, 2)macro##_RULE_IMPL(_3, rule, 3)macro##_RULE_IMPL(_4, rule, 4)macro##_RULE_IMPL(_5, rule, 5)macro##_RULE_IMPL(_6, rule, 6)macro##_RULE_IMPL(_7, rule, 7)macro##_RULE_IMPL(_8, rule, 8)macro##_RULE_IMPL(_9, rule, 9)macro##_RULE_IMPL(_10, rule, 10)macro##_RULE_IMPL(_11, rule, 11)macro##_RULE_IMPL(_12, rule, 12)macro##_RULE_IMPL(_13, rule, 13)macro##_RULE_IMPL(_14, rule, 14)macro##_RULE_IMPL(_15, rule, 15)macro##_RULE_IMPL(_16, rule, 16)macro##_RULE_IMPL(_17, rule, 17)macro##_RULE_IMPL(_18, rule, 18)macro##_RULE_IMPL(_19, rule, 19)macro##_RULE_IMPL(_20, rule, 20)macro##_RULE_IMPL(_21, rule, 21)macro##_RULE_IMPL(_22, rule, 22)macro##_RULE_IMPL(_23, rule, 23)macro##_RULE_IMPL(_24, rule, 24)macro##_RULE_IMPL(_25, rule, 25)macro##_RULE_IMPL(_26, rule, 26)macro##_RULE_IMPL(_27, rule, 27)macro##_RULE_IMPL(_28, rule, 28)macro##_RULE_IMPL(_29, rule, 29)macro##_RULE_IMPL(_30, rule, 30)macro##_RULE_IMPL(_31, rule, 31)macro##_RULE_IMPL(_32, rule, 32)macro##_RULE_IMPL(_33, rule, 33)macro##_RULE_IMPL(_34, rule, 34)macro##_RULE_IMPL(_35, rule, 35)macro##_RULE_IMPL(_36, rule, 36)macro##_RULE_IMPL(_37, rule, 37)macro##_RULE_IMPL(_38, rule, 38)macro##_RULE_IMPL(_39, rule, 39)
#define RULE_EXPAND_40(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40) macro##_RULE_IMPL(_1, rule, 1)macro##_RULE_IMPL(_2, rule, 2)macro##_RULE_IMPL(_3, rule, 3)macro##_RULE_IMPL(_4, rule, 4)macro##_RULE_IMPL(_5, rule, 5)macro##_RULE_IMPL(_6, rule, 6)macro##_RULE_IMPL(_7, rule, 7)macro##_RULE_IMPL(_8, rule, 8)macro##_RULE_IMPL(_9, rule, 9)macro##_RULE_IMPL(_10, rule, 10)macro##_RULE_IMPL(_11, rule, 11)macro##_RULE_IMPL(_12, rule, 12)macro##_RULE_IMPL(_13, rule, 13)macro##_RULE_IMPL(_14, rule, 14)macro##_RULE_IMPL(_15, rule, 15)macro##_RULE_IMPL(_16, rule, 16)macro##_RULE_IMPL(_17, rule, 17)macro##_RULE_IMPL(_18, rule, 18)macro##_RULE_IMPL(_19, rule, 19)macro##_RULE_IMPL(_20, rule, 20)macro##_RULE_IMPL(_21, rule, 21)macro##_RULE_IMPL(_22, rule, 22)macro##_RULE_IMPL(_23, rule, 23)macro##_RULE_IMPL(_24, rule, 24)macro##_RULE_IMPL(_25, rule, 25)macro##_RULE_IMPL(_26, rule, 26)macro##_RULE_IMPL(_27, rule, 27)macro##_RULE_IMPL(_28, rule, 28)macro##_RULE_IMPL(_29, rule, 29)macro##_RULE_IMPL(_30, rule, 30)macro##_RULE_IMPL(_31, rule, 31)macro##_RULE_IMPL(_32, rule, 32)macro##_RULE_IMPL(_33, rule, 33)macro##_RULE_IMPL(_34, rule, 34)macro##_RULE_IMPL(_35, rule, 35)macro##_RULE_IMPL(_36, rule, 36)macro##_RULE_IMPL(_37, rule, 37)macro##_RULE_IMPL(_38, rule, 38)macro##_RULE_IMPL(_39, rule, 39)macro##_RULE_IMPL(_40, rule, 40)
#define RULE_EXPAND_41(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41) macro##_RULE_IMPL(_1, rule, 1)macro##_RULE_IMPL(_2, rule, 2)macro##_RULE_IMPL(_3, rule, 3)macro##_RULE_IMPL(_4, rule, 4)macro##_RULE_IMPL(_5, rule, 5)macro##_RULE_IMPL(_6, rule, 6)macro##_RULE_IMPL(_7, rule, 7)macro##_RULE_IMPL(_8, rule, 8)macro##_RULE_IMPL(_9, rule, 9)macro##_RULE_IMPL(_10, rule, 10)macro##_RULE_IMPL(_11, rule, 11)macro##_RULE_IMPL(_12, rule, 12)macro##_RULE_IMPL(_13, rule, 13)macro##_RULE_IMPL(_14, rule, 14)macro##_RULE_IMPL(_15, rule, 15)macro##_RULE_IMPL(_16, rule, 16)macro##_RULE_IMPL(_17, rule, 17)macro##_RULE_IMPL(_18, rule, 18)macro##_RULE_IMPL(_19, rule, 19)macro##_RULE_IMPL(_20, rule, 20)macro##_RULE_IMPL(_21, rule, 21)macro##_RULE_IMPL(_22, rule, 22)macro##_RULE_IMPL(_23, rule, 23)macro##_RULE_IMPL(_24, rule, 24)macro##_RULE_IMPL(_25, rule, 25)macro##_RULE_IMPL(_26, rule, 26)macro##_RULE_IMPL(_27, rule, 27)macro##_RULE_IMPL(_28, rule, 28)macro##_RULE_IMPL(_29, rule, 29)macro##_RULE_IMPL(_30, rule, 30)macro##_RULE_IMPL(_31, rule, 31)macro##_RULE_IMPL(_32, rule, 32)macro##_RULE_IMPL(_33, rule, 33)macro##_RULE_IMPL(_34, rule, 34)macro##_RULE_IMPL(_35, rule, 35)macro##_RULE_IMPL(_36, rule, 36)macro##_RULE_IMPL(_37, rule, 37)macro##_RULE_IMPL(_38, rule, 38)macro##_RULE_IMPL(_39, rule, 39)macro##_RULE_IMPL(_40, rule, 40)macro##_RULE_IMPL(_41, rule, 41)
#define RULE_EXPAND_42(rule, macro, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42) macro##_RULE_IMPL(_1, rule, 1)macro##_RULE_IMPL(_2, rule, 2)macro##_RULE_IMPL(_3, rule, 3)macro##_RULE_IMPL(_4, rule, 4)macro##_RULE_IMPL(_5, rule, 5)macro##_RULE_IMPL(_6, rule, 6)macro##_RULE_IMPL(_7, rule, 7)macro##_RULE_IMPL(_8, rule, 8)macro##_RULE_IMPL(_9, rule, 9)macro##_RULE_IMPL(_10, rule, 10)macro##_RULE_IMPL(_11, rule, 11)macro##_RULE_IMPL(_12, rule, 12)macro##_RULE_IMPL(_13, rule, 13)macro##_RULE_IMPL(_14, rule, 14)macro##_RULE_IMPL(_15, rule, 15)macro##_RULE_IMPL(_16, rule, 16)macro##_RULE_IMPL(_17, rule, 17)macro##_RULE_IMPL(_18, rule, 18)macro##_RULE_IMPL(_19, rule, 19)macro##_RULE_IMPL(_20, rule, 20)macro##_RULE_IMPL(_21, rule, 21)macro##_RULE_IMPL(_22, rule, 22)macro##_RULE_IMPL(_23, rule, 23)macro##_RULE_IMPL(_24, rule, 24)macro##_RULE_IMPL(_25, rule, 25)macro##_RULE_IMPL(_26, rule, 26)macro##_RULE_IMPL(_27, rule, 27)macro##_RULE_IMPL(_28, rule, 28)macro##_RULE_IMPL(_29, rule, 29)macro##_RULE_IMPL(_30, rule, 30)macro##_RULE_IMPL(_31, rule, 31)macro##_RULE_IMPL(_32, rule, 32)macro##_RULE_IMPL(_33, rule, 33)macro##_RULE_IMPL(_34, rule, 34)macro##_RULE_IMPL(_35, rule, 35)macro##_RULE_IMPL(_36, rule, 36)macro##_RULE_IMPL(_37, rule, 37)macro##_RULE_IMPL(_38, rule, 38)macro##_RULE_IMPL(_39, rule, 39)macro##_RULE_IMPL(_40, rule, 40)macro##_RULE_IMPL(_41, rule, 41)macro##_RULE_IMPL(_42, rule, 42)

// #   define DECLARE_FOR_EACH(...) EXPAND_DECLARE_N(GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
// #   define EXPAND_DECLARE_N(count, ...) EXPAND_DECLARE_N_IMPL(count, __VA_ARGS__)
// #   define EXPAND_DECLARE_N_IMPL(count, ...) DECLARE_EXPAND_##count(__VA_ARGS__)

#define DECLARE_EXPAND(...) DECLARE_EXPAND4(DECLARE_EXPAND4(DECLARE_EXPAND4(DECLARE_EXPAND4(__VA_ARGS__))))
#define DECLARE_EXPAND4(...) DECLARE_EXPAND3(DECLARE_EXPAND3(DECLARE_EXPAND3(DECLARE_EXPAND3(__VA_ARGS__))))
#define DECLARE_EXPAND3(...) DECLARE_EXPAND2(DECLARE_EXPAND2(DECLARE_EXPAND2(DECLARE_EXPAND2(__VA_ARGS__))))
#define DECLARE_EXPAND2(...) DECLARE_EXPAND1(DECLARE_EXPAND1(DECLARE_EXPAND1(DECLARE_EXPAND1(__VA_ARGS__))))
#define DECLARE_EXPAND1(...) __VA_ARGS__

#define DECLARE_FOR_EACH(...)                                    \
  __VA_OPT__(DECLARE_EXPAND(DECLARE_FOR_EACH_HELPER(__VA_ARGS__)))
#define DECLARE_FOR_EACH_HELPER(a1, ...)                         \
  DECLARE_##a1                                                     \
  __VA_OPT__(DECLARE_FOR_EACH_AGAIN PARENS (__VA_ARGS__))
#define DECLARE_FOR_EACH_AGAIN() DECLARE_FOR_EACH_HELPER

// #   define DEFINE_FOR_EACH(...) EXPAND_DEFINE_N(GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
// #   define EXPAND_DEFINE_N(count, ...) EXPAND_DEFINE_N_IMPL(count, __VA_ARGS__)
// #   define EXPAND_DEFINE_N_IMPL(count, ...) DEFINE_EXPAND_##count(__VA_ARGS__)

#define DEFINE_EXPAND(...) DEFINE_EXPAND4(DEFINE_EXPAND4(DEFINE_EXPAND4(DEFINE_EXPAND4(__VA_ARGS__))))
#define DEFINE_EXPAND4(...) DEFINE_EXPAND3(DEFINE_EXPAND3(DEFINE_EXPAND3(DEFINE_EXPAND3(__VA_ARGS__))))
#define DEFINE_EXPAND3(...) DEFINE_EXPAND2(DEFINE_EXPAND2(DEFINE_EXPAND2(DEFINE_EXPAND2(__VA_ARGS__))))
#define DEFINE_EXPAND2(...) DEFINE_EXPAND1(DEFINE_EXPAND1(DEFINE_EXPAND1(DEFINE_EXPAND1(__VA_ARGS__))))
#define DEFINE_EXPAND1(...) __VA_ARGS__

#define DEFINE_FOR_EACH(...)                                    \
  __VA_OPT__(DEFINE_EXPAND(DEFINE_FOR_EACH_HELPER(__VA_ARGS__)))
#define DEFINE_FOR_EACH_HELPER(a1, ...)                         \
  DEFINE_##a1                                                     \
  __VA_OPT__(DEFINE_FOR_EACH_AGAIN PARENS (__VA_ARGS__))
#define DEFINE_FOR_EACH_AGAIN() DEFINE_FOR_EACH_HELPER

#   define RULE_FOR_EACH(rule, macro, ...) EXPAND_RULE_N(rule, macro, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#   define EXPAND_RULE_N(rule, macro, count, ...) EXPAND_RULE_N_IMPL(rule, macro, count, __VA_ARGS__)
#   define EXPAND_RULE_N_IMPL(rule, macro, count, ...) RULE_EXPAND_##count(rule, macro, __VA_ARGS__)

// #   define MACRO_FOR_EACH(macro, ...) EXPAND_MACRO_N(macro, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
// #   define EXPAND_MACRO_N(macro, count, ...) EXPAND_MACRO_N_IMPL(macro, count, __VA_ARGS__)
// #   define EXPAND_MACRO_N_IMPL(macro, count, ...) MACRO_EXPAND_##count(macro, __VA_ARGS__)

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

// #   define RUN_MACRO_FOR_EACH(macro, ...) EXPAND_RUN_MACRO_N(macro, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
// #   define EXPAND_RUN_MACRO_N(macro, count, ...) EXPAND_RUN_MACRO_N_IMPL(macro, count, __VA_ARGS__)
// #   define EXPAND_RUN_MACRO_N_IMPL(macro, count, ...) MACRO_RUN_EXPAND_##count(macro, __VA_ARGS__)

#define RUN_MACRO_EXPAND(...) RUN_MACRO_EXPAND4(RUN_MACRO_EXPAND4(RUN_MACRO_EXPAND4(RUN_MACRO_EXPAND4(__VA_ARGS__))))
#define RUN_MACRO_EXPAND4(...) RUN_MACRO_EXPAND3(RUN_MACRO_EXPAND3(RUN_MACRO_EXPAND3(RUN_MACRO_EXPAND3(__VA_ARGS__))))
#define RUN_MACRO_EXPAND3(...) RUN_MACRO_EXPAND2(RUN_MACRO_EXPAND2(RUN_MACRO_EXPAND2(RUN_MACRO_EXPAND2(__VA_ARGS__))))
#define RUN_MACRO_EXPAND2(...) RUN_MACRO_EXPAND1(RUN_MACRO_EXPAND1(RUN_MACRO_EXPAND1(RUN_MACRO_EXPAND1(__VA_ARGS__))))
#define RUN_MACRO_EXPAND1(...) __VA_ARGS__

#define RUN_MACRO_FOR_EACH(macro, ...)                                    \
  __VA_OPT__(RUN_MACRO_EXPAND(RUN_MACRO_FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define RUN_MACRO_FOR_EACH_HELPER(macro, a1, ...)                         \
  RUN_##macro(a1)                                                     \
  __VA_OPT__(RUN_MACRO_FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define RUN_MACRO_FOR_EACH_AGAIN() RUN_MACRO_FOR_EACH_HELPER


#   define ENUM_RULE_IMPL(type_, rule, n) rule##_##type_##_##n,
#   define UNION_RULE_IMPL(type_, rule, n) struct type_ * var_##n;
#   define RULE_CONTAINER_INTERNAL_RULE_IMPL(type_, rule, n) \
    batch->token_on = current_token; \
    struct type_* var_##n = Create_##type_(batch); \
    if (var_##n && !var_0) \
    { \
        var_0 = malloc(sizeof(*var_0)); \
        var_0->type = rule##_##type_##_##n; \
        var_0->value.var_##n = var_##n; \
        end_token = batch->token_on; \
    }
#   define RULE_CONTAINER_INTERNAL_NEXT_RULE_IMPL(type_, rule, n) \
    batch->token_on = current_token; \
    struct type_* var_##n = Create_##type_(batch); \
    if (var_##n && !var_0) \
    { \
        var_0 = malloc(sizeof(*var_0)); \
        var_0->type = rule##_##type_##_##n; \
        var_0->value.var_##n = var_##n; \
        var_0->next = Create_##rule(batch); \
        end_token = batch->token_on; \
    }

#   define TERMINAL_CHECK_RULE_IMPL(type_, rule, n) struct type_* var_##n = Create_##type_(batch); if (!var_##n) {batch->token_on = current_token; return NULL;}
#   define TERMINAL_SET_RULE_IMPL(type_, rule, n) var_0->var_##n = var_##n;

#   define rule_container(type_) ,RULE_CONTAINER_RULE_IMPL(type_)
#   define rule_container_next(type_) ,RULE_CONTAINER_RULE_NEXT_IMPL(type_)
#   define terminal(type_) ,TERMINAL_RULE_IMPL(type_)

#   define CHECK_RECURSE_NEXT_RULE_IMPL(type_, rule, n) \
    case rule##_##type_##_##n: \
    semantic_##type_(var->value.var_##n); \
    if (var->next) \
    { \
        semantic_##rule(var->next); \
    } \
    break;
#   define CHECK_RECURSE_RULE_IMPL(type_, rule, n) \
    case rule##_##type_##_##n: \
        semantic_##type_(var->value.var_##n); \
    break;

#   define CHECK_RECURSE_NEXT_CODE_GEN_RULE_IMPL(type_, rule, n) \
    case rule##_##type_##_##n: \
    gen_code_##type_(file, var->value.var_##n); \
    if (var->next) \
    { \
        gen_code_##rule(file, var->next); \
    } \
    break;
#   define CHECK_RECURSE_CODE_GEN_RULE_IMPL(type_, rule, n) \
    case rule##_##type_##_##n: \
        gen_code_##type_(file, var->value.var_##n); \
    break;

#   define PRINT_NEXT_RULE_IMPL(type_, rule, n) \
    case rule##_##type_##_##n: \
    printf("%s type: %s\n", __STRING(rule), __STRING(type_)); \
    print_##type_(layer+1, var->value.var_##n); \
    if (var->next) \
    { \
        print_##rule(layer+1, var->next); \
    } \
    break;
#   define PRINT_VALUE_RULE_IMPL(type_, rule, n) \
    case rule##_##type_##_##n: \
        printf("%s type: %s\n", __STRING(rule), __STRING(type_)); \
        print_##type_(layer+1, var->value.var_##n); \
    break;
#   define PRINT_TERMINAL_RULE_IMPL(type_, rule, n) \
    print_##type_(layer+1, var->var_##n);

#   define SCOPE_DECLARE_RULE_CONTAINER_RULE_NEXT_IMPL(type_, semantics_, code_generation_, rules) // nothing
#   define SCOPE_DEFINE_RULE_CONTAINER_RULE_NEXT_IMPL(type_, semantics_, code_generation_, rules) // nothing
#   define SCOPE_DECLARE_RULE_CONTAINER_RULE_IMPL(type_, semantics_, code_generation_, rules) // nothing
#   define SCOPE_DEFINE_RULE_CONTAINER_RULE_IMPL(type_, semantics_, code_generation_, rules) // nothing
#   define SCOPE_DECLARE_TERMINAL_RULE_IMPL(type_, semantics_, code_generation_, rules) // nothing
#   define SCOPE_DEFINE_TERMINAL_RULE_IMPL(type_, semantics_, code_generation_, rules) // nothing

#   define DECLARE_RULE_CONTAINER_RULE_IMPL(type_, semantics_, code_generation_, rules) \
    typedef struct type_ \
    { \
        int scope; \
        DECLARE_##semantics_ \
        DECLARE_##code_generation_ \
        enum \
        { \
            RULE_FOR_EACH(type_, ENUM, EXPAND_##rules) \
        } type; \
        union \
        { \
            RULE_FOR_EACH(type_, UNION, EXPAND_##rules) \
        } value; \
    } type_; \
    struct type_* Create_##type_(struct TokenBatch* batch); \
    void print_##type_(int layer, struct type_* p); \
    void semantic_##type_(struct type_* var); \
    void recurse_##type_(struct type_* var); \
    void gen_code_##type_(FILE* file, struct type_* var); \
    void recurse_code_gen_##type_(FILE* file, struct type_* var);



#   define DECLARE_RULE_CONTAINER_RULE_NEXT_IMPL(type_, semantics_, code_generation_, rules) \
    typedef struct type_ \
    { \
        int scope; \
        DECLARE_##semantics_ \
        DECLARE_##code_generation_ \
        enum \
        { \
            RULE_FOR_EACH(type_, ENUM, EXPAND_##rules) \
        } type; \
        union \
        { \
            RULE_FOR_EACH(type_, UNION, EXPAND_##rules) \
        } value; \
        struct type_* next; \
    } type_; \
    struct type_* Create_##type_(struct TokenBatch* batch); \
    void print_##type_(int layer, struct type_* p); \
    void semantic_##type_(struct type_* var); \
    void recurse_##type_(struct type_* var); \
    void gen_code_##type_(FILE* file, struct type_* var); \
    void recurse_code_gen_##type_(FILE* file, struct type_* var);
#   define DECLARE_TERMINAL_RULE_IMPL(type_, semantics_, code_generation_, rules) \
    typedef struct type_ \
    { \
        int scope; \
        DECLARE_##semantics_ \
        DECLARE_##code_generation_ \
        RULE_FOR_EACH(type_, UNION, EXPAND_##rules) \
    } type_; \
    struct type_* Create_##type_(struct TokenBatch* batch); \
    void print_##type_(int layer, struct type_* p); \
    void semantic_##type_(struct type_* var); \
    void recurse_##type_(struct type_* var); \
    void gen_code_##type_(FILE* file, struct type_* var); \
    void recurse_code_gen_##type_(FILE* file, struct type_* var);
#   define DEFINE_RULE_CONTAINER_RULE_IMPL(type_, semantics_, code_generation_, rules) \
    struct type_* Create_##type_(struct TokenBatch* batch) \
    { \
        int current_token = batch->token_on; \
        int end_token = 0; \
        struct type_* var_0 = NULL; \
        RULE_FOR_EACH(type_, RULE_CONTAINER_INTERNAL, EXPAND_##rules) \
        batch->token_on = end_token; \
        if (var_0) { P_DEFINE_##semantics_ } \
        if (var_0) { INIT_##code_generation_ } \
        return var_0; \
    } \
    void print_##type_(int layer, struct type_* var) \
    { \
        print_white(layer); \
        switch (var->type) { \
        RULE_FOR_EACH(type_, PRINT_VALUE, EXPAND_##rules) \
        } \
    } \
    void semantic_##type_(struct type_* var_0) \
    { \
        void (*recurse_all)(struct type_*) = recurse_##type_; \
        S_DEFINE_##semantics_ \
    } \
    void recurse_##type_(struct type_* var) \
    { \
        switch (var->type) { \
        RULE_FOR_EACH(type_, CHECK_RECURSE, EXPAND_##rules) \
        } \
    } \
    void gen_code_##type_(FILE* file, struct type_* var_0) \
    { \
        void (*recurse_all)(FILE*, struct type_*) = recurse_code_gen_##type_; \
        DEFINE_##code_generation_ \
    } \
    void recurse_code_gen_##type_(FILE* file, struct type_* var) \
    { \
        switch (var->type) { \
        RULE_FOR_EACH(type_, CHECK_RECURSE_CODE_GEN, EXPAND_##rules) \
        } \
    }
#   define DEFINE_RULE_CONTAINER_RULE_NEXT_IMPL(type_, semantics_, code_generation_, rules) \
    struct type_* Create_##type_(struct TokenBatch* batch) \
    { \
        int current_token = batch->token_on; \
        int end_token = 0; \
        struct type_* var_0 = NULL; \
        RULE_FOR_EACH(type_, RULE_CONTAINER_INTERNAL_NEXT, EXPAND_##rules) \
        batch->token_on = end_token; \
        if (var_0) { P_DEFINE_##semantics_ } \
        if (var_0) { INIT_##code_generation_ } \
        return var_0; \
    } \
    void print_##type_(int layer, struct type_* var) \
    { \
        print_white(layer); \
        switch (var->type) { \
        RULE_FOR_EACH(type_, PRINT_NEXT, EXPAND_##rules) \
        } \
    } \
    void semantic_##type_(struct type_* var_0) \
    { \
        void (*recurse_all)(struct type_*) = recurse_##type_; \
        S_DEFINE_##semantics_ \
    } \
    void recurse_##type_(struct type_* var) \
    { \
        switch (var->type) { \
        RULE_FOR_EACH(type_, CHECK_RECURSE_NEXT, EXPAND_##rules) \
        } \
    } \
    void gen_code_##type_(FILE* file, struct type_* var_0) \
    { \
        void (*recurse_all)(FILE*, struct type_*) = recurse_code_gen_##type_; \
        DEFINE_##code_generation_ \
    } \
    void recurse_code_gen_##type_(FILE* file, struct type_* var) \
    { \
        switch (var->type) { \
        RULE_FOR_EACH(type_, CHECK_RECURSE_NEXT_CODE_GEN, EXPAND_##rules) \
        } \
    }
#   define DEFINE_TERMINAL_RULE_IMPL(type_, semantics_, code_generation_, rules) \
    struct type_* Create_##type_(struct TokenBatch* batch) \
    { \
        int current_token = batch->token_on; \
        RULE_FOR_EACH(type_, TERMINAL_CHECK, EXPAND_##rules) \
        { \
            struct type_* var_0 = malloc(sizeof(struct type_)); \
            RULE_FOR_EACH(type_, TERMINAL_SET, EXPAND_##rules) \
            if (var_0) { P_DEFINE_##semantics_ } \
            if (var_0) { INIT_##code_generation_ } \
            return var_0; \
        } \
        batch->token_on = current_token; \
        return NULL; \
    } \
    void print_##type_(int layer, struct type_* var) \
    { \
        RULE_FOR_EACH(type_, PRINT_TERMINAL, EXPAND_##rules) \
    } \
    void semantic_##type_(struct type_* var_0) \
    { \
        void (*recurse_all)(struct type_*) = recurse_##type_; \
        RULE_FOR_EACH(type_, DEFINE_RECURSE_FUNCTION, EXPAND_##rules) \
        S_DEFINE_##semantics_ \
    } \
    void recurse_##type_(struct type_* var) \
    { \
        RULE_FOR_EACH(type_, RECURSE, EXPAND_##rules) \
    } \
    void gen_code_##type_(FILE* file, struct type_* var_0) \
    { \
        void (*recurse_all)(FILE*, struct type_*) = recurse_code_gen_##type_; \
        RULE_FOR_EACH(type_, DEFINE_RECURSE_FUNCTION_CODE_GEN, EXPAND_##rules) \
        DEFINE_##code_generation_ \
    } \
    void recurse_code_gen_##type_(FILE* file, struct type_* var) \
    { \
        RULE_FOR_EACH(type_, RECURSE_CODE_GEN, EXPAND_##rules) \
    }


#   define create_compiler(contents) create_compiler_IMPL(contents)
#   define create_compiler_IMPL(name_, ...) \
struct TokenBatch; \
DECLARE_FOR_EACH(__VA_ARGS__) \
typedef struct Token \
{ \
    TokenType type; \
    char* value; \
    int line; \
    int column; \
    char* lineStr; \
} Token; \
typedef struct TokenBatch \
{ \
    Token* tokens; \
    int token_on; \
    int token_count; \
    int token_capacity; \
} TokenBatch; \
TokenBatch* create_token_batch() \
{ \
    TokenBatch* batch = malloc(sizeof(TokenBatch)); \
    batch->token_count = 0; \
    batch->token_capacity = 256; \
    batch->token_on = 0; \
    batch->tokens = (Token*)malloc(sizeof(Token) * batch->token_capacity); \
    return batch; \
} \
void add_token(TokenBatch* batch, Token token) \
{ \
    if (batch->token_count == batch->token_capacity) \
    { \
        batch->token_capacity += 256; \
        batch->tokens = (Token*)realloc(batch->tokens, sizeof(Token) * batch->token_capacity); \
    } \
    batch->tokens[batch->token_count] = token; \
    batch->token_count++; \
} \
TokenBatch* tokenize(const char* code) \
{ \
    size_t codeLength = strlen(code); \
    size_t offset = 0; \
    TokenBatch* tokens = create_token_batch(); \
    int line = 1; \
    int column = 1; \
    while (offset < codeLength) \
    { \
        int matched = 0; \
        for (int i = 0; i < token_count; i++) \
        { \
            regex_t regex; \
            regmatch_t match[1]; \
            if (regcomp(&regex, token_patterns[i], REG_EXTENDED) == 0) \
            { \
                if (regexec(&regex, code + offset, 1, match, 0) == 0) \
                { \
                    if (ignore_token(i)) \
                    { \
                        offset += match[0].rm_eo; \
                        matched = 1; \
                        regfree(&regex); \
                        break; \
                    } \
                    Token token; \
                    token.type = (TokenType)i; \
                    token.column = column; \
                    token.line = line; \
                    token.value = strndup(code + offset, match[0].rm_eo); \
                    add_token(tokens, token); \
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
void cleanup_batch(struct TokenBatch* batch) \
{ \
    free(batch->tokens); \
} \
int check_token(TokenType type, struct TokenBatch* batch) \
{ \
    if (batch->tokens[batch->token_on].type == type) \
    { \
        batch->token_on++; \
        return 1; \
    } \
    return 0; \
} \
struct Allocation_Table* Create_Allocation_Table(const char* name, const char** string_ids, int n); \
typedef struct Scope \
{ \
    struct Scope* parent_scope; \
    MACRO_FOR_EACH(SCOPE_DECLARE_, __VA_ARGS__) \
} Scope;  \
struct Scope* Create_Scope(struct Scope* parent) \
{ \
    struct Scope* new_scope = (struct Scope*)malloc(sizeof(struct Scope)); \
    new_scope->parent_scope = parent; \
    MACRO_FOR_EACH(SCOPE_DEFINE_, __VA_ARGS__) \
    return new_scope; \
} \
struct Scope* scope = NULL; \
void Scope_Enter() \
{ \
printf("Enter Scope\n"); \
    if (!scope) scope = Create_Scope(NULL); \
    scope = Create_Scope(scope); \
} \
void Scope_Exit() \
{ \
printf("Exit Scope\n"); \
    if (!scope) scope = Create_Scope(NULL); \
    scope = scope->parent_scope; \
} \
typedef struct Allocation_Table \
{ \
    const char** string_ids; \
    int* in_use; \
    int num; \
    const char* name; \
} Allocation_Table; \
struct Allocation_Table* Create_Allocation_Table(const char* name, const char** string_ids, int n) \
{ \
    struct Allocation_Table* table = malloc(sizeof(struct Allocation_Table)); \
    table->string_ids = malloc(sizeof(char*) * n); \
    table->in_use = malloc(sizeof(int) * n); \
    for (int i = 0; i < n; i++) \
    { \
        table->string_ids[i] = string_ids[i]; \
        table->in_use[i] = 0; \
    } \
    table->num = n; \
    table->name = name; \
    return table; \
} \
int Get_Allocation(struct Allocation_Table* table) \
{ \
    for (int i = 0; i < table->num; i++) \
    { \
        if (table->in_use[i] == 0) \
        { \
            table->in_use[i] = 1; \
            return i; \
        } \
    } \
    printf("Error: All %ss are allocated. Unable to Assign a new %s.\n", table->name ,table->name); \
    exit(EXIT_FAILURE); \
    return 0; \
} \
void Free_Allocation(struct Allocation_Table* table, int id) \
{ \
    table->in_use[id] = 0; \
} \
const char* Get_String_Allocation_ID(struct Allocation_Table* table, int id) \
{ \
    return table->string_ids[id]; \
} \
DEFINE_FOR_EACH(__VA_ARGS__)

#define DEFINE_RECURSE_FUNCTION_RULE_IMPL(type_, rule, n) struct type_* var_##n = var_0->var_##n; void (*recurse_##n)(struct type_*) = semantic_##type_;
#define RECURSE_RULE_IMPL(type_, rule, n) semantic_##type_(var->var_##n);
#define DEFINE_RECURSE_FUNCTION_CODE_GEN_RULE_IMPL(type_, rule, n) struct type_* var_##n = var_0->var_##n; void (*recurse_##n)(struct type_*) = semantic_##type_;
#define RECURSE_CODE_GEN_RULE_IMPL(type_, rule, n) gen_code_##type_(file, var->var_##n);

// Semantic Analysis

#define semantic_default() ,SEMANTIC_ANALYSIS_IMPL(0 semantics_continue())

#define semantic(value) ,SEMANTIC_ANALYSIS_IMPL(0 value)

#define SEMANTIC_FIND_METHOD(name, node_, type_, func) ,SEMANTIC_FIND_METHOD_IMPL(name, node_, type_, func)
#define scope_table(name) ,SEMANTIC_SCOPE_TABLE_IMPL(name) // creates a semantic search
#define scope_variable(type_, name, value) ,SEMANTIC_SCOPE_VARIABLE_IMPL(type_, name, value)
#define set_scope_variable(name, value) ,SEMANTIC_SET_SCOPE_VARIABLE_IMPL(name, value)

#define set_var_if_p(n, var, value) ,P_SET_VAR_IF_IMPL(n, var, value)
#define set_var_if_s(n, var, value) ,S_SET_VAR_IF_IMPL(n, var, value)
#define rule_set_var(n, name, value) ,SEMANTIC_RULE_CONTAINER_SET_VARIABLE_IMPL(n-1, name, value) 
#define semantic_var(type, name, value) ,SEMANTIC_VARIABLE_IMPL(type, name, value) // Creates a semantic variable in the current node
#define semantic_set_var_p(n, name, value) ,P_SEMANTIC_SET_VARIABLE_IMPL(n, name, value)
#define semantic_set_var_s(n, name, value) ,S_SEMANTIC_SET_VARIABLE_IMPL(n, name, value)
#define search_add(name, node) ,SEMANTIC_ADD_IMPL(name, node) // adds the node to the semantic search 
#define semantic_search(name, value, representation) ,SEMANTIC_FIND_IMPL(name, value, representation) // Finds an element in a semantic search
#define SEMANTIC_GLOBAL(type, name, init) ,SEMANTIC_GLOBAL_IMPL(type, name, init) // Creates a global semantic variable such as stack offset
#define SEMANTIC_SET_GLOBAL_P(name, value) ,P_SEMANTIC_SET_GLOBAL_IMPL(name, value) // Sets a global variable
#define SEMANTIC_SET_GLOBAL_S(name, value) ,S_SEMANTIC_SET_GLOBAL_IMPL(name, value) // Sets a global variable
#define SEMANTIC_TERMINAL_RECURSE(x) ,SEMANTIC_TERMINAL_RECURSE_IMPL(x) // recurses through other nodes
#define semantics_continue() ,SEMANTIC_RECURSE_ALL_IMPL() // recurses through other nodes
#define enter_scope() ,SEMANTIC_ENTER_SCOPE_IMPL()
#define exit_scope() ,SEMANTIC_EXIT_SCOPE_IMPL()

//#define CREATE_SEMANTIC_ANALYSIS_IMPL(...) // Defines all variables

#define SCOPE_DECLARE_SEMANTIC_GLOBAL_IMPL(type, name, value) // nothing
#define SCOPE_DEFINE_SEMANTIC_GLOBAL_IMPL(type, name, value) // nothing
#define DECLARE_SEMANTIC_GLOBAL_IMPL(type, name, value) type name = value;
#define DEFINE_SEMANTIC_GLOBAL_IMPL(type, name, value) // nothing

#define SCOPE_DECLARE_SEMANTIC_SCOPE_VARIABLE_IMPL(type_, name, value) type_ name;
#define SCOPE_DEFINE_SEMANTIC_SCOPE_VARIABLE_IMPL(type_, name, value) new_scope->name = value;
#define DECLARE_SEMANTIC_SCOPE_VARIABLE_IMPL(type_, name, value) // nothing
#define DEFINE_SEMANTIC_SCOPE_VARIABLE_IMPL(type_, name, value) // nothing

#define SCOPE_DECLARE_SEMANTIC_SCOPE_TABLE_IMPL(name) struct Scope_Table* name;
#define SCOPE_DEFINE_SEMANTIC_SCOPE_TABLE_IMPL(name) new_scope->name = Init_Scope_Table();
#define DECLARE_SEMANTIC_SCOPE_TABLE_IMPL(name) // nothing
#define DEFINE_SEMANTIC_SCOPE_TABLE_IMPL(name) \
void* Find_Scope_Table_##name(struct Scope* scope, void* v, int (*func)(void* n, void* v)) \
{ \
    struct Scope_Table* array = scope->name; \
    for (int i = 0; i < array->size; i++) \
    { \
        if (func(array->data[i], v)) \
        { \
            return array->data[i]; \
        } \
    } \
    if (!scope->parent_scope) \
    { \
        printf("Cannot find it\n"); \
        return NULL; \
    } \
    else \
    { \
        return Find_Scope_Table_##name(scope->parent_scope, v, func); \
    } \
}

// void print_line(int line_number) {
//     FILE *file = fopen(filename, "r"); // Open file in read mode
//     if (!file) {
//         perror("Could not open file");
//         return;
//     }

//     char buffer[1024]; // Buffer to store each line
//     int current_line = 1;

//     // Read lines until the end of the file or the desired line
//     while (fgets(buffer, sizeof(buffer), file)) {
//         if (current_line == line_number) {
//             printf("Line %d: %s", line_number, buffer);
//             fclose(file);
//             return;
//         }
//         current_line++;
//     }

//     // If the file has fewer lines than requested
//     fprintf(stderr, "Error: Line %d does not exist in the file.\n", line_number);
//     fclose(file);
// }

// void print_token_line(struct Token* token)
// {
//     printf("LINE\n");
//     for (int i = 0; i < token->column; i++)
//     {
//         printf(" ");
//     }
//     for (int i = 0; i < strlen(token->value); i++)
//     {
//         printf("~");
//     }
//     printf("\n");
//     exit(1);
// }
#define semantic_assert(exp_, token_, message_) SEMANTIC_ASSERT_IMPL(exp_, token_, message_)
#define DECLARE_SEMANTIC_ASSERT_IMPL(exp_, token_, message_) 
#define P_DEFINE_SEMANTIC_ASSERT_IMPL(exp_, token_, message_) \
if (!(exp_)) \
{ \
    printf(message_); \
    print_token_line(token_); \
}
#define S_DEFINE_SEMANTIC_ASSERT_IMPL(exp_, token_, message_) \
if (!(exp_)) \
{ \
    print_token_line(token_); \
    printf(message_); \
}

#define DECLARE_SEMANTIC_SET_SCOPE_VARIABLE_IMPL(name, value) // nothing
#define P_DEFINE_SEMANTIC_SET_SCOPE_VARIABLE_IMPL(name, value) // nothing
#define S_DEFINE_SEMANTIC_SET_SCOPE_VARIABLE_IMPL(name, value) scope->name = value;

#define DECLARE_SEMANTIC_ANALYSIS_IMPL(placeholder, ...) MACRO_FOR_EACH(DECLARE_, __VA_ARGS__)
#define P_DEFINE_SEMANTIC_ANALYSIS_IMPL(placeholder, ...) MACRO_FOR_EACH(P_DEFINE_, __VA_ARGS__)
#define S_DEFINE_SEMANTIC_ANALYSIS_IMPL(placeholder, ...) MACRO_FOR_EACH(S_DEFINE_, __VA_ARGS__)

#define DECLARE_SEMANTIC_TERMINAL_RECURSE_IMPL(index) // nothing
#define P_DEFINE_SEMANTIC_TERMINAL_RECURSE_IMPL(index) // nothinm
#define S_DEFINE_SEMANTIC_TERMINAL_RECURSE_IMPL(index) recurse_##index(var_##index);

#define DECLARE_SEMANTIC_RECURSE_ALL_IMPL() // nothing
#define P_DEFINE_SEMANTIC_RECURSE_ALL_IMPL() // nothing
#define S_DEFINE_SEMANTIC_RECURSE_ALL_IMPL() recurse_all(var_0);

#define DECLARE_SEMANTIC_VARIABLE_IMPL(type, name, value) type name;
#define P_DEFINE_SEMANTIC_VARIABLE_IMPL(type, name, value) var_0->name = value;
#define S_DEFINE_SEMANTIC_VARIABLE_IMPL(type, name, value) // nothing

#define DECLARE_P_SET_VAR_IF_IMPL(n, var, value) // nothing
#define P_DEFINE_P_SET_VAR_IF_IMPL(n, var, value) if (var_0->type == n) var_0->var = value;
#define S_DEFINE_P_SET_VAR_IF_IMPL(n, var, value) // nothing

#define DECLARE_S_SET_VAR_IF_IMPL(n, var, value) // nothing
#define P_DEFINE_S_SET_VAR_IF_IMPL(n, var, value) // nothing
#define S_DEFINE_S_SET_VAR_IF_IMPL(n, var, value) if (var_0->type == n) var_0->var = value;
// remove
#define DECLARE_P_SEMANTIC_SET_VARIABLE_IMPL(n, name, value) // nothing
#define P_DEFINE_P_SEMANTIC_SET_VARIABLE_IMPL(n, name, value) var_##n->name = value;
#define S_DEFINE_P_SEMANTIC_SET_VARIABLE_IMPL(n, name, value) // nothing

#define DECLARE_S_SEMANTIC_SET_VARIABLE_IMPL(n, name, value) // nothing
#define P_DEFINE_S_SEMANTIC_SET_VARIABLE_IMPL(n, name, value) // nothing
#define S_DEFINE_S_SEMANTIC_SET_VARIABLE_IMPL(n, name, value) var_##n->name = value;

#define DECLARE_SEMANTIC_ADD_IMPL(name, node) // nothing
#define P_DEFINE_SEMANTIC_ADD_IMPL(name, node) // nothing
#define S_DEFINE_SEMANTIC_ADD_IMPL(name, node) if (!scope) scope = Create_Scope(NULL); Add_Scope_Table(scope->name, node);


#define DECLARE_SEMANTIC_FIND_IMPL(name, value, func) // nothing
#define P_DEFINE_SEMANTIC_FIND_IMPL(name, value, func) // nothing
#define S_DEFINE_SEMANTIC_FIND_IMPL(name, value, func) if (!Find_Scope_Table_##name(scope, (void*)value, Find_Method_##func)) {/*exit(EXIT_FAILURE);*/}

#define DECLARE_S_SEMANTIC_SET_GLOBAL_IMPL(name, value) // nothing
#define P_DEFINE_S_SEMANTIC_SET_GLOBAL_IMPL(name, value) // nothing
#define S_DEFINE_S_SEMANTIC_SET_GLOBAL_IMPL(name, value) name = value;

#define DECLARE_P_SEMANTIC_SET_GLOBAL_IMPL(name, value) // nothing
#define P_DEFINE_P_SEMANTIC_SET_GLOBAL_IMPL(name, value) name = value;
#define S_DEFINE_P_SEMANTIC_SET_GLOBAL_IMPL(name, value) // nothing

#define DECLARE_SEMANTIC_ENTER_SCOPE_IMPL() // nothing
#define P_DEFINE_SEMANTIC_ENTER_SCOPE_IMPL() // nothing
#define S_DEFINE_SEMANTIC_ENTER_SCOPE_IMPL() Scope_Enter();

#define DECLARE_SEMANTIC_EXIT_SCOPE_IMPL() // nothing
#define P_DEFINE_SEMANTIC_EXIT_SCOPE_IMPL() // nothing
#define S_DEFINE_SEMANTIC_EXIT_SCOPE_IMPL() Scope_Exit();

#define DECLARE_SEMANTIC_RULE_CONTAINER_SET_VARIABLE_IMPL(n, name, value) // nothing
#define P_DEFINE_SEMANTIC_RULE_CONTAINER_SET_VARIABLE_IMPL(n, name, value) if (var_0->type == n) {var_0->name = value;}
#define S_DEFINE_SEMANTIC_RULE_CONTAINER_SET_VARIABLE_IMPL(n, name, value) // nothing

#define begin_semantic_search(name, type1, type2) int Find_Method_##name(void* n, void* v) { struct type1* node = (struct type1*)n; struct type2* var = (struct type2*)v;
#define end_semantic_search() }
#define GET_VAR(n) var_##n

#define SCOPE_VARIABLE(name) scope->name
#define LAST_SCOPE_VARIABLE(name) scope->parent_scope->name

#define GET_CONTAINER_RULE(n, name) var_0->value.var_##n->name
#define GET_TERMINAL_VAR(n, name) var_##n->name

// Code Gen

#define codegen(value) ,CODE_GENERATION_IMPL(0 value)

#define DEFINE_CODE_GENERATION_IMPL(placeholder, ...) MACRO_FOR_EACH(GEN_,  __VA_ARGS__)
#define DECLARE_CODE_GENERATION_IMPL(placeholder, ...) MACRO_FOR_EACH(DECLARE_,  __VA_ARGS__)
#define INIT_CODE_GENERATION_IMPL(placeholder, ...) MACRO_FOR_EACH(DEFINE_,  __VA_ARGS__)

#define code(...) ,CODE_IMPL(__VA_ARGS__)
#define GEN_CODE_IMPL(...) fprintf(file, __VA_ARGS__);
#define DEFINE_CODE_IMPL(...) // nothing
#define DECLARE_CODE_IMPL(...) // nothing
#define codegen_continue() ,CODE_GEN_RECURSE_ALL_IMPL()

#define run(function_name, ...) ,RUN_IMPL(function_name, __VA_ARGS__)
#define GEN_RUN_IMPL(function_name, ...) function_name(file, __VA_ARGS__);
#define DEFINE_RUN_IMPL(function_name, ...) // nothing
#define DECLARE_RUN_IMPL(function_name, ...) // nothing

#define set(dst, src) ,SET_IMPL(dst, src)
#define GEN_SET_IMPL(dst, src) dst = src;
#define DEFINE_SET_IMPL(dst, src) // nothing
#define DECLARE_SET_IMPL(dst, src) // nothing

#define GEN_CODE_GEN_RECURSE_ALL_IMPL() recurse_all(file, var_0);
#define DECLARE_CODE_GEN_RECURSE_ALL_IMPL() // nothing
#define DEFINE_CODE_GEN_RECURSE_ALL_IMPL() // nothing

#define codegen_default() ,CODE_GENERATION_IMPL(0, CODE_GEN_RECURSE_ALL_IMPL())
#define CODE_GEN_TERMINAL_RECURSE(index) ,CODE_GEN_TERMINAL_RECURSE_IMPL(index)

#define GEN_CODE_GEN_TERMINAL_RECURSE_IMPL(index) recurse_##index(var_##index);
#define DECLARE_CODE_GEN_TERMINAL_RECURSE_IMPL(index) // nothing
#define DEFINE_CODE_GEN_TERMINAL_RECURSE_IMPL(index) // nothing

#define codegen_var(type_, name, value) ,CODE_GEN_VARIABLE_IMPL(type_, name, value)
#define codegen_set_var(n, name, value) ,CODE_GEN_SET_VARIABLE_IMPL(n, name, value)

#define DECLARE_CODE_GEN_VARIABLE_IMPL(type_, name, value) type_ name;
#define DEFINE_CODE_GEN_VARIABLE_IMPL(type_, name, value) var_0->name = value;
#define GEN_CODE_GEN_VARIABLE_IMPL(type_, name, value) // nothing

#define DECLARE_CODE_GEN_SET_VARIABLE_IMPL(n, name, value) // nothing
#define DEFINE_CODE_GEN_SET_VARIABLE_IMPL(n, name, value) // nothing
#define GEN_CODE_GEN_SET_VARIABLE_IMPL(n, name, value) var_##n->name = value;

#define codegen_alloc_table(name, ...) ,CODE_GEN_REGISTER_TABLE_IMPL(name,  GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define DECLARE_CODE_GEN_REGISTER_TABLE_IMPL(name, n, ...) struct Allocation_Table* name = NULL;
#define DEFINE_CODE_GEN_REGISTER_TABLE_IMPL(name, n, ...) 
#define SCOPE_DECLARE_CODE_GEN_REGISTER_TABLE_IMPL(name, n, ...)
#define SCOPE_DEFINE_CODE_GEN_REGISTER_TABLE_IMPL(name, n, ...) const char* strings_##name[] = {__VA_ARGS__}; name = Create_Allocation_Table(__STRING(name), strings_##name, n );

#define GET_ALLOCATION_VAR(name) Get_Allocation(name);

#define CODE_GEN_FREE_ALLOCATION(name, id) ,CODE_GEN_FREE_ALLOCATION_IMPL(name, id)
#define GEN_CODE_GEN_FREE_ALLOCATION_IMPL(name, id) Free_Allocation(name, id);
#define DEFINE_CODE_GEN_FREE_ALLOCATION_IMPL(name, id) // nothing
#define DECLARE_CODE_GEN_FREE_ALLOCATION_IMPL(name, id) // nothing

#define GET_ALLOCATION_STRING(name, id) Get_String_Allocation_ID(name, id)
#define GET_CODE_GEN_VARIABLE(n, name) var_##n->name


// tokens

#define TOKEN_RULE_STRUCT_TOKEN_IMPL(type_, str) \
    typedef struct type_ \
    { \
        struct Token* token; \
    } type_; \
    struct type_* Create_##type_(struct TokenBatch* batch); \
    void print_##type_(int layer, struct type_* p); \
    void semantic_##type_(struct type_* var); \
    void gen_code_##type_(FILE* file, struct type_* var);

#define CREATE_TOKEN_RULE_TOKEN_IMPL(type_, str) \
    struct type_* Create_##type_(struct TokenBatch* batch) \
    { \
        struct Token token = batch->tokens[batch->token_on]; \
        if (token.type == TOKEN_##type_) \
        { \
            type_* var_0 = malloc(sizeof(struct type_)); \
            var_0->token = &batch->tokens[batch->token_on]; \
            batch->token_on++; \
            return var_0; \
        } \
        return NULL; \
    } \
    void print_##type_(int layer, struct type_* p) {} \
    void semantic_##type_(struct type_* var) {} \
    void gen_code_##type_(FILE* file, struct type_* var) {}

#define tokens(value) ,TOKENS_IMPL(0 value)
#define DECLARE_TOKENS_IMPL(placeholder, ...) \
typedef enum \
{ \
    MACRO_FOR_EACH(ENUM_, __VA_ARGS__) \
} TokenType; \
const char* token_patterns[] = { \
    MACRO_FOR_EACH(STR_, __VA_ARGS__) \
}; \
int token_count = GET_ARG_COUNT(__VA_ARGS__); \
MACRO_FOR_EACH(TOKEN_RULE_STRUCT_, __VA_ARGS__)

#define ENUM_TOKEN_IMPL(name, str) TOKEN_##name,
#define STR_TOKEN_IMPL(name, str) str,

#define DEFINE_TOKENS_IMPL(placeholder, ...) MACRO_FOR_EACH(CREATE_TOKEN_RULE_ , __VA_ARGS__)
#define SCOPE_DECLARE_TOKENS_IMPL(placeholder, ...)
#define SCOPE_DEFINE_TOKENS_IMPL(placeholder, ...)
#define rules(...) ,RULES_IMPL(__VA_ARGS__)
#define EXPAND_RULES_IMPL(...) __VA_ARGS__

#define token(name, str) ,TOKEN_IMPL(name, str)

#define ignore_tokens(...) ,IGNORE_TOKENS_IMPL(__VA_ARGS__)
#define DECLARE_IGNORE_TOKENS_IMPL(...) \
int ignore_token(int i) \
{ \
    if (0 \
        RULE_FOR_EACH(_, AND_TOKEN, __VA_ARGS__) \
    ) \
    { \
        return 1; \
    } \
    return 0; \
}
#define DEFINE_IGNORE_TOKENS_IMPL(...)
#define SCOPE_DECLARE_IGNORE_TOKENS_IMPL(...)
#define SCOPE_DEFINE_IGNORE_TOKENS_IMPL(...)
#define AND_TOKEN_RULE_IMPL(token, n1, n2) || TOKEN_##token == i 

#define semantic_search_function(name, search_type, input_type, ...) ,SEMANTIC_SEARCH_FUNCTION_IMPL(name, search_type, input_type, __VA_ARGS__)

#define DECLARE_SEMANTIC_SEARCH_FUNCTION_IMPL(name, search_type, input_type, ...) int Find_Method_##name(void* n, void* v);
#define DEFINE_SEMANTIC_SEARCH_FUNCTION_IMPL(name, search_type, input_type, ...) \
int Find_Method_##name(void* n, void* v) { struct search_type* node = (struct search_type*)n; struct input_type* var = (struct input_type*)v; \
    __VA_ARGS__ \
}
#define SCOPE_DECLARE_SEMANTIC_SEARCH_FUNCTION_IMPL(name, search_type, input_type, ...)
#define SCOPE_DEFINE_SEMANTIC_SEARCH_FUNCTION_IMPL(name, search_type, input_type, ...)

#define TOKEN_CONTENTS(n) var_##n->token->value
#define TOKEN_LINE(n) var_##n->token->line;
#define TOKEN_COLUMN(n) var_##n->token->column;

#define CODE_SIZE() GetFileSize(file)


long GetFileSize(FILE *file) {
    // Save the current position of the file pointer
    long current_pos = ftell(file);
    if (current_pos == -1) {
        perror("ftell");
        return -1;  // Error getting the current position
    }

    // Move to the end of the file
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("fseek");
        return -1;  // Error moving to the end of the file
    }

    // Get the size of the file (current position is the file size)
    long size = ftell(file);
    if (size == -1) {
        perror("ftell");
        return -1;  // Error getting the size of the file
    }

    // Restore the original file pointer position
    fseek(file, current_pos, SEEK_SET);

    return size;
}






// create_compiler(Main_Compiler
//     tokens(
//         token(INT32, "^int32")
//         token(BOOL, "^bool")
//         token(RETURN, "^return")
//         token(PLUS, "^\\+")
//         token(MINUS, "^\\-")
//         token(MULTIPLY, "^\\*")
//         token(DIVIDE, "^\\/")
//         token(EQUAL, "^=")
//         token(GREATER, "^>")
//         token(LESS, "^<")
//         token(SEMICOLON, "^[;]")
//         token(COMMA, "^[,]")
//         token(OPEN_PAREN, "^[(]")
//         token(CLOSE_PAREN, "^[)]")
//         token(OPEN_BRACK, "^[{]")
//         token(CLOSE_BRACK, "^[}]")
//         token(IDENTIFIER, "^[a-zA-Z_][a-zA-Z0-9_]*")
//         token(NUMBER_LITERAL, "^[+-]?[0-9]+(\.[0-9]+)?")
//         token(WHITESPACE, "\\s+")
//         token(COMMENT, "(^//.*|\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/)")
//     )
//     ignore_tokens(
//         WHITESPACE,
//         COMMENT
//     )
//     semantic_search_function(MatchVariable, Identifier, Identifier,
//         if (!strcmp(var->contents, node->contents))
//         {
//             var->stackOffset = node->stackOffset;
//             return 1;
//         }
//         return 0;
//     )
//     scope_table(Variables)
//     scope_variable(int, stack_offset, 0)
//     scope_variable(int, next_stack_offset, 0)
//     codegen_alloc_table(Registers_table, "R1", "A1", "F2")


//     rule_container(Code
//         semantic_default()
//         codegen(
//             codegen_var(int, idk, 10)
//             codegen_continue()
//         )
//         rules(
//             Global_Statement
//         )
//     )
//     rule_container_next(Global_Statement
//         semantic_default()
//         codegen(
//             codegen_var(int, idk, 10)
//             codegen_continue()
//         )
//         rules(
//             Variable_Declaration,
//             Function_Declaration
//         )
//     )
//     terminal(Body
//         semantic(
//             semantic_var(int, stack_offset, 0)
//             enter_scope()
//             set_scope_variable(next_stack_offset, LAST_SCOPE_VARIABLE(next_stack_offset) + LAST_SCOPE_VARIABLE(stack_offset))
//             semantic_set_var_s(0, stack_offset, SCOPE_VARIABLE(next_stack_offset))
//             semantics_continue()
//             exit_scope()
//         )
//         codegen(
//             codegen_continue()
//         )
//         rules(
//             OPEN_BRACK,
//             Global_Statement,
//             CLOSE_BRACK
//         )
//     )
//     terminal(Function_Declaration
//         semantic_default()
//         codegen_default()
//         rules(
//             Variable_Type,
//             Identifier,
//             OPEN_PAREN,
//             CLOSE_PAREN,
//             Body
//         )
//     )
//     rule_container(Variable_Declaration
//         semantic_default()
//         codegen(
//             codegen_var(int, idk, 10)
//             codegen_continue()
//         )
//         rules(
//             Initialized_Variable_Declaration,
//             Uninitialized_Variable_Declaration
//         )
//     )
//     terminal(Initialized_Variable_Declaration
//         semantic(
//             search_add(Variables, GET_VAR(2))
//             set_scope_variable(stack_offset, SCOPE_VARIABLE(stack_offset) + GET_TERMINAL_VAR(1, size))
//             semantics_continue()
//         )
//         codegen(
//             codegen_continue()
//         )
//         rules(
//             Variable_Type,
//             Identifier,
//             EQUAL,
//             Expression,
//             SEMICOLON
//         )
//     )
//     terminal(Uninitialized_Variable_Declaration
//         semantic(
//             search_add(Variables, GET_VAR(2))
//             set_scope_variable(stack_offset, SCOPE_VARIABLE(stack_offset) + GET_TERMINAL_VAR(1, size))
//             semantics_continue()
//         )
//         codegen_default()
//         rules(
//             Variable_Type,
//             Identifier,
//             SEMICOLON
//         )
//     )
//     terminal(Simple_Simple_Expression
//         semantic_default()
//         codegen_default()
//         rules(
//             Simple_Expression,
//             Operator,
//             Simple_Expression
//         )
//     )
//     terminal(Simple_Complex_Expression
//         semantic_default()
//         codegen_default()
//         rules(
//             Simple_Expression,
//             Operator,
//             Complex_Expression
//         )
//     )
//     terminal(Complex_Simple_Expression
//         semantic_default()
//         codegen_default()
//         rules(
//             OPEN_PAREN,
//             Complex_Expression,
//             CLOSE_PAREN,
//             Operator,
//             Simple_Expression
//         )
//     )
//     terminal(Complex_Complex_Expression
//         semantic_default()
//         codegen_default()
//         rules(
//             OPEN_PAREN,
//             Complex_Expression,
//             CLOSE_PAREN,
//             Operator,
//             Complex_Expression
//         )
//     )
//     rule_container(Simple_Expression
//         semantic_default()
//         codegen_default()
//         rules(
//             Constant_Expression,
//             Variable_Expression,
//             Function_Expression
//         )
//     )
//     rule_container(Complex_Expression
//         semantic_default()
//         codegen_default()
//         rules(
//             Simple_Complex_Expression,
//             Simple_Simple_Expression,
//             Complex_Simple_Expression,
//             Complex_Complex_Expression
//         )
//     )
//     rule_container(Expression
//         semantic_default()
//         codegen_default()
//         rules(
//             Complex_Expression,
//             Simple_Expression
//         )
//     )
//     rule_container(Operator
//         semantic_default()
//         codegen_default()
//         rules(
//             PLUS,
//             MINUS,
//             MULTIPLY,
//             DIVIDE,
//             GREATER,
//             LESS,
//             EQUAL
//         )
//     )
//     terminal(Operator_Expression
//         semantic_default()
//         codegen_default()
//         rules(
//             Expression,
//             Operator,
//             Expression
//         )
//     )
//     terminal(Constant_Expression
//         semantic_default()
//         codegen_default()
//         rules(
//             Literal
//         )
//     )
//     terminal(Variable_Expression
//         semantic(
//             semantic_search(Variables, GET_VAR(1), MatchVariable)
//             semantics_continue()
//         )
//         codegen_default()
//         rules(
//             Identifier
//         )
//     )
//     rule_container(Primitive
//         semantic(
//             semantic_var(int, size, 0)
//             set_var_if_p(1, size, 32)
//             set_var_if_p(2, size, 32)
//             semantics_continue()
//         )
//         codegen_default()
//         rules(
//             INT32,
//             BOOL
//         )
//     )
//     rule_container(Variable_Type
//         semantic(
//             semantics_continue()
//             semantic_var(int, size, 0)
//             rule_set_var(1, size, 0)
//             rule_set_var(2, size, GET_CONTAINER_RULE(2, size))
//         )
//         codegen_default()
//         rules(
//             Identifier,
//             Primitive
//         )
//     )
//     terminal(Function_Expression
//         semantic_default()
//         codegen_default()
//         rules(
//             Identifier,
//             OPEN_PAREN,
//             CLOSE_PAREN,
//             SEMICOLON
//         )
//     )
//     terminal(Identifier
//         semantic(
//             semantic_var(int, stackOffset, 0)
//             semantic_var(char*, contents, "")
//             semantics_continue()
//             semantic_set_var_p(0, contents, TOKEN_CONTENTS(1))
//         )
//         codegen_default()
//         rules(
//             IDENTIFIER
//         )
//     )
//     terminal(Literal
//         semantic(
//             semantics_continue()
//             semantic_var(char*, contents, "")
//             semantic_set_var_p(0, contents, TOKEN_CONTENTS(1))
//         )
//         codegen_default()
//         rules(
//             NUMBER_LITERAL
//         )
//     )
// )


#pragma region MOV_Codegen_functions

unsigned char getModRM(unsigned char mod, unsigned char reg, unsigned char rm) {
    unsigned char modRM = (mod << 6) | (reg << 3) | rm;
    return modRM;
}

void hexStringToByteArray(FILE* file, const char* hexString, int size) {
    // Skip the "0x" prefix if it exists
    const char* hex = hexString;
    if (strncmp(hexString, "0x", 2) == 0) {
        hex = hexString + 2;
    }

    size_t length = strlen(hex);

    // Ensure that the string length is even
    if (length % 2 != 0) {
        length++;  // Make it even by considering the next character as zero
    }

    size_t byteArraySize = length / 2;
    // Convert hex string to byte array
    for (size_t i = 0; i < byteArraySize; ++i) {
        u_int8_t* byte;
        sscanf(hex + 2 * byteArraySize - 2 * (i+1), "%2hhx", &byte);
        fprintf(file, "%c", byte);
    }
    if (size - (int)byteArraySize > 0)
    {
        for (int i = 0; i < size - byteArraySize; i++)
        {
            fprintf(file, "%c", 0);
        }
    }
}

int file_pointer = 0;
int hexStringSize(const char* hexString) {
    // Skip the "0x" prefix if it exists
    const char* hex = hexString;
    if (strncmp(hexString, "0x", 2) == 0) {
        hex = hexString + 2;
    }

    size_t length = strlen(hex);

    // Ensure that the string length is even
    if (length % 2 != 0) {
        length++;  // Make it even by considering the next character as zero
    }

    return length / 2;
}
// Function to convert unsigned 32-bit to byte array
void handleLoadOffset(FILE* file, int num, int src, int dst) {
    if (num < -127 || num > 127)
    {
        fprintf(file, "%c", getModRM(0b10, src, dst));
        fprintf(file, "%c%c%c%c", num & 0xFF, (num >> 8) & 0xFF, (num >> 16) & 0xFF, (num >> 24) & 0xFF);
    }
    else
    {
        fprintf(file, "%c", getModRM(0b01, src, dst));
        fprintf(file, "%c", num);
    }
}

void handleComplexLoadOffset(FILE* file, int num, int mod, int src_l, int src_r, int dst) {
    if (num < -127 || num > 127)
    {
        fprintf(file, "%c%c", getModRM(0b10, dst, 0b100), getModRM(mod, src_r, src_l));
        fprintf(file, "%c%c%c%c", num & 0xFF, (num >> 8) & 0xFF, (num >> 16) & 0xFF, (num >> 24) & 0xFF);
    }
    else
    {
        fprintf(file, "%c%c", getModRM(0b01, dst, 0b100), getModRM(mod, src_r, src_l));
        fprintf(file, "%c", num);
    }
}
// mov r r
void fileprint_r_r_instruction(FILE* file, u_int8_t instruction, int left_register_size, int left_register_value, int right_register_size, int right_register_value)
{
    if (left_register_size == 8 && right_register_size == 8)
    {
        fprintf(file, "%c%c", instruction-2, getModRM(0b11, right_register_value, left_register_value));
    }
    else if (left_register_size == 16 && right_register_size == 16)
    {
        fprintf(file, "%c%c%c", 0x66, instruction-1, getModRM(0b11, right_register_value, left_register_value));
    }
    else if (left_register_size == 32 && right_register_size == 32)
    {
        fprintf(file, "%c%c", instruction-1, getModRM(0b11, right_register_value, left_register_value));
    }
    else if (left_register_size == 64 && right_register_size == 64)
    {
        fprintf(file, "%c%c%c", 0x48, instruction-1, getModRM(0b11, right_register_value, left_register_value));
    }
}

void fileprint_r_imm_instruction(FILE* file, u_int8_t instruction, int left_register_size, int left_register_value, const char* imm)
{
    if (instruction == 0xb0)
    {
        if (left_register_size == 8)
        {
            fprintf(file, "%c", 0xB0 + left_register_value);
            hexStringToByteArray(file, imm, 1);
        }
        else if (left_register_size == 16)
        {
            fprintf(file, "%c%c", 0x66, 0xB8 + left_register_value);
            hexStringToByteArray(file, imm, 2);
        }
        else if (left_register_size == 32)
        {
            fprintf(file, "%c", 0xB8 + left_register_value);
            hexStringToByteArray(file, imm, 4);
        }
        else if (left_register_size == 64)
        {
            int size = hexStringSize(imm);
            if (size <= 4)
            {
                fprintf(file, "%c%c%c", 0x48, 0xC7, 0xC0 + left_register_value);
                hexStringToByteArray(file, imm, 4);
            }
            else
            {
                fprintf(file, "%c%c", 0x48, 0xB8 + left_register_value);
                hexStringToByteArray(file, imm, 8);
            }
        }
    }
    else
    {
    // instruction is 0xB0
        if (left_register_size == 8)
        {
            fprintf(file, "%c%c", 0x80, instruction + left_register_value);
            hexStringToByteArray(file, imm, 1);
        }
        else if (left_register_size == 16)
        {
            int size = hexStringSize(imm);
            if (size == 1)
            {
                fprintf(file, "%c%c%c", 0x66, 0x83, instruction + left_register_value);
                hexStringToByteArray(file, imm, 1);
            }
            else
            {
                fprintf(file, "%c%c%c", 0x66, 0x81, instruction + left_register_value);
                hexStringToByteArray(file, imm, 2);
            }
        }
        else if (left_register_size == 32)
        {
            int size = hexStringSize(imm);
            if (size == 1)
            {
                fprintf(file, "%c%c", 0x83, instruction + left_register_value);
                hexStringToByteArray(file, imm, 1);
            }
            else
            {
                fprintf(file, "%c%c", 0x81, instruction + left_register_value);
                hexStringToByteArray(file, imm, 4);
            }
        }
        else if (left_register_size == 64)
        {
            int size = hexStringSize(imm);
            if (size == 1)
            {
                fprintf(file, "%c%c%c", 0x48, 0x83, instruction + left_register_value);
                hexStringToByteArray(file, imm, 1);
            }
            else
            {
                fprintf(file, "%c%c%c", 0x48, 0x81, instruction + left_register_value);
                hexStringToByteArray(file, imm, 4);
            }
        }
    }
}
// MOV r [r]
void fileprint_r_indirect_instruction(FILE* file, u_int8_t instruction, int inverse, int left_register_size, int left_register_value, int right_register_size, int right_register_value)
{
    if (inverse)
    {
        instruction -= 2;
    }

    if (right_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    if (left_register_size == 8)
    {
        fprintf(file, "%c%c", instruction, getModRM(0b00, right_register_value, left_register_value));
    }
    else if (left_register_size == 16)
    {
        fprintf(file, "%c%c%c", 0x66, instruction+1, getModRM(0b00, right_register_value, left_register_value));
    }
    else if (left_register_size == 32)
    {
        fprintf(file, "%c%c", instruction+1, getModRM(0b00, right_register_value, left_register_value));
    }
    else if (left_register_size == 64)
    {
        fprintf(file, "%c%c%c", 0x48, instruction+1, getModRM(0b00, right_register_value, left_register_value));
    }
}
// mov r [n]
void fileprint_r_direct_instruction(FILE* file, u_int8_t instruction, int inverse, int left_register_size, int left_register_value, const char* hex)
{
    if (inverse)
    {
        instruction -= 2;
    }

    if (left_register_size == 8)
    {
        fprintf(file, "%c%c%c", instruction, getModRM(0b00, left_register_value, 0b100), 0x25);
        hexStringToByteArray(file, hex, 4);
    }
    else if (left_register_size == 16)
    {
        fprintf(file, "%c%c%c%c", 0x66, instruction+1, getModRM(0b00, left_register_value, 0b100), 0x25);
        hexStringToByteArray(file, hex, 4);
    }
    else if (left_register_size == 32)
    {
        fprintf(file, "%c%c%c", instruction+1, getModRM(0b00, left_register_value, 0b100), 0x25);
        hexStringToByteArray(file, hex, 4);
    }
    else if (left_register_size == 64)
    {
        fprintf(file, "%c%c%c%c", 0x48, instruction+1, getModRM(0b00, left_register_value, 0b100), 0x25);
        hexStringToByteArray(file, hex, 4);
    }
}
// mov r [r+n]
void fileprint_r_offset_instruction(FILE* file, u_int8_t instruction, int inverse, int offset, int left_register_size, int left_register_value, int right_register_size, int right_register_value)
{
    if (inverse)
    {
        instruction -= 2;
    }

    if (right_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    if (left_register_size == 8)
    {
        fprintf(file, "%c", instruction);
        handleLoadOffset(file, offset, left_register_value, right_register_value);
    }
    else if (left_register_size == 16)
    {
        fprintf(file, "%c%c", 0x66, instruction+1);
        handleLoadOffset(file, offset, left_register_value, right_register_value);
    }
    else if (left_register_size == 32)
    {
        fprintf(file, "%c", instruction+1);
        handleLoadOffset(file, offset, left_register_value, right_register_value);
    }
    else if (left_register_size == 64)
    {
        fprintf(file, "%c%c", 0x48, instruction+1);
        handleLoadOffset(file, offset, left_register_value, right_register_value);
    }

}
// mov r [r+r*n]
void fileprint_r_scaled_instruction(FILE* file, u_int8_t instruction, int inverse, int left_register_size, int left_register_value, int right_left_register_size, int right_left_register_value, int right_right_register_size, int right_right_register_value, int multiple)
{
    if (inverse)
    {
        instruction -= 2;
    }

    if (right_left_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    int mod = 0;
    if (multiple == 1)
    {
        mod = 0b00;
    }
    else if (multiple == 2)
    {
        mod = 0b01;
    }
    else if (multiple == 4)
    {
        mod = 0b10;
    }
    else if (multiple == 8)
    {
        mod = 0b11;
    }
    

    if (left_register_size == 8)
    {
        fprintf(file, "%c%c%c", instruction, getModRM(0b00, left_register_value, 0b100), getModRM(mod, right_right_register_value, right_left_register_value));
    }
    else if (left_register_size == 16)
    {
        fprintf(file, "%c%c%c%c", 0x66, instruction+1, getModRM(0b00, left_register_value, 0b100), getModRM(mod, right_right_register_value, right_left_register_value));
    }
    else if (left_register_size == 32)
    {
        fprintf(file, "%c%c%c", instruction+1, getModRM(0b00, left_register_value, 0b100), getModRM(mod, right_right_register_value, right_left_register_value));
    }
    else if (left_register_size == 64)
    {
        fprintf(file, "%c%c%c%c", 0x48, instruction+1, getModRM(0b00, left_register_value, 0b100), getModRM(mod, right_right_register_value, right_left_register_value));
    }
}
// mov r [r+r]
void fileprint_r_indexed_instruction(FILE* file, u_int8_t instruction, int inverse, int left_register_size, int left_register_value, int right_left_register_size, int right_left_register_value, int right_right_register_size, int right_right_register_value)
{
    fileprint_r_scaled_instruction(file, instruction, inverse, left_register_size, left_register_value, right_left_register_size, right_left_register_value, right_right_register_size, right_right_register_value, 1);
}
// mov r [r+r*n+n]
void fileprint_r_complex_instruction(FILE* file, u_int8_t instruction, int inverse, int left_register_size, int left_register_value, int right_left_register_size, int right_left_register_value, int right_right_register_size, int right_right_register_value, int multiple, int offset)
{
    if (inverse)
    {
        instruction-=2;
    }

    if (right_left_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    int mod = 0;
    if (multiple == 1)
    {
        mod = 0b00;
    }
    else if (multiple == 2)
    {
        mod = 0b01;
    }
    else if (multiple == 4)
    {
        mod = 0b10;
    }
    else if (multiple == 8)
    {
        mod = 0b11;
    }

    if (left_register_size == 8)
    {
        fprintf(file, "%c", instruction);
        handleComplexLoadOffset(file, offset, mod, right_left_register_value, right_right_register_value, left_register_value);
    }
    else if (left_register_size == 16)
    {
        fprintf(file, "%c%c", 0x66, instruction+1);
        handleComplexLoadOffset(file, offset, mod, right_left_register_value, right_right_register_value, left_register_value);
    }
    else if (left_register_size == 32)
    {
        fprintf(file, "%c", instruction+1);
        handleComplexLoadOffset(file, offset, mod, right_left_register_value, right_right_register_value, left_register_value);
    }
    else if (left_register_size == 64)
    {
        fprintf(file, "%c%c", 0x48, instruction+1);
        handleComplexLoadOffset(file, offset, mod, right_left_register_value, right_right_register_value, left_register_value);
    }
}





#pragma endregion

#pragma region MUL_Codegen_functions
void fileprint_r_instruction(FILE* file, int instruction, u_int8_t group, int register_size, int register_value)
{
    if (register_size == 8)
    {
        fprintf(file, "%c%c", group-1, getModRM(0b11, instruction, register_value));
    }
    else if (register_size == 16)
    {
        fprintf(file, "%c%c%c", 0x66, group, getModRM(0b11, instruction, register_value));
    }
    else if (register_size == 32)
    {
        fprintf(file, "%c%c", group, getModRM(0b11, instruction, register_value));
    }
    else if (register_size == 64)
    {
        fprintf(file, "%c%c%c", 0x48, group, getModRM(0b11, instruction, register_value));
    }
}
void fileprint_indirect_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int register_size, int register_value)
{
    if (register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    if (size_specifier == 8)
    {
        fprintf(file, "%c%c", group-1, getModRM(0b00, instruction, register_value));
    }
    else if (size_specifier == 16)
    {
        fprintf(file, "%c%c%c", 0x66, group, getModRM(0b00, instruction, register_value));
    }
    else if (size_specifier == 32)
    {
        fprintf(file, "%c%c", group, getModRM(0b00, instruction, register_value));
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c%c%c", 0x48, group, getModRM(0b00, instruction, register_value));
    }
}
// CHANGE THE WAY WE ARE DOING INSTRUCTIONS SO IT IS PROPER
void fileprint_offset_instruction(FILE* file, u_int8_t instruction, u_int8_t group, int size_specifier, int register_size, int register_value, int offset)
{

    if (register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    if (size_specifier == 8)
    {
        fprintf(file, "%c", group-1);
        handleLoadOffset(file, offset, instruction, register_value);
    }
    else if (size_specifier == 16)
    {
        fprintf(file, "%c%c", 0x66, group);
        handleLoadOffset(file, offset, instruction, register_value);
    }
    else if (size_specifier == 32)
    {
        fprintf(file, "%c", group);
        handleLoadOffset(file, offset, instruction, register_value);
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c%c", 0x48, group);
        handleLoadOffset(file, offset, instruction, register_value);
    }

}
void fileprint_scaled_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value, int multiple)
{
    if (left_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    int mod = 0;
    if (multiple == 1)
    {
        mod = 0b00;
    }
    else if (multiple == 2)
    {
        mod = 0b01;
    }
    else if (multiple == 4)
    {
        mod = 0b10;
    }
    else if (multiple == 8)
    {
        mod = 0b11;
    }

    if (size_specifier == 8)
    {
        fprintf(file, "%c%c%c", group-1, getModRM(0b00, instruction, 0b100), getModRM(mod, right_register_value, left_register_value));
    }
    else if (size_specifier == 16)
    {
        fprintf(file, "%c%c%c%c", 0x66, group,  getModRM(0b00, instruction, 0b100), getModRM(mod, right_register_value, left_register_value));
    }
    else if (size_specifier == 32)
    {
        fprintf(file, "%c%c%c", group,  getModRM(0b00, instruction, 0b100), getModRM(mod, right_register_value, left_register_value));
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c%c%c%c", 0x48, group,  getModRM(0b00, instruction, 0b100), getModRM(mod, right_register_value, left_register_value));
    }
}
void fileprint_indexed_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value)
{
    fileprint_scaled_instruction(file, instruction, group, size_specifier, left_register_size, left_register_value, right_register_size, right_register_value, 1);
}
void fileprint_complex_instruction(FILE* file, u_int8_t instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value, int multiple, int offset)
{


    if (left_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    int mod = 0;
    if (multiple == 1)
    {
        mod = 0b00;
    }
    else if (multiple == 2)
    {
        mod = 0b01;
    }
    else if (multiple == 4)
    {
        mod = 0b10;
    }
    else if (multiple == 8)
    {
        mod = 0b11;
    }

    if (size_specifier == 8)
    {
        fprintf(file, "%c", group - 1);
        handleComplexLoadOffset(file, offset, mod, left_register_value, right_register_value, instruction);
    }
    else if (size_specifier == 16)
    {
        fprintf(file, "%c%c", 0x66, group);
        handleComplexLoadOffset(file, offset, mod, left_register_value, right_register_value, instruction);
    }
    else if (size_specifier == 32)
    {
        fprintf(file, "%c", group);
        handleComplexLoadOffset(file, offset, mod, left_register_value, right_register_value, instruction);
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c%c", 0x48, group);
        handleComplexLoadOffset(file, offset, mod, left_register_value, right_register_value, instruction);
    }
}
#pragma endregion
#pragma region Pop_Push
void fileprint_pp_r_instruction(FILE* file, int instruction, u_int8_t group, int register_size, int register_value)
{
    if (instruction == 0b110)
    {
        if (register_size == 16)
        {
            fprintf(file, "%c%c", 0x66, 0x50 + register_value);
        }
        else if (register_size == 64)
        {
            fprintf(file, "%c", 0x50 + register_value);
        }
    }
    else
    {
        if (register_size == 16)
        {
            fprintf(file, "%c%c", 0x66, 0x58 + register_value);
        }
        else if (register_size == 64)
        {
            fprintf(file, "%c", 0x58 + register_value);
        }
    }
    
}
void fileprint_pp_indirect_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int register_size, int register_value)
{
    if (register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    if (size_specifier == 16)
    {
        fprintf(file, "%c%c%c", 0x66, group, getModRM(0b00, instruction, register_value));
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c%c", group, getModRM(0b00, instruction, register_value));
    }
}
// CHANGE THE WAY WE ARE DOING INSTRUCTIONS SO IT IS PROPER
void fileprint_pp_offset_instruction(FILE* file, u_int8_t instruction, u_int8_t group, int size_specifier, int register_size, int register_value, int offset)
{

    if (register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    if (size_specifier == 16)
    {
        fprintf(file, "%c%c", 0x66, group);
        handleLoadOffset(file, offset, instruction, register_value);
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c", group);
        handleLoadOffset(file, offset, instruction, register_value);
    }
}

void fileprint_pp_scaled_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value, int multiple)
{
    if (left_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    int mod = 0;
    if (multiple == 1)
    {
        mod = 0b00;
    }
    else if (multiple == 2)
    {
        mod = 0b01;
    }
    else if (multiple == 4)
    {
        mod = 0b10;
    }
    else if (multiple == 8)
    {
        mod = 0b11;
    }


    if (size_specifier == 16)
    {
        fprintf(file, "%c%c%c%c", 0x66, group,  getModRM(0b00, instruction, 0b100), getModRM(mod, right_register_value, left_register_value));
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c%c%c", group,  getModRM(0b00, instruction, 0b100), getModRM(mod, right_register_value, left_register_value));
    }
}
void fileprint_pp_indexed_instruction(FILE* file, int instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value)
{
    fileprint_pp_scaled_instruction(file, instruction, group, size_specifier, left_register_size, left_register_value, right_register_size, right_register_value, 1);
}
void fileprint_pp_complex_instruction(FILE* file, u_int8_t instruction, u_int8_t group, int size_specifier, int left_register_size, int left_register_value, int right_register_size, int right_register_value, int multiple, int offset)
{
    if (left_register_size == 32)
    {
        fprintf(file, "%c", 0x67);
    }

    int mod = 0;
    if (multiple == 1)
    {
        mod = 0b00;
    }
    else if (multiple == 2)
    {
        mod = 0b01;
    }
    else if (multiple == 4)
    {
        mod = 0b10;
    }
    else if (multiple == 8)
    {
        mod = 0b11;
    }

    if (size_specifier == 16)
    {
        fprintf(file, "%c%c", 0x66, group);
        handleComplexLoadOffset(file, offset, mod, left_register_value, right_register_value, instruction);
    }
    else if (size_specifier == 64)
    {
        fprintf(file, "%c", group);
        handleComplexLoadOffset(file, offset, mod, left_register_value, right_register_value, instruction);
    }
}
#pragma endregion

create_compiler(idk
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
    ignore_tokens(
        WHITESPACE
    )
    semantic_search_function(MatchVariable, Label, IDENTIFIER,
        if (!strcmp(var->token->value, node->value))
        {
            return 1;
        }
        return 0;
    )
    scope_table(Labels)
    rule_container(Code
        semantic()
        codegen_default()
        rules(
            Statement
        )
    )
    rule_container_next(Statement
        semantic_default()
        codegen_default()
        rules(
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
    terminal(NOP_instruction
        semantic_default()
        codegen(
            code("%c", 0x90)
            codegen_continue()
        )
        rules(
            NOP
        )
    )
    terminal(RET_instruction
        semantic_default()
        codegen(
            code("%c", 0xc3)
            codegen_continue()
        )
        rules(
            RET
        )
    )
    rule_container(Plus_Minus
        semantic(
            semantic_var(int, val, 0)
            set_var_if_p(0, val, 1)
            set_var_if_p(1, val, -1)
        )
        codegen_default()
        rules(
            PLUS,
            MINUS
        )
    )
    terminal(Label
        semantic(
            semantic_var(int, ptr, 0)
            semantic_var(char*, value, 0)
            search_add(Labels, var_0)
            semantics_continue()
        )
        codegen(
            set(var_0->ptr, CODE_SIZE())
            set(var_0->value, var_1->token->value)
            codegen_continue()
        )
        rules(
            IDENTIFIER,
            COLON
        )
    )
#pragma region Registers
    rule_container(Register64
        semantic(
            semantic_var(int, reg_value, 0)
            semantic_var(int, val_added_code, 2)
            semantic_var(int, mem_added_code, 0)
            set_var_if_p(0, reg_value, 0)
            set_var_if_p(1, reg_value, 1)
            set_var_if_p(2, reg_value, 2)
            set_var_if_p(3, reg_value, 3)
            set_var_if_p(4, reg_value, 4)
            set_var_if_p(5, reg_value, 5)
            set_var_if_p(6, reg_value, 6)
            set_var_if_p(7, reg_value, 7)
        )
        codegen_default()
        rules(
            RAX,
            RCX,
            RDX,
            RBX,
            RSP,
            RBP,
            RSI,
            RDI
        )
    )
    rule_container(Register32
        semantic(
            semantic_var(unsigned char, reg_value, 0)
            semantic_var(int, val_added_code, 1)
            semantic_var(int, mem_added_code, 1)
            set_var_if_p(0, reg_value, 0)
            set_var_if_p(1, reg_value, 1)
            set_var_if_p(2, reg_value, 2)
            set_var_if_p(3, reg_value, 3)
            set_var_if_p(4, reg_value, 4)
            set_var_if_p(5, reg_value, 5)
            set_var_if_p(6, reg_value, 6)
            set_var_if_p(7, reg_value, 7)
        )
        codegen_default()
        rules(
            EAX,
            ECX,
            EDX,
            EBX,
            ESP,
            EBP,
            ESI,
            EDI
        )
    )
    rule_container(Register16
        semantic(
            semantic_var(unsigned char, reg_value, 0)
            semantic_var(int, val_added_code, 2)
            semantic_var(int, mem_added_code, 0)
            set_var_if_p(0, reg_value, 0)
            set_var_if_p(1, reg_value, 1)
            set_var_if_p(2, reg_value, 2)
            set_var_if_p(3, reg_value, 3)
            set_var_if_p(4, reg_value, 4)
            set_var_if_p(5, reg_value, 5)
            set_var_if_p(6, reg_value, 6)
            set_var_if_p(7, reg_value, 7)
        )
        codegen_default()
        rules(
            AX,
            CX,
            DX,
            BX,
            SP,
            BP,
            SI,
            DI
        )
    )
    rule_container(Register8
        semantic(
            semantic_var(unsigned char, reg_value, 0)
            semantic_var(int, val_added_code, 1)
            semantic_var(int, mem_added_code, 0)
            set_var_if_p(0, reg_value, 0)
            set_var_if_p(1, reg_value, 1)
            set_var_if_p(2, reg_value, 2)
            set_var_if_p(3, reg_value, 3)
            set_var_if_p(4, reg_value, 4)
            set_var_if_p(5, reg_value, 5)
            set_var_if_p(6, reg_value, 6)
            set_var_if_p(7, reg_value, 7)
        )
        codegen_default()
        rules(
            AL,
            CL,
            DL,
            BL,
            AH,
            CH,
            DH,
            BH
        )
    )
    rule_container(Register
        semantic(
            semantic_var(unsigned char, reg_value, 0)
            semantic_var(int, reg_size, 0)
            semantic_var(int, val_added_code, 0)
            semantic_var(int, mem_added_code, 0)
            set_var_if_p(0, val_added_code, var_1->val_added_code)
            set_var_if_p(1, val_added_code, var_2->val_added_code)
            set_var_if_p(2, val_added_code, var_3->val_added_code)
            set_var_if_p(3, val_added_code, var_4->val_added_code)
            set_var_if_p(0, mem_added_code, var_1->mem_added_code)
            set_var_if_p(1, mem_added_code, var_2->mem_added_code)
            set_var_if_p(2, mem_added_code, var_3->mem_added_code)
            set_var_if_p(3, mem_added_code, var_4->mem_added_code)
            set_var_if_p(0, reg_value, var_1->reg_value)
            set_var_if_p(1, reg_value, var_2->reg_value)
            set_var_if_p(2, reg_value, var_3->reg_value)
            set_var_if_p(3, reg_value, var_4->reg_value)
            set_var_if_p(0, reg_size, 8)
            set_var_if_p(1, reg_size, 16)
            set_var_if_p(2, reg_size, 32)
            set_var_if_p(3, reg_size, 64)
        )
        codegen_default()
        rules(
            Register8,
            Register16,
            Register32,
            Register64
        )
    )
#pragma endregion
#pragma region instructions
    rule_container(Multi_Purpose_Instruction
        semantic(
            semantic_var(unsigned char, r, 0)
            semantic_var(unsigned char, imm, 0)
            set_var_if_p(0, r, 0x8A)
            set_var_if_p(0, imm, 0xB0)
            set_var_if_p(1, r, 0x02)
            set_var_if_p(1, imm, 0xC0)
            set_var_if_p(2, r, 0x2A)
            set_var_if_p(2, imm, 0xE8)
            set_var_if_p(3, r, 0x0A)
            set_var_if_p(3, imm, 0xC8)
            set_var_if_p(4, r, 0x22)
            set_var_if_p(4, imm, 0xE0)
            set_var_if_p(5, r, 0x3A)
            set_var_if_p(5, imm, 0xF8)
            set_var_if_p(6, r, 0x12)
            set_var_if_p(6, imm, 0xD0)
            set_var_if_p(7, r, 0x1A)
            set_var_if_p(7, imm, 0xD8)
            set_var_if_p(8, r, 0x32)
            set_var_if_p(8, imm, 0xF0)
            set_var_if_p(9, r, 0x86)
            set_var_if_p(9, imm, 0xC0)
        )
        codegen_default()
        rules(
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
    )
    rule_container(Bitwise_Instruction
        semantic(
            semantic_var(unsigned char, instruction, 0)
            semantic_var(unsigned char, group, 0xF7)
            set_var_if_p(0, instruction, 0b000)
            set_var_if_p(1, instruction, 0b001)
            set_var_if_p(2, instruction, 0b010)
            set_var_if_p(3, instruction, 0b011)
            set_var_if_p(4, instruction, 0b100)
            set_var_if_p(5, instruction, 0b100)
            set_var_if_p(6, instruction, 0b101)
            set_var_if_p(7, instruction, 0b111)
        )
        codegen_default()
        rules(
            ROL,
            ROR,
            RCL,
            RCR,
            SHL,
            SAL,
            SHR,
            SAR
        )
    )
    rule_container(Miscellaneous_Arithmetic_Instruction
        semantic(
            semantic_var(unsigned char, instruction, 0)
            semantic_var(unsigned char, group, 0xF7)
            set_var_if_p(0, instruction, 0b100)
            set_var_if_p(1, instruction, 0b101)
            set_var_if_p(2, instruction, 0b110)
            set_var_if_p(3, instruction, 0b111)
            set_var_if_p(4, instruction, 0b010)
            set_var_if_p(5, instruction, 0b011)
        )
        codegen_default()
        rules(
            MUL,
            IMUL,
            DIV,
            IDIV,
            NOT,
            NEG
        )
    )
    rule_container(Inc_Dec_Instruction
        semantic(
            semantic_var(unsigned char, instruction, 0)
            semantic_var(unsigned char, group, 0xFF)
            set_var_if_p(0, instruction, 0b000)
            set_var_if_p(1, instruction, 0b001)
        )
        codegen_default()
        rules(
            INC,
            DEC
        )
    )
    rule_container(Push_Pop_Instructions
        semantic(
            semantic_var(unsigned char, instruction, 0)
            semantic_var(unsigned char, group, 0)
            set_var_if_p(0, instruction, 0b110)
            set_var_if_p(0, group, 0xFF)
            set_var_if_p(1, instruction, 0b000)
            set_var_if_p(1, group, 0x8F)
        )
        codegen_default()
        rules(
            PUSH,
            POP
        )
    )
    rule_container(unary_instructions
        semantic(
            semantic_var(unsigned char, instruction, 0)
            semantic_var(unsigned char, group, 0)
            set_var_if_p(0, instruction, var_1->instruction)
            set_var_if_p(0, group, var_1->group)
            set_var_if_p(1, instruction, var_2->instruction)
            set_var_if_p(1, group, var_2->group)
        )
        codegen_default()
        rules(
            Miscellaneous_Arithmetic_Instruction,
            Inc_Dec_Instruction
        )
    )
    rule_container(Size_Specifier
        semantic(
            semantic_var(int, size, 0)
            set_var_if_p(0, size, 8)
            set_var_if_p(1, size, 16)
            set_var_if_p(2, size, 32)
            set_var_if_p(3, size, 64)
        )
        codegen_default()
        rules(
            BYTE,
            WORD,
            DWORD,
            QWORD
        )
    )
#pragma endregion
#pragma region MOV
    terminal(MOV_r_r_instruction
        semantic_default()
        codegen(
            run(fileprint_r_r_instruction, var_1->r, var_2->reg_size, var_2->reg_value, var_3->reg_size, var_3->reg_value)
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
            Register,
            Register
        )
    )
    terminal(MOV_r_imm_instruction
        semantic_default()
        codegen(
            run(fileprint_r_imm_instruction, var_1->imm, var_2->reg_size, var_2->reg_value, var_3->token->value)
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
            Register,
            HEX_LITERAL
        )
    )
    terminal(MOV_r_direct_instruction
        semantic_default()
        codegen(
            run(fileprint_r_direct_instruction, var_1->r, 0, var_2->reg_size, var_2->reg_value, var_4->token->value)
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
            Register,
            OPEN_BRACK,
            HEX_LITERAL,
            CLOSE_BRACK
        )
    )
    terminal(MOV_r_indirect_instruction
        semantic_default()
        codegen(
            run(fileprint_r_indirect_instruction, var_1->r, 0, var_2->reg_size, var_2->reg_value, var_4->reg_size, var_4->reg_value)
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
            Register,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK
        )
    )
    terminal(MOV_r_offset_instruction
        semantic_default()
        codegen(
            run(fileprint_r_offset_instruction, var_1->r, 0, atoi(var_6->token->value) * var_5->val, var_2->reg_size, var_2->reg_value, var_4->reg_size, var_4->reg_value)
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
            Register,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK
        )
    )
    terminal(MOV_r_indexed_instruction
        semantic_default()
        codegen(
            run(fileprint_r_indexed_instruction, var_1->r, 0, var_2->reg_size, var_2->reg_value, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value)
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
            Register,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            CLOSE_BRACK
        )
    )
    terminal(MOV_r_scaled_instruction
        semantic_default()
        codegen(
            run(fileprint_r_scaled_instruction, var_1->r, 0, var_2->reg_size, var_2->reg_value, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value, atoi(var_8->token->value))
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
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
    terminal(MOV_r_complex_instruction
        semantic_default()
        codegen(
            run(fileprint_r_complex_instruction, var_1->r, 0, var_2->reg_size, var_2->reg_value, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value, atoi(var_8->token->value), atoi(var_10->token->value) * var_9->val)
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
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
    terminal(MOV_direct_r_instruction
        semantic_default()
        codegen(
            run(fileprint_r_direct_instruction, var_1->r, 1, var_5->reg_size, var_5->reg_value, var_3->token->value)
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
            OPEN_BRACK,
            HEX_LITERAL,
            CLOSE_BRACK,
            Register
        )
    )
    terminal(MOV_indirect_r_instruction
        semantic_default()
        codegen(
            run(fileprint_r_indirect_instruction, var_1->r, 1, var_5->reg_size, var_5->reg_value, var_3->reg_size, var_3->reg_value)
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK,
            Register
        )
    )
    terminal(MOV_offset_r_instruction
        semantic_default()
        codegen(
            run(fileprint_r_offset_instruction, var_1->r, 1, atoi(var_5->token->value) * var_4->val, var_7->reg_size, var_7->reg_value, var_3->reg_size, var_3->reg_value)
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK,
            Register
        )
    )
    terminal(MOV_indexed_r_instruction
        semantic_default()
        codegen(
            run(fileprint_r_indexed_instruction, var_1->r, 1, var_7->reg_size, var_7->reg_value, var_3->reg_size, var_3->reg_value, var_5->reg_size, var_5->reg_value)
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            CLOSE_BRACK,
            Register
        )
    )
    terminal(MOV_scaled_r_instruction
        semantic_default()
        codegen(
            run(fileprint_r_scaled_instruction, var_1->r, 1, var_9->reg_size, var_9->reg_value, var_3->reg_size, var_3->reg_value, var_5->reg_size, var_5->reg_value, atoi(var_7->token->value))
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
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
    terminal(MOV_complex_r_instruction
        semantic_default()
        codegen(
            run(fileprint_r_complex_instruction, var_1->r, 1, var_11->reg_size, var_11->reg_value, var_3->reg_size, var_3->reg_value, var_5->reg_size, var_5->reg_value, atoi(var_7->token->value), atoi(var_9->token->value) * var_8->val)
            codegen_continue()
        )
        rules(
            Multi_Purpose_Instruction,
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
#pragma endregion
#pragma region MUL
    terminal(r_instruction
        semantic_default()
        codegen(
            run(fileprint_r_instruction, var_1->instruction, var_1->group, var_2->reg_size, var_2->reg_value)
            codegen_continue()
        )
        rules(
            unary_instructions,
            Register
        )
    )
    terminal(indirect_instruction
        semantic_default()
        codegen(
            run(fileprint_indirect_instruction, var_1->instruction, var_1->group, var_2->size, var_4->reg_size, var_4->reg_value)
            codegen_continue()
        )
        rules(
            unary_instructions,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK
        )
    )
    terminal(index_instruction
        semantic_default()
        codegen(
            run(fileprint_indexed_instruction, var_1->instruction, var_1->group, var_2->size, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value)
            codegen_continue()
        )
        rules(
            unary_instructions,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            CLOSE_BRACK
        )
    )
    terminal(scaled_instruction
        semantic_default()
        codegen(
            run(fileprint_scaled_instruction, var_1->instruction, var_1->group, var_2->size, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value, atoi(var_8->token->value))
            codegen_continue()
        )
        rules(
            unary_instructions,
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
    terminal(complex_instruction
        semantic_default()
        codegen(
            run(fileprint_complex_instruction, var_1->instruction, var_1->group, var_2->size, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value, atoi(var_8->token->value), atoi(var_10->token->value)*var_9->val)
            codegen_continue()
        )
        rules(
            unary_instructions,
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
    terminal(offset_instruction
        semantic_default()
        codegen(
            run(fileprint_offset_instruction, var_1->instruction, var_1->group, var_2->size, var_4->reg_size, var_4->reg_value, atoi(var_6->token->value)*var_5->val)
            codegen_continue()
        )
        rules(
            unary_instructions,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK
        )
    )
#pragma endregion
#pragma region Push_Pop
    terminal(pp_r_instruction
        semantic_default()
        codegen(
            run(fileprint_pp_r_instruction, var_1->instruction, var_1->group, var_2->reg_size, var_2->reg_value)
            codegen_continue()
        )
        rules(
            Push_Pop_Instructions,
            Register
        )
    )
    terminal(pp_indirect_instruction
        semantic_default()
        codegen(
            run(fileprint_pp_indirect_instruction, var_1->instruction, var_1->group, var_2->size, var_4->reg_size, var_4->reg_value)
            codegen_continue()
        )
        rules(
            Push_Pop_Instructions,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK
        )
    )
    terminal(pp_index_instruction
        semantic_default()
        codegen(
            run(fileprint_pp_indexed_instruction, var_1->instruction, var_1->group, var_2->size, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value)
            codegen_continue()
        )
        rules(
            Push_Pop_Instructions,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            CLOSE_BRACK
        )
    )
    terminal(pp_scaled_instruction
        semantic_default()
        codegen(
            run(fileprint_pp_scaled_instruction, var_1->instruction, var_1->group, var_2->size, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value, atoi(var_8->token->value))
            codegen_continue()
        )
        rules(
            Push_Pop_Instructions,
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
    terminal(pp_complex_instruction
        semantic_default()
        codegen(
            run(fileprint_pp_complex_instruction, var_1->instruction, var_1->group, var_2->size, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value, atoi(var_8->token->value), atoi(var_10->token->value)*var_9->val)
            codegen_continue()
        )
        rules(
            Push_Pop_Instructions,
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
    terminal(pp_offset_instruction
        semantic_default()
        codegen(
            run(fileprint_pp_offset_instruction, var_1->instruction, var_1->group, var_2->size, var_4->reg_size, var_4->reg_value, atoi(var_6->token->value)*var_5->val)
            codegen_continue()
        )
        rules(
            Push_Pop_Instructions,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK
        )
    )
#pragma endregion
#pragma region bit_operation
    terminal(bitwise_hex_r_instruction
        semantic_default()
        codegen(
            run(fileprint_r_instruction, var_1->instruction, 0xC1, var_2->reg_size, var_2->reg_value)
            run(hexStringToByteArray, var_3->token->value, 1)
            codegen_continue()
        )
        rules(
            Bitwise_Instruction,
            Register,
            HEX_LITERAL
        )
    )
    terminal(bitwise_hex_indirect_instruction
        semantic_default()
        codegen(
            run(fileprint_indirect_instruction, var_1->instruction, 0xC1, var_2->size, var_4->reg_size, var_4->reg_value)
            run(hexStringToByteArray, var_6->token->value, 1)
            codegen_continue()
        )
        rules(
            Bitwise_Instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK,
            HEX_LITERAL
        )
    )
    terminal(bitwise_hex_index_instruction
        semantic_default()
        codegen(
            run(fileprint_indexed_instruction, var_1->instruction, 0xC1, var_2->size, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value)
            run(hexStringToByteArray, var_8->token->value, 1)
            codegen_continue()
        )
        rules(
            Bitwise_Instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            CLOSE_BRACK,
            HEX_LITERAL
        )
    )
    terminal(bitwise_hex_scaled_instruction
        semantic_default()
        codegen(
            run(fileprint_scaled_instruction, var_1->instruction, 0xC1, var_2->size, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value, atoi(var_8->token->value))
            run(hexStringToByteArray, var_10->token->value, 1)
            codegen_continue()
        )
        rules(
            Bitwise_Instruction,
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
    terminal(bitwise_hex_complex_instruction
        semantic_default()
        codegen(
            run(fileprint_complex_instruction, var_1->instruction, 0xC1, var_2->size, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value, atoi(var_8->token->value), atoi(var_10->token->value)*var_9->val)
            run(hexStringToByteArray, var_12->token->value, 1)
            codegen_continue()
        )
        rules(
            Bitwise_Instruction,
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
    terminal(bitwise_hex_offset_instruction
        semantic_default()
        codegen(
            run(fileprint_offset_instruction, var_1->instruction, 0xC1, var_2->size, var_4->reg_size, var_4->reg_value, atoi(var_6->token->value)*var_5->val)
            run(hexStringToByteArray, var_8->token->value, 1)
            codegen_continue()
        )
        rules(
            Bitwise_Instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK,
            HEX_LITERAL
        )
    )
#pragma endregion
#pragma region bitwise_cl
    terminal(bitwise_cl_r_instruction
        semantic_default()
        codegen(
            run(fileprint_r_instruction, var_1->instruction, 0xD3, var_2->reg_size, var_2->reg_value)
            codegen_continue()
        )
        rules(
            Bitwise_Instruction,
            Register,
            CL
        )
    )
    terminal(bitwise_cl_indirect_instruction
        semantic_default()
        codegen(
            run(fileprint_indirect_instruction, var_1->instruction, 0xD3, var_2->size, var_4->reg_size, var_4->reg_value)
            codegen_continue()
        )
        rules(
            Bitwise_Instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            CLOSE_BRACK,
            CL
        )
    )
    terminal(bitwise_cl_index_instruction
        semantic_default()
        codegen(
            run(fileprint_indexed_instruction, var_1->instruction, 0xD3, var_2->size, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value)
            codegen_continue()
        )
        rules(
            Bitwise_Instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            PLUS,
            Register,
            CLOSE_BRACK,
            CL
        )
    )
    terminal(bitwise_cl_scaled_instruction
        semantic_default()
        codegen(
            run(fileprint_scaled_instruction, var_1->instruction, 0xD3, var_2->size, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value, atoi(var_8->token->value))
            codegen_continue()
        )
        rules(
            Bitwise_Instruction,
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
    terminal(bitwise_cl_complex_instruction
        semantic_default()
        codegen(
            run(fileprint_complex_instruction, var_1->instruction, 0xD3, var_2->size, var_4->reg_size, var_4->reg_value, var_6->reg_size, var_6->reg_value, atoi(var_8->token->value), atoi(var_10->token->value)*var_9->val)
            codegen_continue()
        )
        rules(
            Bitwise_Instruction,
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
    terminal(bitwise_cl_offset_instruction
        semantic_default()
        codegen(
            run(fileprint_offset_instruction, var_1->instruction, 0xD3, var_2->size, var_4->reg_size, var_4->reg_value, atoi(var_6->token->value)*var_5->val)
            codegen_continue()
        )
        rules(
            Bitwise_Instruction,
            Size_Specifier,
            OPEN_BRACK,
            Register,
            Plus_Minus,
            NUMBER_LITERAL,
            CLOSE_BRACK,
            CL
        )
    )
)





