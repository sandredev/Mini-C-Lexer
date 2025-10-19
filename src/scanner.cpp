#include "../include/scanner.hpp"
#include <string>
#include <iostream>

mini_c_lexer::Scanner::Scanner() : prefix(""), is_matching(false) {}; 

void mini_c_lexer::Scanner::scan(std::string& input) {
    for (char c : input) {
        prefix += c;
        dfa_identifiers.do_transition(c);
        dfa_integers.do_transition(c);
        if (dfa_identifiers.is_lexem()) {
            is_matching = true;
            std::cout << "Token: IDENTIFIER \"" << prefix << "\"" << std::endl;
        }
        else if (dfa_integers.is_lexem()) {
            is_matching = true;
            std::cout << "Token: INT_NUM \"" << prefix << "\"" << std::endl;

        }
        else if (prefix == "main") {
            is_matching = true;
            std::cout << "Token: MAIN \"" << prefix << "\"" << std::endl;
        }
        else if (prefix == "int") {
            is_matching = true;
            std::cout << "Token: INT \"" << prefix << "\"" << std::endl;
        }
        else if (prefix == "void") {
            is_matching = true;
            std::cout << "Token: VOID \"" << prefix << "\"" << std::endl;
        }
        else if (prefix == "break") {
            is_matching = true;
            std::cout << "Token: BREAK \"" << prefix << "\"" << std::endl;
        }
        else if (prefix == "do") {
            is_matching = true;
            std::cout << "Token: DO \"" << prefix << "\"" << std::endl;
        }
        else if (prefix == "if") {
            is_matching = true;
            std::cout << "Token: IF \"" << prefix << "\"" << std::endl;
        }
        else if (prefix == "while") {
            is_matching = true;
            std::cout << "Token: WHILE \"" << prefix << "\"" << std::endl;
        }
        else if (prefix == "return") {
            is_matching = true;
            std::cout << "Token: RETURN \"" << prefix << "\"" << std::endl;
        }
        else if (prefix == "scanf") {
            is_matching = true;
            std::cout << "Token: READ \"" << prefix << "\"" << std::endl;
        }
        else if (prefix == "printf") {
            is_matching = true;
            std::cout << "Token: WRITE \"" << prefix << "\"" << std::endl;
        }
        else {
            is_matching = false;
        }
    }
}