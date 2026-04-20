#include "parser.h"
#include <stdexcept>

// Parser state
struct Parser {
    const std::vector<Token>& tokens;
    size_t pos = 0;

    Token peek() { return tokens[pos]; }
    Token consume() { return tokens[pos++]; }

    // Grammar rules (precedence low → high)
    // expr   → assignment
    // assign → IDENT = expr | addsub
    // addsub → muldiv ((+|-) muldiv)*
    // muldiv → primary ((*|/) primary)*
    // primary → NUMBER | IDENT | (expr)

    std::unique_ptr<Node> parseExpr() {
        // Check for assignment: IDENT = ...
        if (peek().type == TokenType::IDENT &&
            pos + 1 < tokens.size() &&
            tokens[pos + 1].type == TokenType::EQUALS) {
            std::string name = consume().value;
            consume(); // eat '='
            auto expr = parseExpr();
            return std::make_unique<AssignNode>(name, std::move(expr));
        }
        return parseAddSub();
    }

    std::unique_ptr<Node> parseAddSub() {
        auto left = parseMulDiv();
        while (peek().type == TokenType::PLUS ||
               peek().type == TokenType::MINUS) {
            char op = consume().value[0];
            auto right = parseMulDiv();
            left = std::make_unique<BinaryOpNode>(
                op, std::move(left), std::move(right));
        }
        return left;
    }

    std::unique_ptr<Node> parseMulDiv() {
        auto left = parsePrimary();
        while (peek().type == TokenType::STAR ||
               peek().type == TokenType::SLASH) {
            char op = consume().value[0];
            auto right = parsePrimary();
            left = std::make_unique<BinaryOpNode>(
                op, std::move(left), std::move(right));
        }
        return left;
    }

    std::unique_ptr<Node> parsePrimary() {
        Token t = peek();

        if (t.type == TokenType::NUMBER) {
            consume();
            return std::make_unique<NumberNode>(std::stod(t.value));
        }

        if (t.type == TokenType::IDENT) {
            consume();
            return std::make_unique<VariableNode>(t.value);
        }

        if (t.type == TokenType::LPAREN) {
            consume(); // eat '('
            auto expr = parseExpr();
            if (peek().type != TokenType::RPAREN)
                throw std::runtime_error("Expected ')'");
            consume(); // eat ')'
            return expr;
        }

        throw std::runtime_error(
            "Unexpected token: '" + t.value + "'");
    }
};

std::unique_ptr<Node> parse(const std::vector<Token>& tokens) {
    Parser p{tokens};
    return p.parseExpr();
}
