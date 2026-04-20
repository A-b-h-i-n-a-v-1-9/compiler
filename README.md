# Mini Expression Compiler with IR + Register Allocator

A full compiler pipeline built from scratch in C++17 — no libraries, no shortcuts.
Implements every stage from raw text to register-allocated pseudo-assembly.

## Pipeline

```
Raw Input
   │
   ▼
┌─────────┐
│  Lexer  │  tokenizes input into numbers, identifiers, operators
└────┬────┘
     │ tokens
     ▼
┌─────────┐
│ Parser  │  recursive descent → builds Abstract Syntax Tree (AST)
└────┬────┘
     │ AST
     ▼
┌──────────┐
│  IR Gen  │  walks AST → emits three-address intermediate representation
└────┬─────┘
     │ IR instructions
     ▼
┌────────────────────┐
│  Register Allocator│  linear-scan → assigns physicial registers (r0..r3)
│                    │  spills to memory slots when registers exhausted
└────────────────────┘
     │
     ▼
  Pseudo-Assembly Output
```

## Example Session

```
>> 2 + 3 * 4
=> 14
--- IR + Register Allocation ---
  MOV r0, 2
  MOV r1, 3
  MOV r2, 4
  MUL r3, r1, r2       ← operator precedence respected at IR level
  ADD [mem0], r0, r3   ← all 4 regs live; allocator spills to memory
--- end ---

>> x = 10
=> 10
--- IR + Register Allocation ---
  MOV r0, 10
  MOV x, r0
--- end ---

>> x + 5
=> 15
--- IR + Register Allocation ---
  MOV r0, 5
  ADD r1, x, r0
--- end ---
```

## Key Concepts Implemented

- **Lexical analysis** — scanning raw text into a token stream
- **Recursive descent parsing** — hand-written top-down parser with correct precedence
- **Abstract Syntax Tree (AST)** — typed node hierarchy with unique_ptr ownership
- **Three-address IR** — every operation broken into `result = left op right` form
  (same concept as LLVM IR / NVIDIA PTX)
- **Linear-scan register allocation** — assigns temps to physical registers in
  definition order; the same algorithm used in production compilers (LLVM, GCC)
- **Spill handling** — when all registers are live, operands spill to named memory
  slots (`[mem0]`, `[mem1]`, ...) — mirrors what real backends do under pressure
- **Variable scoping** — runtime symbol table via `unordered_map`
- **Error handling** — division by zero, undefined variables, unexpected tokens

## Build & Run

Requirements: `g++` with C++17 support, `make`

```bash
git clone https://github.com/A-b-h-i-n-a-v-1-9/compiler.git
cd compiler
make
./compiler
```

## Project Structure

```
compiler/
├── include/
│   ├── lexer.h         # token types and tokenizer interface
│   ├── parser.h        # AST node definitions and parser interface
│   ├── evaluator.h     # evaluator with variable store
│   ├── ir.h            # IR instruction types and IRProgram
│   ├── ir_gen.h        # AST → three-address IR emitter
│   └── reg_alloc.h     # linear-scan register allocator
├── src/
│   ├── lexer.cpp
│   ├── parser.cpp
│   ├── evaluator.cpp
│   ├── ir_gen.cpp      # tree-walking IR emission
│   ├── reg_alloc.cpp   # linear scan + spill logic + asm printer
│   └── main.cpp        # REPL — eval + IR + regalloc per expression
└── Makefile
```

## Why This Project

NVIDIA's compiler toolchain (NVCC) compiles CUDA source through multiple IR stages
before reaching PTX and finally machine code. This project builds that same pipeline
at a micro scale — every stage hand-written — to develop deep intuition for how
source text becomes executable instructions, register by register.

Written in C++17. Built on Kali Linux.
