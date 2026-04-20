#pragma once
#include "parser.h"
#include <unordered_map>

class Evaluator {
public:
    double evaluate(Node* node);
    std::unordered_map<std::string, double> variables;
};
