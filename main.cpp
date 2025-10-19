#include "include/deterministic_finite_automatas/dfa_identifiers.hpp"
#include "include/deterministic_finite_automatas/dfa_integers.hpp"
#include "include/deterministic_finite_automatas/dfa_math_symbols.hpp"
#include "include/deterministic_finite_automatas/dfa_point_numbers.hpp"
#include "include/deterministic_finite_automatas/dfa_relational_operators.hpp"
#include "include/deterministic_finite_automatas/dfa_logic_operators.hpp"
#include "include/deterministic_finite_automatas/dfa_bit_operators.hpp"

int main() {
    mini_c_lexer::DFAIdentifiers dfa_identifiers;
    dfa_identifiers.test();
    mini_c_lexer::DFAIntegers dfa_constants;
    dfa_constants.test();
    mini_c_lexer::DFAMathSymbols dfa_math_symbols;
    dfa_math_symbols.test();
    mini_c_lexer::DFAPointNumbers dfa_point_numbers;
    dfa_point_numbers.test();
    mini_c_lexer::DFARelationalOperators dfa_relational_operators;
    dfa_relational_operators.test();
    mini_c_lexer::DFALogicOperators dfa_logic_operators;
    dfa_logic_operators.test();
    mini_c_lexer::DFABitOperators dfa_bit_operators;
    dfa_bit_operators.test();
    return 0;
}