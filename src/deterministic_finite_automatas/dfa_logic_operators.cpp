#include "../../include/deterministic_finite_automatas/dfa_logic_operators.hpp"
#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <stdexcept>


mini_c_lexer::DFALogicOperators::DFALogicOperators() {
    /*
    DFA:
                &       |       !   
    init        AND     OR      NOT_OP  0
    AND         ANDAND  -       -       0
    OR          -       OROR    -       0
    ANDAND      -       -       -       1
    OROR        -       -       -       1
    NOT_OP      -       -       -       1

    the last column specifies whether the state is acceptance or not.

    -1 means no transition.
    */
    transitions_table = {
        {1, 2, 5, 0},
        {3, -1, -1, -1, 0},
        {-1, 4, -1, -1, 0},
        {-1, -1, -1, -1, 1},
        {-1, -1, -1, -1, 1},
        {-1, -1, -1, -1, 1}
    };
};

void mini_c_lexer::DFALogicOperators::do_transition(char& input) {
    if (current_state == -1) return;
    switch (input) 
    {
        case '&': 
            current_state = transitions_table[current_state][0];
            break;
        case '|':
            current_state = transitions_table[current_state][1];
            break;
        case '!':
            current_state = transitions_table[current_state][2];
            break;
        default:
            current_state = -1;
    }
};

void mini_c_lexer::DFALogicOperators::test() {
    std::cout << "Currently testing DFA that recognizes logic operators..." << std::endl;
    std::vector<std::string> test_inputs = {
        "!",
        "||",
        "&&",
        "|",
        "&",
        "!=",
        "<<"
        };
    for (std::string& input : test_inputs) {
        current_state = 0;
        for (char c : input) {
            do_transition(c);
        }
        std::cout << input << " is lexem: " << std::boolalpha << is_lexem();
        try {
            std::cout << "; TOKEN: " << which_token_is() << std::endl;
        }
        catch (std::logic_error) {
            std::cout << "NONE" << std::endl;
        }
    }
    current_state = 0;
};

bool mini_c_lexer::DFALogicOperators::is_lexem() const {
    if (current_state == -1) return false;
    return transitions_table[current_state][4] == 1;
}

std::string mini_c_lexer::DFALogicOperators::which_token_is() {
    switch (current_state)
    {
        case 3:
            return "ANDAND";
            break;
        case 4:
            return "OROR";
            break;
        case 5:
            return "NOT_OP";
            break;
        default:
            throw std::logic_error("no token's been detected");
            break;
    }
}