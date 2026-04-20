#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "ir_gen.h"
#include "reg_alloc.h"

int main() {
    Evaluator eval;
    std::string line;

    std::cout << "==========================================\n";
    std::cout << "  Mini Compiler + IR  |  Kalki | 4bh1nav  \n";
    std::cout << "==========================================\n";
    std::cout << "Commands: type expressions or assignments\n";
    std::cout << "Examples: 2 + 3 * 4  |  x = 10  |  x + 5\n";
    std::cout << "Type 'exit' to quit\n\n";

    while (true) {
        std::cout << ">> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "exit") break;
        if (line.empty()) continue;

        try {
            // --- evaluation (original pipeline) ---
            auto tokens  = tokenize(line);
            auto ast     = parse(tokens);
            double result = eval.evaluate(ast.get());
            std::cout << "=> " << result << "\n";

            // --- IR: re-tokenize + re-parse fresh ---
            auto tokens2 = tokenize(line);
            auto ast2    = parse(tokens2);
            IRGen gen;
            gen.emit(ast2.get());

            // --- register allocation + asm print ---
            RegAlloc ra;
            ra.run(gen.program);
            ra.printAssembly(gen.program);

        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }
    }

    std::cout << "\nGoodbye!\n";
    return 0;
}
