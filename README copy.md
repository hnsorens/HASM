  
  
  # Macro-Based Compiler Builder

  ## Installation

  To integrate the Macro-Based Compiler Builder into your project:

  1. Clone this repository:
    ``bash
    git clone https://github.com/HnsorensSoftware/MacroCompilerBuilder
    cd macro-compiler-builder

  2. Include the provided Header file into your C project
  
  
  Compiler Builder Docs  

*   [Overview](#Overview)
*   [COMPILER Macro Definition](#COMPILERMacroDefinition)
*   [createCompiler](#createCompilerMacro)
*   [Tokens Macro](#TokensMacro)
*   [IgnoreTokens Macro](#ignoreTokensMacro)
*   [AST Nodes](#NodeMacro)
*   [Iteration](#IterationSteps)
*   [any\_rule Implementation](#any_rule)
*   [all\_rule Implementation](#all_rule)
*   [Iteration Functions](#IterationFunctions)
*   [Semantic Iteration](#SemanticIteration)
*   [Code Generation Iteration](#CodeGenerationIteration)
*   [Copmiler Function Call](#Compiling)
*   [Extending and Customizing the Compiler](#Extending)
*   [Conclusion](#Conclusion)

Macro-Based Compiler Builder Documentation
==========================================

Overview
--------

This document provides a detailed explanation of the macro-based compiler builder written in C, a tool designed to aid in building compilers using a flexible and modular macro system. This approach allows the user to define the components of a compiler — such as tokens, Abstract Syntax Tree (AST) nodes, parsing rules, and iteration steps — in a highly customizable and extensible manner. By leveraging macros, this tool simplifies the process of building a compiler by allowing for dynamic definition and processing of language rules, tokens, and transformations.

The compiler builder works by defining the compiler components in a header file using macros. The macros specify how the source code is tokenized, how the Abstract Syntax Tree (AST) is built, and how various compiler passes (such as semantic analysis and code generation) are handled.

This documentation will provide a deep dive into the usage, capabilities, and inner workings of the macro system used to define a compiler. Code examples are included to demonstrate the different features and how they are combined to create a working compiler.

Macro-Based Compiler Builder Structure
======================================

COMPILER Macro Definition
-------------------------

The **COMPILER** macro is the entry point for defining a compiler. This macro assigns a name to the compiler, which is later used throughout the system. The macro establishes the context for all the tokens, rules, and iteration steps that are defined later.

    
    #define COMPILER MY_COMPILER
                    

This line of code sets `MY_COMPILER` as the name of the compiler. The name `MY_COMPILER` is used to generate the necessary structures and functions for the specific copmiler.

createCompiler
--------------

The **createCompiler** macro generates the header file for the compiler, which includes definitions for the tokens, AST node types, and iteration steps. This macro groups together several other macros, including tokens, ignoreTokens, node, and iterationStep, among others.

    
    #define COMPILER MY_COMPILER
    createCompiler(
        ...
    )
                    

Tokens Macro
------------

The **tokens** macro is used to define all the lexical tokens that the compiler will recognize. Each token consists of a name (such as `PLUS`, `MINUS`, `IDENTIFIER`) and a regular expression pattern that matches it. Here is an example:

    
    #define COMPILER MY_COMPILER
    createCompiler(
        tokens(
            token(PLUS, "^\\+")       // Matches the '+' symbol
            token(MINUS, "^\\-")      // Matches the '-' symbol
            token(IDENTIFIER, "^[a-zA-Z_][a-zA-Z0-9_]*") // Matches variable names
        )
    )
                    

`token(PLUS, "^\\+")` matches the plus symbol (`+`) in the source code.

`token(MINUS, "^\\-")` matches the minus symbol (`-`).

`token(IDENTIFIER, "^[a-zA-Z_][a-zA-Z0-9_]*")` matches identifiers (variables or function names), following typical naming conventions (starting with a letter or underscore and followed by letters, numbers, or underscores).

IgnoreTokens Macro
------------------

The **ignoreTokens** macro allows you to specify which tokens should be ignored during parsing. These are usually whitespace or comments that don't affect the program’s semantics but are needed for syntax correctness.

    
    createCompiler(
        ignoreTokens(
            WHITESPACE,
            COMMENT
        )
    ) 
                    

This example instructs the compiler to ignore tokens representing whitespace and comments during parsing, meaning that these tokens will not appear in the resulting AST.

AST Nodes
=========

The **node** macro is used to define the structure of an AST node. Every AST node is associated with a parsing rule. Rules can either be `any_rule` or `all_rule`:

**any\_rule**: Matches any one of the specified rules.

**all\_rule**: Matches all of the specified rules in assending order.

Each rule can include tokens or other AST nodes. The node also defines variables (via the `var` macro), which store information to be used later in the iteration steps.

    
    createCompiler(
        node(Expr
            any_rule(PLUS, MINUS)
            var(int, value, 0)   // Variable `value` to hold the result
        )
    )   
                    

In this example the `Expr` node matches either the `PLUS` or `MINUS` token (via the `any_rule`) and has a variable `value` to store some result (innitialized to 0).

    
    createCompiler(
        node(Statement
            all_rule(IDENTIFIER, PLUS)
            var(int, count, 0)
        )
    )
                    

The `Statement` node uses `all_rule`, meaning it expects both an `IDENTIFIER` and a `PLUS` token to form a valid statement. The node also defines a variables `count` to track the number of times this rules is applied.

Iteration Steps
---------------

Iteration steps are macros used to define the actions performed at various stages of compilation, such as parsing, semantic analysis, and code generation. These steps are executed sequentially after parsing is completed. Each iteration step is defined using the **iterationStep** macro.

This example sets up two iteration steps:

**semantics**: Responsible for checking the program's semantics (e.g., type checking, variable scoping).

**codegen**: Responsible for generating the target code (e.g., assembly or machine code).

AST Node Definitions
====================

Each AST node is defined using the **node** macro. Depending on whether the node uses `any_rule` or `all_rule`, the structure of the node will differ. Below are examples of both. It is important to note that the **Root** node will always be the beggining of the code compilation.

any\_rule Node
--------------

For a node that uses `any_rule`, the node structure includes a `var_index` field that identifies which rule is currently active. The rule options are stored in a union, as only one of them will be active at a time.

    
    node(Expr
        any_rule(PLUS, MINUS)
        var(int, value, 0)
    )
                    

Here's the general structure of the node:

    
    struct Expr {
        int var_index;   // The index of the rule used
        union {
            struct var_1;  // Structure for the PLUS rule
            struct var_2;  // Structure for the MINUS rule
        } var;
        int value;        // Variable to hold a result
    };
                    

For a node that uses `all_rule`, all of the specified rules are directly included in the structure, and no union is needed.

    
    node(Statement
        all_rule(IDENTIFIER, PLUS)
        var(int, count, 0)
    )
                    

Here's a general structure of the node:

    
    struct Statement {
        struct var_1;  // The structure for IDENTIFIER rule
        struct var_2;  // The structure for PLUS rule
        int count;      // Variable to track how often the rule is used
    };
                    

Iteration Functions
===================

Iteration functions are defined for each node and iteration step (e.g., semantics, code generation). The iteration functions take in the AST node and the output file (`FILE* file`) as parameters.

The **iteration** macro is used to define an iteration step function for a given node. The specify the node that the iteration function is being defined for, define **NODE** as the name of the node.

    
    #define NODE Root
                

When defining the iteration functions, it is important to include the `continue_it();` macro which continues the iteration recursive process.

Semantic Iteration
------------------

The semantic iteration is an example of an iteration step that can be put into place. During the **semantics** iteration, the compiler checks the program's semantic correctness, such as type checking or variable scoping. The iteration function may modify the AST or perform validation.

    
    #define NODE Expr
    iteration(semantics)
    {
        continue_it();
        if (var_0->var_index == 1) {  // PLUS rule
            var_0->value = 1;
        } else if (var_0->var_index == 2) {  // MINUS rule
            var_0->value = -1;
        }
    }
                    

In this example, the function checks which rule is being applied (using the `var_index`) and sets the `value` of the node accordingly. The `continue_it();` is called at the beggining so the child nodes are populated before any values are potentially taken from them. This is a good practice for semantics.

Code Generation Iteration
-------------------------

The code generation iteration step is another example of an iteration step. The `codegen` iteration is responsible for generating the target code based on the AST. This might involve translating AST nodes into assembly or intermediate code.

    
    #define NODE Statement
    iteration(codegen)
    {
        if (var_0->var_index == 1) {  // IDENTIFIER rule
            fprintf(file, "var_%d", var_0->var_1.identifier);
        }
        if (var_0->var_index == 2) {  // PLUS rule
            fprintf(file, " + ");
        }
        continue_it();
    }
                    

In this code generation iteration, the function writes to the output file based on the active rule. It generates a code snippet for an identifier or a plus sign (`+`), depending on which rule is applied. The `continue_it();` is after the code is written to file to keep the code in order. In some cases `continue_it();` may be in the center, when a node requires code to be written before and after its childeren nodes.

Compiling
=========

Compiler Function Call
----------------------

When your compiler is complete, there needs to be a way to actually compiler it. That is where the Compiler function comes in. The compiler function is used to compile your code. The parameters for the compiler function are the names of the input file and output file.

    
    #define COMPILER MyCompiler
    createCompiler(
        ...
    )
    
    int main()
    {
        compileMyCompiler("file_in.txt", "file_out.txt");
        return 0;
    }
                    

In this example, a compiler is created called **MyCompiler**. To compiler MyCompiler, we use the **compilerMyCompiler** function.

Extending and Customizing the Compiler
======================================

One of the key advantages of this macro-based compiler builder is its modularity. You can easily extend and customize the compiler by adding new tokens, rules, and iteration steps. For example:

    
    createCompiler(
        tokens(
            token(MULTIPLY, "^\\*"),
            token(DIVIDE, "^\\/")
        )
        node(MultExpr
            any_rule(MULTIPLY, DIVIDE)
            var(int, result, 0)
        )
        iterationStep(semantics)
        iterationStep(codegen)
    )
                    

In this example, we add new tokens (`MULTIPLY` and `DIVIDE`) and a new node (`MultExpr`) that can match either multiplication or division operations. The iteration steps for semantics and code generation are defined as before.

Conclusion
==========

The macro-based compiler builder in C provides a flexible and extensible way to define the components of a compiler. By using macros to define tokens, AST nodes, and iteration steps, it allows for rapid development and customization. The modularity of the system makes it easy to add new features, such as new tokens or compilation passes, and to modify existing ones as needed.

The use of macros, while somewhat complex at first, provides a powerful mechanism for building highly modular and configurable compilers that can be adapted to a wide range of programming languages and compiler strategies. By customizing each component (tokenization, parsing, semantics, and code generation), you can create a complete, functioning compiler that meets your needs.

© 2024 Macro-Based Compiler Builder Documentation