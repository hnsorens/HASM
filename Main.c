
// #include "Parser.h"
#include <stdlib.h>
#include <stdio.h>
#include "HASMGenerationPipeline.h"

int main(int argc, const char* argv[])
{
    CompileHASM(argv[1], argv[2]);
    return 0;
}