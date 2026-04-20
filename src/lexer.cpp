#include "lexer.h"
#include <cctype>
#include <stdexcept>

std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < input.size()) {
        // Skip spaces
        if (std::isspace(input[i])) { i++; continue; }

        // Numbers
        if (std::isdigit(input[i])) {
            std::string num;
            while (i < input.size() && std::isdigit(input[i]))
                num += input[i++];
            tokens.push_back({TokenType::NUMBER, num});
            continue;
        }

        // Identifiers / variable names
        if (std::isalpha(input[i])) {
            std::string ident;
            while (i < input.size() && std::isalnum(input[i]))
                ident += input[i++];
            tokens.push_back({TokenType::IDENT, ident});
            continue;
        }

        // Operators and symbols
        switch (input[i]) {
            case '+': tokens.push_back({TokenType::PLUS,    "+"}); break;
            case '-': tokens.push_back({TokenType::MINUS,   "-"}); break;
            case '*': tokens.push_back({TokenType::STAR,    "*"}); break;
            case '/': tokens.push_back({TokenType::SLASH,   "/"}); break;
            case '=': tokens.push_back({TokenType::EQUALS,  "="}); break;
            case '(': tokens.push_back({TokenType::LPAREN,  "("}); break;
            case ')': tokens.push_back({TokenType::RPAREN,  ")"}); break;
            default:
                throw std::runtime_error(
                    std::string("Unknown character: ") + input[i]);
        }
        i++;
    }

    tokens.push_back({TokenType::END, ""});
    return tokens;
}
