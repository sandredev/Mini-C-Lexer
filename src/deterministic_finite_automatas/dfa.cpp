#include "../../include/deterministic_finite_automatas/dfa.hpp"


mini_c_lexer::DFA::DFA() : current_state(0) {};

mini_c_lexer::DFA::~DFA() = default;

void mini_c_lexer::DFA::restart() {
    current_state = 0;
}