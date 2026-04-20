#include "evaluator.h"
#include <stdexcept>

double Evaluator::evaluate(Node* node) {

    // It's a number — just return it
    if (auto* n = dynamic_cast<NumberNode*>(node))
        return n->value;

    // It's a variable — look it up
    if (auto* n = dynamic_cast<VariableNode*>(node)) {
        if (variables.find(n->name) == variables.end())
            throw std::runtime_error(
                "Error: undefined variable '" + n->name + "'");
        return variables[n->name];
    }

    // It's an assignment — evaluate RHS, store it
    if (auto* n = dynamic_cast<AssignNode*>(node)) {
        double val = evaluate(n->expr.get());
        variables[n->name] = val;
        return val;
    }

    // It's a binary operation — evaluate both sides
    if (auto* n = dynamic_cast<BinaryOpNode*>(node)) {
        double left  = evaluate(n->left.get());
        double right = evaluate(n->right.get());
        switch (n->op) {
            case '+': return left + right;
            case '-': return left - right;
            case '*': return left * right;
            case '/':
                if (right == 0)
                    throw std::runtime_error("Error: division by zero");
                return left / right;
        }
    }

    throw std::runtime_error("Error: unknown node type");
}
