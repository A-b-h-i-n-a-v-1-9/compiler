#pragma once
#include <string>
#include <vector>

using Operand = std::string;

struct IRInstr {
    enum class Op { ADD, SUB, MUL, DIV, ASSIGN } op;
    std::string result;
    Operand     left;
    Operand     right;
};

struct IRProgram {
    std::vector<IRInstr> instrs;
    int tempCount = 0;
    std::string newTemp() {
        return "t" + std::to_string(tempCount++);
    }
};
