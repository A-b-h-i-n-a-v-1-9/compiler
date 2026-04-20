#pragma once
#include "lexer.h"
#include <memory>
#include <string>

// AST Node types
struct Node {
    virtual ~Node() = default;
};

struct NumberNode : Node {
    double value;
    NumberNode(double v) : value(v) {}
};

struct VariableNode : Node {
    std::string name;
    VariableNode(const std::string& n) : name(n) {}
};

struct BinaryOpNode : Node {
    char op;
    std::unique_ptr<Node> left, right;
    BinaryOpNode(char o, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
        : op(o), left(std::move(l)), right(std::move(r)) {}
};

struct AssignNode : Node {
    std::string name;
    std::unique_ptr<Node> expr;
    AssignNode(const std::string& n, std::unique_ptr<Node> e)
        : name(n), expr(std::move(e)) {}
};

std::unique_ptr<Node> parse(const std::vector<Token>& tokens);
