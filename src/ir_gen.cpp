#include "ir_gen.h"
#include <stdexcept>

Operand IRGen::emit(Node* node) {

    if (auto* n = dynamic_cast<NumberNode*>(node)) {
        // Load immediate into a fresh temp
        std::string t = program.newTemp();
        program.instrs.push_back({IRInstr::Op::ASSIGN, t, n->value == (int)n->value
            ? std::to_string((int)n->value)
            : std::to_string(n->value), ""});
        return t;
    }

    if (auto* n = dynamic_cast<VariableNode*>(node))
        return n->name;   // variables are their own operand

    if (auto* n = dynamic_cast<AssignNode*>(node)) {
        Operand src = emit(n->expr.get());
        program.instrs.push_back({IRInstr::Op::ASSIGN, n->name, src, ""});
        return n->name;
    }

    if (auto* n = dynamic_cast<BinaryOpNode*>(node)) {
        Operand l = emit(n->left.get());
        Operand r = emit(n->right.get());
        std::string t = program.newTemp();
        IRInstr::Op op;
        switch (n->op) {
            case '+': op = IRInstr::Op::ADD; break;
            case '-': op = IRInstr::Op::SUB; break;
            case '*': op = IRInstr::Op::MUL; break;
            case '/': op = IRInstr::Op::DIV; break;
            default: throw std::runtime_error("unknown op");
        }
        program.instrs.push_back({op, t, l, r});
        return t;
    }

    throw std::runtime_error("IRGen: unknown node");
}
