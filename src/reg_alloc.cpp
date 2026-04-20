#include "reg_alloc.h"
#include <iostream>
#include <vector>
#include <algorithm>

// Linear-scan: assign registers in definition order, spill when exhausted
void RegAlloc::run(const IRProgram& prog) {
    std::vector<bool> used(NUM_REGS, false);
    int spillIdx = 0;

    auto alloc = [&](const std::string& name) {
        if (table.count(name)) return;          // already allocated
        // try to find a free register
        for (int i = 0; i < NUM_REGS; i++) {
            if (!used[i]) {
                used[i] = true;
                table[name] = {false, i, ""};
                return;
            }
        }
        // spill to memory
        table[name] = {true, -1, "mem" + std::to_string(spillIdx++)};
    };

    for (auto& ins : prog.instrs) {
        if (!ins.left.empty()  && ins.left[0]  != '-' &&
            !std::isdigit(ins.left[0]))           alloc(ins.left);
        if (!ins.right.empty() && ins.right[0] != '-' &&
            !std::isdigit(ins.right[0]))          alloc(ins.right);
        alloc(ins.result);
    }
}

static std::string opStr(IRInstr::Op op) {
    switch (op) {
        case IRInstr::Op::ADD:    return "ADD";
        case IRInstr::Op::SUB:    return "SUB";
        case IRInstr::Op::MUL:    return "MUL";
        case IRInstr::Op::DIV:    return "DIV";
        case IRInstr::Op::ASSIGN: return "MOV";
    }
    return "?";
}

static std::string loc(const std::unordered_map<std::string,
                       RegAlloc::Allocation>& tbl,
                       const std::string& name) {
    // numeric literals pass through unchanged
    if (name.empty() || std::isdigit(name[0]) || name[0] == '-')
        return name;
    auto it = tbl.find(name);
    if (it == tbl.end()) return name;
    return it->second.spilled
        ? "[" + it->second.spillSlot + "]"
        : "r" + std::to_string(it->second.reg);
}

void RegAlloc::printAssembly(const IRProgram& prog) const {
    std::cout << "\n--- IR + Register Allocation ---\n";
    for (auto& ins : prog.instrs) {
        std::string dst = loc(table, ins.result);
        if (ins.op == IRInstr::Op::ASSIGN) {
            std::cout << "  MOV " << dst << ", " << loc(table, ins.left) << "\n";
        } else {
            std::cout << "  " << opStr(ins.op)
                      << " " << dst
                      << ", " << loc(table, ins.left)
                      << ", " << loc(table, ins.right) << "\n";
        }
    }
    std::cout << "--- end ---\n";
}
