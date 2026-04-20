#pragma once
#include "ir.h"
#include <unordered_map>
#include <string>
#include <vector>

class RegAlloc {
public:
    static constexpr int NUM_REGS = 4;

    struct Allocation {
        bool        spilled   = false;
        int         reg       = -1;
        std::string spillSlot;
    };

    // operand name  →  allocation result
    std::unordered_map<std::string, Allocation> table;

    void run(const IRProgram& prog);
    void printAssembly(const IRProgram& prog) const;
};
