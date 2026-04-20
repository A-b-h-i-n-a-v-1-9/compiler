# Mini Expression Compiler

A recursive descent compiler written in C++17 from scratch — no libraries, no shortcuts.
Built to demonstrate core compiler engineering concepts relevant to systems programming.

## What it does

Implements a full compiler pipeline for a simple expression language:

- **Lexer** — tokenizes raw input into numbers, identifiers, and operators
- **Parser** — builds an Abstract Syntax Tree (AST) using recursive descent
- **Evaluator** — walks the AST to compute results and manage variable state

## Features

- Arithmetic with correct operator precedence: `+` `-` `*` `/`
- Parenthesised expressions: `(3 + 4) * 2`
- Variable assignment and reuse: `x = 10`, `x + 5`
- Error handling: division by zero, undefined variables, unknown tokens

## Build & Run

```bash
make
./compiler
```

Requires: `g++` with C++17 support.

## Example Session


2 + 3 * 4
=> 14
x = 10
=> 10
x + 5
=> 15
y = x * 2 + 1
=> 21
(3 + 4) * 2
=> 14
10 / 0
Error: division by zero
z
Error: undefined variable 'z'



## Project Structure
nvidia-compiler/
├── include/
│   ├── lexer.h       # Token types and tokenizer interface
│   ├── parser.h      # AST node definitions and parser interface
│   └── evaluator.h   # Evaluator class with variable store
├── src/
│   ├── lexer.cpp     # Tokenizer implementation
│   ├── parser.cpp    # Recursive descent parser
│   ├── evaluator.cpp # AST tree-walker and evaluator
│   └── main.cpp      # REPL entry point
└── Makefile

## Concepts Demonstrated

- Lexical analysis and tokenization
- Recursive descent parsing
- Abstract Syntax Tree (AST) construction
- Tree-walking interpretation
- Operator precedence and associativity
- Runtime error handling
