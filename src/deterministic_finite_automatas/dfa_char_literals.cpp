#include "../../include/deterministic_finite_automatas/dfa_char_literals.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>


mini_c_lexer::DFACharLiterals::DFACharLiterals() {
    /*
    DFA:
                '       character         
    init        1'      -           0
    1'          2'      1'          0
    2'          -       -           1

    the last column specifies whether the state is acceptance or not.

    charater column corresponds to whatever character is different from doble quote.

    by design, I decided that this DFA behaves almost the same as the DFAStringLiterals because
    a character can be written with more than 1 character (such as \t) and it's not lexer's job
    to verify whether the character is valid or not, neither which character is.

    -1 means in the implementation no transition.
    */
    transitions_table = {
        {1, -1, 0}, // init
        {2, 1, 0},  // 1'
        {-1, -1, 1} // 2'
    };
};

void mini_c_lexer::DFACharLiterals::do_transition(char& input) {
    if (current_state == -1) return;
    switch (input) 
    {
        case '\'': 
            current_state = transitions_table[current_state][0];
            break;
        default:
            current_state = transitions_table[current_state][1];
    }
};

void mini_c_lexer::DFACharLiterals::test() {
    std::cout << "Currently testing DFA that recognizes char literals..." << std::endl;
    std::vector<std::string> test_inputs = {
        "'a'",
        "'e'",
        "'\\t'",
        "'asa",
        "asa'"
        };
    for (std::string& input : test_inputs) {
        current_state = 0;
        for (char c : input) {
            do_transition(c);
        }
        std::cout << input << " is lexem: " << std::boolalpha << is_lexem();
        std::cout << "; TOKEN: " << which_token_is() << std::endl;
    }
    current_state = 0;
};

bool mini_c_lexer::DFACharLiterals::is_lexem() const {
    if (current_state == -1) return false;
    return transitions_table[current_state][2] == 1;
};

std::string mini_c_lexer::DFACharLiterals::which_token_is() {
    if (is_lexem()) return "CHAR_LITERAL";
    return "NONE";
}


bool mini_c_lexer::DFACharLiterals::is_scanning_char_literal() {
    return current_state == 1;
}