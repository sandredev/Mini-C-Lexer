#include "../../include/deterministic_finite_automatas/dfa_string_literals.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>


mini_c_lexer::DFAStringLiterals::DFAStringLiterals() {
    /*
    DFA:
                "       character         
    init        1"      -           0
    1"          2"      1"          0
    2"          -       -           1

    the last column specifies whether the state is acceptance or not.

    charater column corresponds to whatever character is different from doble quote.

    -1 means no transition.
    */
    transitions_table = {
        {1, -1, 0},
        {2, 1, 0},
        {-1, -1, 1}
    };
};

void mini_c_lexer::DFAStringLiterals::do_transition(char& input) {
    if (current_state == -1) return;
    switch (input) 
    {
        case '\"': 
            current_state = transitions_table[current_state][0];
            break;
        default:
            current_state = transitions_table[current_state][1];
    }
};

void mini_c_lexer::DFAStringLiterals::test() {
    std::cout << "Currently testing DFA that recognizes string literals..." << std::endl;
    std::vector<std::string> test_inputs = {
        "\"\"",
        "\"asdsad\"",
        "\"",
        "\"\"\"\"\"\"\"\""
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

bool mini_c_lexer::DFAStringLiterals::is_lexem() const {
    if (current_state == -1) return false;
    return transitions_table[current_state][2] == 1;
};

std::string mini_c_lexer::DFAStringLiterals::which_token_is() {
    if (is_lexem()) return "STRING_LITERAL";
    return "NONE";
}