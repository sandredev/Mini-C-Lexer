#include "../../include/deterministic_finite_automatas/dfa_special_symbols.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

mini_c_lexer::DFASpecialSymbols::DFASpecialSymbols() {
    /*
    DFA:
                    =            ,            ;            -            >           .           #      
    init            ASSIGN       COMMA        SEMI         MINUS        -           DOT         HASHTAG     0   
    ASSIGN          -            -            -            -            -           -           -           1
    COMMA           -            -            -            -            -           -           -           1
    SEMI            -            -            -            -            -           -           -           1        
    MINUS           -            -            -            -            ARROW_OP    -           -           0
    DOT_OP          -            -            -            -            -           -           -           1         
    ARROW_OP        -            -            -            -            -           -           -           1
    HASHTAG         -            -            -            -            -           -           -           1

    the last column specifies whether the state is acceptance or not.

    -1 means no transition.
    */
    transitions_table = {
        {1, 2, 3, 4, -1, 5, 7, 0},  // init
        {-1, -1, -1, -1, -1, -1, -1, 1},  // ASSIGN
        {-1, -1, -1, -1, -1, -1, -1, 1},  // COMMA
        {-1, -1, -1, -1, -1, -1, -1, 1},  // SEMI
        {-1, -1, -1, -1, 6, -1, -1, 0},  // MINUS
        {-1, -1, -1, -1, -1, -1, -1, 1}, // DOT_OP
        {-1, -1, -1, -1, -1, -1, -1, 1}, // ARROW_OP
        {-1, -1, -1, -1, -1, -1, -1, 1}  // HASHTAG
    };
};

void mini_c_lexer::DFASpecialSymbols::do_transition(char& input) {
    if (current_state == -1) return;
    switch (input)
    {
    case '=':
        current_state = transitions_table[current_state][0];
        break;
    case ',':
        current_state = transitions_table[current_state][1];
        break;
    case ';':
        current_state = transitions_table[current_state][2];
        break;
    case '-':
        current_state = transitions_table[current_state][3];
        break;
    case '>':
        current_state = transitions_table[current_state][4];
        break;
    case '.':
        current_state = transitions_table[current_state][5];
        break;
    case '#':
        current_state = transitions_table[current_state][6];
        break;
    default:
        current_state = -1;
        break;
    }
};

void mini_c_lexer::DFASpecialSymbols::test() {
    std::cout << "Currently testing DFA that recognizes special symbols..." << std::endl;
    std::vector<std::string> test_inputs = {
        ".",
        ";",
        ",",
        "#",
        "->",
        "=",
        "-",
        ";;"
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

std::string mini_c_lexer::DFASpecialSymbols::which_token_is() {
    switch (current_state)
    {
    case 1:
        return "ASSIGN";
        break;
    case 2:
        return "COMMA";
        break;
    case 3:
        return "SEMI";
        break;
    case 5:
        return "DOT_OP";
        break;
    case 6:
        return "ARROW_OP";
        break;
    case 7:
        return "HASHTAG";
        break;
    default:
        return "NONE";
        break;
    }
}

bool mini_c_lexer::DFASpecialSymbols::is_lexem() const {
    if (current_state == -1) return false;
    return transitions_table[current_state][7] == 1;
}