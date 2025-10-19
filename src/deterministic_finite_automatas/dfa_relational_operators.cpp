#include "../../include/deterministic_finite_automatas/dfa_relational_operators.hpp"
#include <string>
#include <vector>
#include <cctype>
#include <iostream>


mini_c_lexer::DFARelationalOperators::DFARelationalOperators() {
    /*
    DFA:
                <           >           =           !           
    init        LT          GT          EQ1         NOT     0          
    GT          -           -           GTEQ        -       1
    LT          -           -           LTEQ        -       1
    GTEQ        -           -           -           -       1
    LTEQ        -           -           -           -       1
    EQ1         -           -           EQ2         -       0
    EQ2         -           -           -           -       1
    NOT         -           -           NOTEQ       -       0
    NOTEQ       -           -           -           -       1

    the last column specifies whether the state is acceptance or not.

    -1 means no transition.
    */
    transitions_table = {
        {2, 1, 5, 7, 0},
        {-1, -1, 3, -1, 1}, // GT
        {-1, -1, 4, -1, 1}, // LT
        {-1, -1, -1, -1, 1}, // GTEQ
        {-1, -1, -1, -1, 1},  //LTEQ
        {-1, -1, 6, -1, 0},
        {-1, -1, -1, -1, 1}, // EQ
        {-1, -1, 8, -1, 0},  
        {-1, -1, -1, -1, 1}  // NOTEQ
    };
};

void mini_c_lexer::DFARelationalOperators::do_transition(char& input) {
    if (current_state == -1) return;
    if (input == '<') current_state = transitions_table[current_state][0];
    else if (input == '>') current_state = transitions_table[current_state][1];
    else if (input == '=') current_state = transitions_table[current_state][2];
    else if (input == '!') current_state = transitions_table[current_state][3];
    else current_state = -1;
};

void mini_c_lexer::DFARelationalOperators::test() {
    std::cout << "Currently testing DFA that recognizes relational operators..." << std::endl;
    std::vector<std::string> test_inputs = {
            "<",     
            ">",     
            "<=",    
            ">=",    
            "==",    
            "!=",    
            "!",     
            "=",     
            "<<",    
            ">>",    
            "<>",    
            "><",    
            "===",   
            "!==",   

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

bool mini_c_lexer::DFARelationalOperators::is_lexem() const {
    if (current_state == -1) return false;
    return transitions_table[current_state][4] == 1;
}

std::string mini_c_lexer::DFARelationalOperators::which_token_is() {
    switch (current_state)
    {
        case 1:
            return "GT";
            break;
        case 2:
            return "LT";
            break;
        case 3:
            return "GTEQ";
            break;
        case 4:
            return "LTEQ";
            break;
        case 6:
            return "EQ";
            break;
        case 8:
            return "NOTEQ";
            break;
        default:
            throw std::logic_error("no lexem's been detected");
            break;
    }
}