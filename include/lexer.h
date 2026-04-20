#pragma once
#include <string>
#include <vector>

enum class TokenType {
    NUMBER, IDENT,
    PLUS, MINUS, STAR, SLASH,
    EQUALS, LPAREN, RPAREN,
    END
};

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> tokenize(const std::string& input);
