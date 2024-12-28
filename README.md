  Compiler Builder Docs  

    ## Installation

  To integrate the Macro-Based Compiler Builder into your project:

  1. Clone this repository:
    git clone https://github.com/HnsorensSoftware/MacroCompilerBuilder
    cd macro-compiler-builder

  2. To Compile, run:
     HASM ASM_file Output


*   [Overview](#Overview)
*   [Immediate](#Immediate)
*   [Registers](#Registers)
*   [Memory](#Memory)
*   Data Movement
    
    *   [MOV Instruction](#MOV)
    *   [PUSH Instruction](#PUSH)
    *   [POP Instruction](#POP)
    *   [LEA Instruction](#LEA)
    *   [XCHG Instruction](#XCHG)
    
*   Arithmetic Operations
    
    *   [ADD Instruction](#ADD)
    *   [SUB Instruction](#SUB)
    *   [MUL Instruction](#MUL)
    *   [DIV Instruction](#DIV)
    *   [IMUL Instruction](#IMUL)
    *   [IDIV Instruction](#IDIV)
    *   [ADC Instruction](#ADC)
    *   [SBB Instruction](#SBB)
    *   [NEG Instruction](#NEG)
    *   [INC Instruction](#INC)
    *   [DEC Instruction](#DEC)
    
*   Logical and Bitwise Operations
    
    *   [AND Instruction](#AND)
    *   [OR Instruction](#OR)
    *   [XOR Instruction](#XOR)
    *   [NOT Instruction](#NOT)
    *   [TEST Instruction](#TEST)
    
*   Comparison and Jumps
    
    *   [CMP Instruction](#CMP)
    *   [JO Instruction](#JO)
    *   [JNO Instruction](#JNO)
    *   [JBE Instruction](#JBE)
    *   [JB Instruction](#JB)
    *   [JAE Instruction](#JAE)
    *   [JNE Instruction](#JNE)
    *   [JE Instruction](#JE)
    *   [JA Instruction](#JA)
    *   [JS Instruction](#JS)
    *   [JNS Instruction](#JNS)
    *   [JP Instruction](#JP)
    *   [JNP Instruction](#JNP)
    *   [JLE Instruction](#JLE)
    *   [JL Instruction](#JL)
    *   [JGE Instruction](#JGE)
    *   [JG Instruction](#JG)
    
*   Control Flow
    
    *   [JMP Instruction](#JMP)
    *   [CALL Instruction](#CALL)
    *   [RET Instruction](#RET)
    *   [WAIT Instruction](#WAIT)
    *   [SYSCALL Instruction](#SYSCALL)
    
*   Interrupts and System
    
    *   [INT Instruction](#INT)
    
*   Miscellaneous Operations
    
    *   [NOP Instruction](#NOT)
    

HASM Documentation
==================

Overview
--------

This documentation provides a detailed overview of an assembly language. It explains the core concepts, registers, memory access patterns, and the instructions available for writing assembly programs. The focus is on 32-bit and 64-bit architectures.

Immediate Values
----------------

Immediate values are constant values directly embedded in an instruction. They can be represented in the following formats:

*   **Hexadecimal:** Prefixed with `0x`, e.g., `0x1A`
*   **Decimal:** A standard integer, e.g., `26`
*   **Binary:** Prefixed with `0b`, e.g., `0b11010`

Registers
---------

Registers are small storage locations within the CPU. They are used for quick access to data and instructions. The registers are categorized as either 32-bit, 64-bit, 16-bit, or 8-bit based on the CPU architecture.

### 32-bit Registers

ECX

Counter

EDX

Data Register

ESI

Source Index

EDI

Destination Index

ESP

Stack Pointer

EBP

Base Pointer

### 64-bit Registers

Register

Purpose

### 16-bit Registers

Register

Purpose

AX

Accumulator

BX

Base Register

CX

Counter

DX

Data Register

SI

Source Index

DI

Destination Index

SP

Stack Pointer

BP

Base Pointer

### 8-bit Registers

Register

Purpose

AL

Lower 8 bits of AX

AH

Higher 8 bits of AX

BL

Lower 8 bits of BX

BH

Higher 8 bits of BX

CL

Lower 8 bits of CX

CH

Higher 8 bits of CX

DL

Lower 8 bits of DX

DH

Higher 8 bits of DX

Memory
------

Memory in assembly language refers to the system's main memory (RAM) and is accessed through specific patterns. The following are common memory access patterns:

*   `[address]`: Direct access to the memory at `address`
*   `[base + offset]`: Access memory at `base` plus an offset
*   `[base + index * scale]`: Access memory at `base` plus the product of `index` and `scale`
*   `[base + index * scale + offset]`: Combination of base, index, scale, and offset

The registers for the `base` and `index` must be the same. Either 32 bit or 64 bit.

Memory access size depends on the instruction and can vary between 8-bit, 16-bit, 32-bit, or 64-bit operations using the following keywords:

*   `BYTE`: represents an 8 bit memory size
*   `WORD`: represents an 16 bit memory size
*   `DWORD`: represents an 32 bit memory size
*   `QWORD`: represents an 64 bit memory size

So memory is represented as the following:

    BYTE [...]
    

Data Movement and Stack Operations
==================================

### MOV Instruction (Move)

The MOV instruction copies the value of the source operand to the destination operand. This is the most commonly used instruction for transferring data. The syntax is:

    MOV destination, source

The `destination` operand is updated with the value from the `source` operand. Operands can be:

*   A register and another register
*   A register and a memory location
*   A register and an immediate value

Example:

    MOV RAX, RBX         ; Copy value of RBX to RAX
    MOV RCX, [memory]    ; Load value from memory into RCX
    MOV RDX, 42          ; Load immediate value into RDX

The MOV instruction does not modify flags and cannot be used to transfer data between two memory locations.

### PUSH Instruction (Push onto Stack)

The PUSH instruction pushes a value onto the stack, adjusting the stack pointer (SP or RSP) accordingly. The syntax is:

    PUSH operand

Where the `operand` is any 16 byte or 64 byte register or any Word or Qword memory.

Example:

    PUSH RAX ; Push RAX onto the stack

PUSH decrements the stack pointer and stores the value of the operand at the new memory location. It can be used to save registers or pass arguments to functions.

### POP Instruction (Pop from Stack)

The POP instruction pops a value from the stack into the specified register, adjusting the stack pointer. The syntax is:

    POP operand

Where the `operand` is any 16 byte or 64 byte register or any Word or Qword memory.

Example:

    POP RAX ; Pop a value from the stack into RAX

POP increments the stack pointer and loads the value into the specified operand, typically a register.

### LEA Instruction (Load Effective Address)

The LEA (Load Effective Address) instruction calculates the effective address of a memory operand and stores it in a register. It does not access the memory; it simply computes the address. The syntax is:

    LEA destination source

The `destination` operand is updated with the memory address calculated and stores it in a register. The `source` operand is any memory location.

Example:

    LEA RAX, [RBX + RCX*4 + 8] ; Calculate address and store in RAX

LEA is commonly used for pointer arithmetic and array indexing. It is also useful for performing complex arithmetic operations without modifying flags. Note that LEA requires a register as the destination operand; it cannot directly store the result in memory.

### XCHG Instruction (Exchange)

The XCHG (Exchange) instruction swaps the values of two operands. One operand must always be a register. The syntax is:

    XCHG operand1, operand2

Operands can be:

*   Two registers
*   A register and a memory location (but not two memory locations)

Example:

    XCHG RAX, RBX ; Swap values of RAX and RBX

If one operand is in memory, the instruction is atomic, which is useful in multi-threaded environments. Note that XCHG cannot operate on mismatched operand sizes (e.g., 8-bit and 16-bit).

Arithmetic Operations
=====================

### ADD Instruction (Add)

The ADD instruction adds the source operand to the destination operand. The result is stored in the destination operand. The syntax is:

    ADD destination, source

The `destination` operand is updated with the value from the `source` operand. Operands can be:

*   A register and another register
*   A register and a memory location
*   A register and an immediate value

Example:

    ADD RAX, RBX ; RAX = RAX + RBX

ADD updates the flags based on the result of the addition (carry flag, overflow flag, zero flag, etc.).

### SUB Instruction (Subtract)

The SUB instruction subtracts the source operand from the destination operand. The result is stored in the destination operand. The syntax is:

    SUB destination, source

The `destination` operand is updated with the value from the `source` operand. Operands can be:

*   A register and another register
*   A register and a memory location
*   A register and an immediate value

Example:

    SUB RAX, RBX ; RAX = RAX - RBX

SUB updates the flags based on the result of the subtraction (carry flag, overflow flag, zero flag, etc.).

### MUL Instruction (Multiply)

The MUL instruction performs unsigned multiplication of the accumulator (AX, EAX, or RAX) with the specified operand. The result is stored in a pair of registers (DX:AX, EDX:EAX, or RDX:RAX). The syntax is:

    MUL multiplier

Example:

    MOV RAX, 5
    MOV RBX, 10
    MUL RBX      ; RAX = RAX * RBX, RDX = high-order bits of result

The result of the multiplication is stored in RDX (high-order) and RAX (low-order). The flags are not modified by this instruction.

### DIV Instruction (Divide)

The DIV instruction performs unsigned division on the accumulator (AX, EAX, or RAX) and the specified operand. It stores the quotient in the destination register and the remainder in the register specified by the instruction. The syntax is:

    DIV divisor

Example:

    MOV RAX, 100
    MOV RBX, 4
    DIV RBX      ; RAX = quotient, RDX = remainder

The result of the division is stored in RAX (quotient) and RDX (remainder). If the divisor is zero, a divide-by-zero exception occurs.

### IMUL Instruction (Signed Multiply)

The IMUL instruction performs signed multiplication, storing the result in the destination register. The syntax is:

    IMUL destination, source

Example:

    IMUL RAX, RBX ; Signed multiply RAX by RBX

The result of the multiplication is stored in RAX (low-order) and RDX (high-order).

### IDIV Instruction (Signed Divide)

The IDIV instruction performs signed division on the accumulator (AX, EAX, or RAX) and the specified divisor. The result is stored in the destination register and the remainder in the register specified by the instruction. The syntax is:

    IDIV divisor

Example:

    MOV RAX, -100
    MOV RBX, 4
    IDIV RBX      ; RAX = quotient, RDX = remainder

The result is stored in RAX (quotient) and RDX (remainder), with proper sign handling for signed division.

### ADC Instruction (Add with Carry)

The ADC (Add with Carry) instruction performs an addition operation on two operands while including the current value of the carry flag (CF). This is particularly useful for multi-word arithmetic, such as operations involving large integers that span multiple registers. The syntax for ADC is as follows:

    ADC destination source

The `destination` operand is modified to store the result of the addition, while the `source` operand is added to it along with the carry flag. The operands can be:

*   A register and another register
*   A register and a memory location
*   A register and an immediate value

Example:

    MOV RAX, 0xFFFFFFFFFFFFFFFF ; Load maximum 64-bit value into RAX
    MOV RBX, 1                  ; Load 1 into RBX
    ADD RAX, RBX                ; Perform addition (overflow sets CF)
    ADC RCX, 0                  ; Add with carry to RCX

This instruction is essential for handling overflow conditions in arithmetic operations. However, it requires careful management of the carry flag to ensure correctness. Attempting to use mismatched operand sizes (e.g., mixing 8-bit and 32-bit operands) will result in an error.

### SBB Instruction (Subtract with Borrow)

The SBB (Subtract with Borrow) instruction is used to subtract one operand from another, including the current value of the carry flag (CF). This makes it the counterpart to ADC and is often used in multi-word subtraction operations. The syntax is:

    SBB destination source

The `destination` operand is updated with the result of the subtraction, which includes the carry flag. Operands can be:

*   A register and another register
*   A register and a memory location
*   A register and an immediate value

Example:

    MOV RAX, 0x10000000000000000 ; Load a large value into RAX
    MOV RBX, 1                   ; Load 1 into RBX
    SUB RAX, RBX                 ; Perform subtraction
    SBB RCX, 0                   ; Subtract with borrow from RCX

Use cases include high-precision arithmetic and cryptographic algorithms. Like ADC, operand sizes must match; otherwise, an error will occur.

### NEG Instruction (Negate)

The NEG instruction negates the value of the operand (changes the sign). The syntax is:

    NEG operand

Example:

    NEG RAX ; Negate RAX

NEG updates the flags, including the overflow flag if the result is too large to fit in the operand's size.

### INC Instruction (Increment)

The INC instruction adds 1 to the operand. It is commonly used in loops. The syntax is:

    INC operand

Example:

    INC RAX ; Increment RAX by 1

INC updates the flags based on the result, including the zero flag and sign flag.

### DEC Instruction (Decrement)

The DEC instruction subtracts 1 from the operand. It is commonly used in loops. The syntax is:

    DEC operand

Example:

    DEC RAX ; Decrement RAX by 1

DEC updates the flags based on the result, including the zero flag and sign flag.

Logical and Bitwise Operations
==============================

### AND Instruction (Logical AND)

The AND instruction performs a bitwise logical AND operation between the operands. The result is stored in the destination operand. The syntax is:

    AND destination, source

The `destination` operand is updated with the value from the `source` operand. Operands can be:

*   A register and another register
*   A register and a memory location
*   A register and an immediate value

Example:

    AND RAX, RBX ; RAX = RAX & RBX

AND updates the flags, including the zero flag if the result is zero.

### OR Instruction (Logical OR)

The OR instruction performs a bitwise logical OR operation between the operands. The result is stored in the destination operand. The syntax is:

    OR destination, source

The `destination` operand is updated with the value from the `source` operand. Operands can be:

*   A register and another register
*   A register and a memory location
*   A register and an immediate value

Example:

    OR RAX, RBX ; RAX = RAX | RBX

OR updates the flags, including the zero flag if the result is zero.

### XOR Instruction (Logical XOR)

The XOR instruction performs a bitwise exclusive OR operation between the operands. The result is stored in the destination operand. The syntax is:

    XOR destination, source

The `destination` operand is updated with the value from the `source` operand. Operands can be:

*   A register and another register
*   A register and a memory location
*   A register and an immediate value

Example:

    XOR RAX, RBX ; RAX = RAX ^ RBX

XOR updates the flags, including the zero flag if the result is zero.

### NOT Instruction (Logical NOT)

The NOT instruction performs a bitwise logical NOT operation, inverting each bit of the operand. The syntax is:

    NOT operand

Example:

    NOT RAX ; Invert the bits of RAX

NOT updates the flags, particularly the zero flag if the result is zero.

### TEST Instruction (Test)

The TEST instruction performs a bitwise AND operation between two operands and updates the processor flags based on the result, without storing the result. The syntax is:

Operands must be the same size and can include:

*   Two registers
*   A register and a memory location
*   A register and an immediate value

Example:

    TEST RAX, RAX
    JZ ZeroDetected ; Jump if zero flag is set

TEST is efficient for checking specific bits or conditions without modifying the original operands. Ensure operand sizes match to avoid errors.

Comparison and Jumps
====================

### CMP Instruction (Compare)

The CMP instruction subtracts the source operand from the destination operand but does not store the result. It only affects the flags. The syntax is:

    CMP destination, source

The `destination` operand is updated with the value from the `source` operand. Operands can be:

*   A register and another register
*   A register and a memory location
*   A register and an immediate value

Example:

    CMP RAX, RBX ; Compare RAX and RBX

CMP updates the flags based on the result of the subtraction (zero flag, carry flag, overflow flag, etc.), but does not modify any registers.

### JO Instruction (Jump if Overflow)

The JO instruction transfers control to a specified address if the overflow flag (OF) is set, indicating an arithmetic overflow. The syntax is:

    JO target

Example:

    ADD RAX, RBX
    JO OverflowDetected

This instruction is crucial for overflow detection and error handling in arithmetic operations.

### JNO Instruction (Jump if No Overflow)

JNO performs the opposite of JO, jumping if the overflow flag is clear. The syntax is:

    JNO target

Example:

    ADD RAX RBX
    JNO NoOverflow

JNO is useful for confirming successful arithmetic operations without overflow.

### JBE (Jump if Below or Equal)

The JBE instruction jumps to the specified address if the carry flag (CF) is set or the zero flag (ZF) is set, indicating the first operand is less than or equal to the second. The syntax is:

    JBE target

Example:

    CMP RAX, RBX
    JBE BelowOrEqual

### JB Instruction (Jump if Below)

JB jumps if the carry flag (CF) is set, indicating an unsigned comparison where the first operand is less than the second. The syntax is:

    JB target

Example:

    CMP RAX RBX
    JB BELOW

### JAE Instruction (Jump if Above or Equal)

JAE jumps if the carry flag (CF) is clear, indicating the first operand is greater than or equal to the second in an unsigned comparison. The syntax is:

    JAE target

Example:

    CMP RAX RBX
    JAE AboveOrEqual

### JNE Instruction (Jump if Not Equal)

The JNE instruction performs a conditional jump if the operands are not equal. It checks the zero flag. The syntax is:

    JNE label

Example:

    JNE label ; Jump if not equal

The jump occurs if the zero flag is not set (indicating that the operands are not equal).

### JE Instruction (Jump If Equal)

JE jumps to the target address if the zero flag (ZF) is set, indicating equality. The syntax is:

    JE target

Example:

    CMP RAX RBX
    JE Equal

### JA Instruction (Jump if Above)

The JA instruction performs a conditional jump if the first operand is greater than the second operand. It checks the carry flag and zero flag. The syntax is:

    JA label

Example:

    JA label ; Jump if above

The jump occurs if the carry flag is clear and the zero flag is clear (indicating greater than).

### JS Instruction (Jump if Sign)

The JS instruction performs a conditional jump if the sign flag is set (indicating a negative result). The syntax is:

    JS label

Example:

    JS label ; Jump if sign flag is set

The jump occurs if the sign flag is set, indicating that the last result was negative.

### JNS Instruction (Jump if Not Sign)

The JNS instruction performs a conditional jump if the sign flag is not set (indicating a non-negative result). The syntax is:

    JNS label

Example:

    JNS label ; Jump if not sign flag is set

The jump occurs if the sign flag is clear, indicating that the last result was non-negative.

### JP Instruction (Jump if Parity)

The JP instruction performs a conditional jump if the parity flag is set (indicating even parity). The syntax is:

    JP label

Example:

    JP label ; Jump if parity flag is set

The jump occurs if the parity flag is set, indicating even parity in the result.

### JNP Instruction (Jump if No Parity)

The JNP instruction performs a conditional jump if the parity flag is not set (indicating odd parity). The syntax is:

    JNP label

Example:

    JNP label ; Jump if no parity flag is set

The jump occurs if the parity flag is clear, indicating odd parity in the result.

### JLE Instruction (Jump if Less or Equal)

The JLE instruction performs a conditional jump if the first operand is less than or equal to the second operand. It checks the zero flag and the sign flag. The syntax is:

    JLE label

Example:

    JLE label ; Jump if less or equal

The jump occurs if the zero flag is set or the sign flag is set (indicating less than or equal).

### JL Instruction (Jump if Less)

The JL instruction performs a conditional jump if the first operand is less than the second operand. It checks the sign flag. The syntax is:

    JL label

Example:

    JL label ; Jump if less

The jump occurs if the sign flag is set (indicating less than).

### JGE Instruction (Jump if Greater or Equal)

The JGE instruction performs a conditional jump if the first operand is greater than or equal to the second operand. It checks the sign flag. The syntax is:

    JGE label

Example:

    JGE label ; Jump if greater or equal

The jump occurs if the sign flag is clear (indicating greater than or equal).

### JG Instruction (Jump if Greater)

The JG instruction performs a conditional jump if the first operand is greater than the second operand. It checks the zero flag and sign flag. The syntax is:

    JG label

Example:

    JG label ; Jump if greater

The jump occurs if the zero flag is clear and the sign flag is clear (indicating greater than).

Control Flow
============

### JMP Instruction (Jump)

The JMP instruction performs an unconditional transfer of control to a specified address. It is fundamental for loops, branches, and skips. The syntax is:

    JMP target

The `target` can be:

*   A label (direct jump)
*   A memory location or register containing the target address (indirect jump)

Example:

    JMP Label
    Label:
        NOP ; Execution resumes here

JMP is versatile but must be used carefully to avoid creating spaghetti code. Ensure that jumps do not result in infinite loops or unreachable code.

### Call Instruction (Call Procedure)

The CALL instruction transfers control to a procedure (subroutine) while saving the return address on the stack. This enables structured programming and modular design. The syntax is:

    CALL target

The `target` can be a:

*   Label (direct call)
*   Register containing the target address (indirect call)

    CALL MyFunction ; Jump to MyFunction and save return address

Upon executing a CALL, the instruction pointer (RIP) is pushed onto the stack. Returning from the procedure requires a corresponding RET instruction. Mismatched stack operations can result in crashes or undefined behavior.

### RET Instruction (Return)

The RET instruction returns control from a procedure by popping the return address from the stack into the instruction pointer (RIP). The syntax is:

    RET

Example:

    RET ; Return from function call

RET is often used to return control to the caller after a CALL instruction. Optionally, it can also pop arguments from the stack by using the `RET n` form.

### WAIT Instruction (Wait for Interrupt)

The WAIT instruction causes the processor to wait for an interrupt, typically used in legacy systems. It is a no-operation instruction for the processor, allowing it to halt until an interrupt occurs. The syntax is:

    WAIT

Example:

    WAIT ; Wait for an interrupt

WAIT is often used in systems that use interrupt-driven processing and can be used for synchronization.

### SYSCALL Instruction (System Call)

SYSCALL is used to transition from user mode to kernel mode, invoking a system call. It is the preferred mechanism for requesting services from the operating system in x64 architecture. The syntax is:

    SYSCALL

Example:

    MOV RAX, 60 ; System call number for exit
    MOV RDI, 0  ; Exit code
    SYSCALL

SYSCALL is efficient but requires knowledge of the system call interface, including call numbers and register usage. Misusing it can lead to crashes or security vulnerabilities.

Interrupts and Systems
======================

### INT Instruction (Interrupt)

The INT instruction generates a software interrupt, transferring control to the interrupt handler. The syntax is:

    INT interrupt_number

Example:

    INT 0x80 ; Call interrupt 0x80, commonly used in Linux system calls

The INT instruction is used to invoke a software interrupt, often used for system calls or invoking operating system routines.

Miscellaneous Operations
========================

### NOP Instruction (No Operation)

The NOP instruction performs no operation and is used to create a delay or padding in the code. The syntax is:

    NOP

Example:

    NOP ; No operation, do nothing

NOP does not modify any registers, memory, or flags and is typically used for debugging or aligning code.