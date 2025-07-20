# HASM - x86 Assembly Compiler

A complete x86-64 assembler written in C that compiles assembly code directly to executable ELF64 binaries. HASM supports a comprehensive subset of x86 instructions and provides a clean, modern assembly syntax.

## Features

### 🚀 Core Capabilities
- **Direct ELF64 Generation**: Compiles assembly to native Linux executables
- **Complete Compiler Pipeline**: Lexical analysis, parsing, semantic analysis, and code generation
- **x86-64 Support**: Full 64-bit register set and addressing modes
- **Label Resolution**: Automatic jump target resolution and optimization
- **Variable Declarations**: Support for data sections with multiple data types

### 📝 Supported Instructions

#### Data Movement
- `MOV` - Move data between registers, memory, and immediate values

#### Arithmetic & Logic
- `ADD`, `SUB` - Addition and subtraction
- `ADC`, `SBB` - Addition/subtraction with carry/borrow
- `AND`, `OR`, `XOR` - Bitwise logical operations
- `NOT`, `NEG` - Bitwise NOT and negation
- `INC`, `DEC` - Increment and decrement

#### Multiplication & Division
- `MUL`, `IMUL` - Unsigned and signed multiplication
- `DIV`, `IDIV` - Unsigned and signed division

#### Comparison & Testing
- `CMP` - Compare operands
- `TEST` - Test bits (sets flags)

#### Control Flow
- `JMP` - Unconditional jump
- `JE`, `JNE` - Jump if equal/not equal
- `JA`, `JAE`, `JB`, `JBE` - Unsigned comparison jumps
- `JL`, `JLE`, `JG`, `JGE` - Signed comparison jumps
- `JO`, `JNO` - Jump if overflow/not overflow
- `JS`, `JNS` - Jump if sign/not sign
- `JP`, `JNP` - Jump if parity/not parity
- `CALL`, `RET` - Subroutine calls and returns

#### System & Stack
- `PUSH`, `POP` - Stack operations
- `SYSCALL` - System calls (Linux x86-64)
- `INT` - Software interrupts
- `NOP` - No operation
- `WAIT` - Wait for floating point operations

#### Address Calculation
- `LEA` - Load effective address

### 🏗️ Data Types & Variables

#### Supported Data Types
- `DB` - Define Byte (8-bit)
- `DW` - Define Word (16-bit)
- `DD` - Define Doubleword (32-bit)
- `DQ` - Define Quadword (64-bit)

#### Variable Features
- String literals: `"Hello, World!"`
- Character literals: `'A'`
- Numeric literals: `42`, `0x100`, `0b1010`
- Arrays: `DB 1, 2, 3, 4`
- Repetition: `TIMES 5 DB 0`

## Installation

### Prerequisites
- GCC compiler
- Linux system (for ELF64 output)
- Make

### Build Instructions
```bash
# Clone the repository
git clone <repository-url>
cd HASM

# Build the assembler
make

# Or build manually
gcc -Wall -Wextra -Werror -pedantic -g main.c assembler.c Instructions.c InstructionHandlers.c -o HASM
```

## Usage

### Basic Usage
```bash
# Compile a single assembly file
./HASM input.hasm

# Specify output file
./HASM input.hasm -o output

# Run tests
make test
```

### Assembly File Structure
```nasm
; Example HASM assembly program
SECTION DATA
    message: DB "Hello, World!", 10  ; String with newline
    count: DD 42                     ; 32-bit integer

SECTION TEXT
    GLOBAL BEGIN                     ; Entry point label
    
BEGIN:
    ; System call to write message
    MOV RAX, 1                      ; sys_write
    MOV RDI, 1                      ; stdout
    LEA RSI, [message]              ; message address
    MOV RDX, 14                     ; length
    SYSCALL                         ; Make system call
    
    ; System call to exit
    MOV RAX, 60                     ; sys_exit
    MOV RDI, 0                      ; exit code 0
    SYSCALL                         ; Make system call
```

### Supported Syntax

#### Registers
- **64-bit**: `RAX`, `RCX`, `RDX`, `RBX`, `RSP`, `RBP`, `RSI`, `RDI`, `R8`-`R15`
- **32-bit**: `EAX`, `ECX`, `EDX`, `EBX`, `ESP`, `EBP`, `ESI`, `EDI`
- **16-bit**: `AX`, `CX`, `DX`, `BX`, `SP`, `BP`, `SI`, `DI`
- **8-bit**: `AL`, `CL`, `DL`, `BL`, `AH`, `CH`, `DH`, `BH`

#### Addressing Modes
- Register: `MOV RAX, RBX`
- Immediate: `MOV RAX, 42`
- Memory: `MOV RAX, [RBX]`
- Memory with displacement: `MOV RAX, [RBX+8]`
- Memory with index: `MOV RAX, [RBX+RCX*2]`

#### Numbers
- Decimal: `42`
- Hexadecimal: `0x2A`
- Binary: `0b101010`

## Project Structure

```
HASM/
├── main.c                 # Main compiler pipeline
├── assembler.h           # Core data structures and declarations
├── assembler.c           # Vector implementation and instruction map
├── Instructions.h        # Instruction parsing utilities
├── Instructions.c        # Instruction parsing and encoding
├── InstructionHandlers.h # Instruction handler declarations
├── InstructionHandlers.c # Instruction handler implementations
├── elf.h                 # ELF64 format definitions
├── Makefile              # Build configuration
├── Examples/             # Sample assembly programs
│   └── HelloWorld/
│       └── HelloWorld.hasm
└── Tests/                # Test suite
    ├── Code/             # Test assembly files
    └── Bin/              # Expected binary outputs
```

## Compiler Architecture

### 1. Lexical Analysis (`lexical_analysis`)
- Tokenizes source code into keywords, symbols, numbers, and strings
- Handles comments (lines starting with `;`)
- Tracks line and column positions for error reporting

### 2. Syntax Analysis (`syntax_analysis`)
- Parses tokens into instruction structures
- Handles different assembly sections (DATA, TEXT, BSS)
- Processes labels, instructions, and variable declarations

### 3. Semantic Analysis (`semantic_analysis`)
- Resolves label references for jump instructions
- Optimizes jump instruction sizes (short vs long jumps)
- Validates instruction operands

### 4. Code Generation (`code_generation`)
- Generates ELF64 executable headers
- Encodes x86 instructions into machine code
- Writes binary output to file

## Testing

The project includes a comprehensive test suite covering all supported instructions:

```bash
# Run all tests
make test

# Individual test files are in Tests/Code/
# Expected outputs are in Tests/Bin/
```

## Examples

### Hello World
```nasm
SECTION DATA
    msg: DB "Hello, World!", 10

SECTION TEXT
    GLOBAL BEGIN
    
BEGIN:
    MOV RAX, 1          ; sys_write
    MOV RDI, 1          ; stdout
    LEA RSI, [msg]      ; message address
    MOV RDX, 14         ; length
    SYSCALL
    
    MOV RAX, 60         ; sys_exit
    MOV RDI, 0          ; exit code
    SYSCALL
```

### Simple Calculator
```nasm
SECTION DATA
    result: DD 0

SECTION TEXT
    GLOBAL BEGIN
    
BEGIN:
    MOV EAX, 10         ; Load first number
    ADD EAX, 20         ; Add second number
    MOV [result], EAX   ; Store result
    
    MOV RAX, 60         ; Exit
    MOV RDI, 0
    SYSCALL
```

## Error Handling

HASM provides detailed error messages with source location information:

```
program.asm:5:10: error: Invalid register name
  MOV RAX, INVALID_REG
          ^
note: Expected one of: Register, Immediate Value, Memory, Label
```

## Limitations

- Currently supports Linux x86-64 only
- Limited floating-point instruction support
- No macro system
- No conditional assembly directives
- No external symbol linking

## Acknowledgments

- ELF64 format specification
- x86-64 instruction set architecture
- Linux system call interface

---

**HASM** - An educational x86 assembler for learning and development.
