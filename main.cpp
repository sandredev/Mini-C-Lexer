#include "include/deterministic_finite_automatas/dfa_identifiers.hpp"
#include "include/deterministic_finite_automatas/dfa_integers.hpp"
#include "include/deterministic_finite_automatas/dfa_math_symbols.hpp"
#include "include/deterministic_finite_automatas/dfa_point_numbers.hpp"
#include "include/deterministic_finite_automatas/dfa_relational_operators.hpp"
#include "include/deterministic_finite_automatas/dfa_logic_operators.hpp"
#include "include/deterministic_finite_automatas/dfa_bit_operators.hpp"
#include "include/deterministic_finite_automatas/dfa_grouping_operators.hpp"
#include "include/deterministic_finite_automatas/dfa_string_literals.hpp"
#include "include/deterministic_finite_automatas/dfa_special_symbols.hpp"
#include "include/deterministic_finite_automatas/dfa_char_literals.hpp"
#include "include/scanner.hpp"
#include <iostream>
#include <fstream>

void test_dfas() {
    mini_c_lexer::DFAIdentifiers dfa_identifiers;
    dfa_identifiers.test();
    std::cout << std::endl;
    mini_c_lexer::DFAIntegers dfa_constants;
    dfa_constants.test();
    std::cout << std::endl;
    mini_c_lexer::DFAMathSymbols dfa_math_symbols;
    dfa_math_symbols.test();
    std::cout << std::endl;
    mini_c_lexer::DFAPointNumbers dfa_point_numbers;
    dfa_point_numbers.test();
    std::cout << std::endl;
    mini_c_lexer::DFARelationalOperators dfa_relational_operators;
    dfa_relational_operators.test();
    std::cout << std::endl;
    mini_c_lexer::DFALogicOperators dfa_logic_operators;
    dfa_logic_operators.test();
    std::cout << std::endl;
    mini_c_lexer::DFABitOperators dfa_bit_operators;
    dfa_bit_operators.test();
    std::cout << std::endl;
    mini_c_lexer::DFAGroupingOperators dfa_grouping_operators;
    dfa_grouping_operators.test();
    std::cout << std::endl;
    mini_c_lexer::DFAStringLiterals dfa_string_literals;
    dfa_string_literals.test();
    std::cout << std::endl;
    mini_c_lexer::DFASpecialSymbols dfa_special_symbols;
    dfa_special_symbols.test();
    std::cout << std::endl;
    mini_c_lexer::DFACharLiterals dfa_char_literals;
    dfa_char_literals.test();
    std::cout << std::endl;
}

int main() {
    test_dfas();
    mini_c_lexer::Scanner scanner;
    std::string code = "";
    std::cout << std::endl;
    std::fstream code_file("test_code.c");
    std::string code_line;
    while (std::getline(code_file, code_line)) {
        code += code_line + "\n";
    }
    scanner.scan(code);
    return 0;
}