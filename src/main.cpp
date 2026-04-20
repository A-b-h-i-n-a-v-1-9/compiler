
#include <iostream>

#include <string>

#include "lexer.h"

#include "parser.h"

#include "evaluator.h"

int main() {

    Evaluator eval;

    std::string line;

    std::cout << "==================================\n";

    std::cout << "  Mini Compiler  | Kalki | 4bh1nav \n";

    std::cout << "==================================\n";

    std::cout << "Commands: type expressions or assignments\n";

    std::cout << "Examples: 2 + 3 * 4  |  x = 10  |  x + 5\n";

    std::cout << "Type 'exit' to quit\n\n";

    while (true) {

        std::cout << ">> ";

        if (!std::getline(std::cin, line)) break;

        if (line == "exit") break;

        if (line.empty()) continue;

        try {

            auto tokens = tokenize(line);

            auto ast    = parse(tokens);

            double result = eval.evaluate(ast.get());

            std::cout << "=> " << result << "\n";

        } catch (const std::exception& e) {

            std::cout << e.what() << "\n";

        }

    }

    std::cout << "\nGoodbye!\n";

    return 0;

}

