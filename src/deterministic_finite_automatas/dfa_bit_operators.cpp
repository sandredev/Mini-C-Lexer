#include "../../include/deterministic_finite_automatas/dfa_bit_operators.hpp"
#include <string>
#include <vector>
#include <iostream>


mini_c_lexer::DFABitOperators::DFABitOperators() {
    /*
    DFA:
                &           |           ^           <           >           ~
    init        BIT_AND     BIT_OR      BIT_XOR     SHL_OP1     SHR_OP1     BIT_NOT     0
    BIT_AND     -           -           -           -           -           -           1
    BIT_OR      -           -           -           -           -           -           1
    BIT_XOR     -           -           -           -           -           -           1
    SHL_OP1     -           -           -           SHL_OP2     -           -           0
    SHR_OP1     -           -           -           -           SHR_OP2     -           0     
    SHL_OP2     -           -           -           -           -           -           1
    SHR_OP2     -           -           -           -           -           -           1
    BIT_NOT     -           -           -           -           -           -           1
    
    the last column specifies whether the state is acceptance or not.

    -1 means no transition.
    */
    transitions_table = {
        {1, 2, 3, 4, 5, 8, 0},
        {-1, -1, -1, -1, -1, -1, 1},
        {-1, -1, -1, -1, -1, -1, 1},
        {-1, -1, -1, -1, -1, -1, 1},
        {-1, -1, -1, 6, -1, -1, 0},
        {-1, -1, -1, -1, 7, -1, 0},
        {-1, -1, -1, -1, -1, -1, 1},
        {-1, -1, -1, -1, -1, -1, 1},
        {-1, -1, -1, -1, -1, -1, 1},
    };
};

void mini_c_lexer::DFABitOperators::do_transition(char& input) {
    if (current_state == -1) return;
    switch (input) 
    {
        case '&': 
            current_state = transitions_table[current_state][0];
            break;
        case '|':
            current_state = transitions_table[current_state][1];
            break;
        case '^':
            current_state = transitions_table[current_state][2];
            break;
        case '<':
            current_state = transitions_table[current_state][3];
            break;
        case '>':
            current_state = transitions_table[current_state][4];
            break;
        case '~':
            current_state = transitions_table[current_state][5];
            break;
        default:
            current_state = -1;
    }
};

void mini_c_lexer::DFABitOperators::test() {
    std::cout << "Currently testing DFA that recognizes bit operators..." << std::endl;
    std::vector<std::string> test_inputs = {
        "~",
        "<<",
        ">>",
        "^",
        "&",
        "|",
        "||",
        "<",
        ">",
        "&&",
        "!"
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

bool mini_c_lexer::DFABitOperators::is_lexem() const {
    if (current_state == -1) return false;
    return transitions_table[current_state][6] == 1;
}

std::string mini_c_lexer::DFABitOperators::which_token_is() {
    switch (current_state)
    {
        case 1:
            return "BIT_AND";
            break;
        case 2:
            return "BIT_OR";
            break;
        case 3:
            return "BIT_XOR";
            break;
        case 6:
            return "SHL_OP";
            break;
        case 7:
            return "SHR_OP";
            break;
        case 8:
            return "BIT_NOT";
            break;
        default:
            return "NONE";
            break;
    }
}