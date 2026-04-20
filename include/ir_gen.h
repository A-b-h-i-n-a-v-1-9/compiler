#pragma once
#include "parser.h"
#include "ir.h"

class IRGen {
public:
    IRProgram program;
    Operand emit(Node* node);
};
