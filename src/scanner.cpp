#include "../include/scanner.hpp"
#include "../include/deterministic_finite_automatas/dfa_identifiers.hpp"
#include "../include/deterministic_finite_automatas/dfa_integers.hpp"
#include "../include/deterministic_finite_automatas/dfa_math_symbols.hpp"
#include "../include/deterministic_finite_automatas/dfa_point_numbers.hpp"
#include "../include/deterministic_finite_automatas/dfa_relational_operators.hpp"
#include "../include/deterministic_finite_automatas/dfa_logic_operators.hpp"
#include "../include/deterministic_finite_automatas/dfa_bit_operators.hpp"
#include "../include/deterministic_finite_automatas/dfa_grouping_operators.hpp"
#include "../include/deterministic_finite_automatas/dfa_string_literals.hpp"
#include "../include/deterministic_finite_automatas/dfa_special_symbols.hpp"
#include <string>
#include <iostream>

mini_c_lexer::Scanner::Scanner() : prefix("") {}; 

void mini_c_lexer::Scanner::scan(std::string& input) {
    last_detected_token = "NONE";
    std::cout << "Currently scanning code..." << std::endl << input << std::endl;
    remove_comments(input); // Ensures there's no comments in the input
    input.push_back('\0'); // This character is appended to ensure the last token of the input is processed
    for (char c : input) {
        // If a string or char literal is being scanned, the algorithm change in order
        // to scan it properly
        if (is_scanning_string_or_char_literal()) {
            prefix += c;
            dfa_string_literals.do_transition(c);
            dfa_char_literals.do_transition(c);
            last_detected_token = (dfa_char_literals.which_token_is() != "NONE") ? 
                    dfa_char_literals.which_token_is() : last_detected_token;  
            last_detected_token = (dfa_string_literals.which_token_is() != "NONE") ? 
                    dfa_string_literals.which_token_is() : last_detected_token;  
            continue;
        }
        // If the current character is a character that separates tokens then outputs the
        // last token detected before that character and continues scanning
        if (c == '\n' || c == '\t' || c == '\0' || c == ' ') {
            if (last_detected_token != "NONE") std::cout << "TOKEN: " << last_detected_token 
                                                << " \"" << prefix << "\"" << std::endl;
            prefix = "";
            restart_dfas();
            last_detected_token = "NONE";
            continue;
        }
        prefix += c;
        make_dfas_do_transition(c);
        update_last_detected_token_if_not_keyword();
        update_last_detected_token_if_keyword();

        // If the current prefix with the last character added is not a lexem of any DFA anymore, 
        // outputs the last token detected and the prefix before it stopped beign a lexem. 
        // Then restarts the value of the prefix starting with the new character that made the last
        // prefix stop beign a lexem to scan a new token.
        if (!is_current_prefix_a_lexem() && !is_scanning_string_or_char_literal() && !is_a_longer_prefix_possible()) {
            std::cout << "TOKEN: " << last_detected_token << " \"" << prefix.substr(0, prefix.length() - 1) << "\"" << std::endl;
            prefix = c;
            last_detected_token = "NONE";
            restart_dfas();
            update_last_detected_token_if_keyword();
            make_dfas_do_transition(c);
            update_last_detected_token_if_not_keyword();
        }
    }
}

bool mini_c_lexer::Scanner::update_last_detected_token_if_keyword() {
    if (prefix == "auto") {
        last_detected_token = "AUTO";
        return true;
    }
    if (prefix == "double") {
        last_detected_token = "DOUBLE";
        return true;
    }
    if (prefix == "int") {
        last_detected_token = "INT";
        return true;
    }
    if (prefix == "struct") {
        last_detected_token = "STRUCT";
        return true;
    }
    if (prefix == "break") {
        last_detected_token = "BREAK";
        return true;
    }
    if (prefix == "else") {
        last_detected_token = "ELSE";
        return true;
    }
    if (prefix == "long") {
        last_detected_token = "LONG";
        return true;
    }
    if (prefix == "switch") {
        last_detected_token = "SWITCH";
        return true;
    }
    if (prefix == "case") {
        last_detected_token = "CASE";
        return true;
    }
    if (prefix == "enum") {
        last_detected_token = "ENUM";
        return true;
    }
    if (prefix == "register") {
        last_detected_token = "REGISTER";
        return true;
    }
    if (prefix == "typedef") {
        last_detected_token = "typedef";
        return true;
    }
    if (prefix == "char") {
        last_detected_token = "CHAR";
        return true;
    }
    if (prefix == "extern") {
        last_detected_token = "EXTERN";
        return true;
    }
    if (prefix == "return") {
        last_detected_token = "RETURN";
        return true;
    }
    if (prefix == "union") {
        last_detected_token = "UNION";
        return true;
    }
    if (prefix == "const") {
        last_detected_token = "CONST";
        return true;
    }
    if (prefix == "float") {
        last_detected_token = "FLOAT";
        return true;
    }
    if (prefix == "short") {
        last_detected_token = "SHORT";
        return true;
    }
    if (prefix == "unsigned") {
        last_detected_token = "UNSIGNED";
        return true;
    }
    if (prefix == "continue") {
        last_detected_token = "CONTINUE";
        return true;
    }
    if (prefix == "for") {
        last_detected_token = "FOR";
        return true;
    }
    if (prefix == "signed") {
        last_detected_token = "SIGNED";
        return true;
    }
    if (prefix == "void") {
        last_detected_token = "VOID";
        return true;
    }
    if (prefix == "default") {
        last_detected_token = "DEFAULT";
        return true;
    }
    if (prefix == "goto") {
        last_detected_token = "GOTO";
        return true;
    }
    if (prefix == "sizeof") {
        last_detected_token = "SIZEOF";
        return true;
    }
    if (prefix == "volatile") {
        last_detected_token = "VOLATILE";
        return true;
    }
    if (prefix == "do") {
        last_detected_token = "DO";
        return true;
    }
    if (prefix == "if") {
        last_detected_token = "IF";
        return true;
    }
    if (prefix == "static") {
        last_detected_token = "STATIC";
        return true;
    }
    if (prefix == "while") {
        last_detected_token = "WHILE";
        return true;
    }
    if (prefix == "main") {
        last_detected_token = "MAIN";
        return true;
    }
    return false;
};

void mini_c_lexer::Scanner::update_last_detected_token_if_not_keyword() {
    last_detected_token = (dfa_identifiers.which_token_is() != "NONE") ? 
                    dfa_identifiers.which_token_is() : last_detected_token;
    last_detected_token = (dfa_point_numbers.which_token_is() != "NONE") ? 
                    dfa_point_numbers.which_token_is() : last_detected_token;
    last_detected_token = (dfa_integers.which_token_is() != "NONE") ? 
                    dfa_integers.which_token_is() : last_detected_token; 
    last_detected_token = (dfa_string_literals.which_token_is() != "NONE") ? 
                    dfa_string_literals.which_token_is() : last_detected_token;
    last_detected_token = (dfa_grouping_operators.which_token_is() != "NONE") ? 
                    dfa_grouping_operators.which_token_is() : last_detected_token;
    last_detected_token = (dfa_bit_operators.which_token_is() != "NONE") ? 
                    dfa_bit_operators.which_token_is() : last_detected_token;  
    last_detected_token = (dfa_relational_operators.which_token_is() != "NONE") ? 
                    dfa_relational_operators.which_token_is() : last_detected_token; 
    last_detected_token = (dfa_math_symbols.which_token_is() != "NONE") ? 
                    dfa_math_symbols.which_token_is() : last_detected_token;       
    last_detected_token = (dfa_special_symbols.which_token_is() != "NONE") ? 
                    dfa_special_symbols.which_token_is() : last_detected_token;      
    last_detected_token = (dfa_char_literals.which_token_is() != "NONE") ? 
                    dfa_char_literals.which_token_is() : last_detected_token;  
    last_detected_token = (dfa_logic_operators.which_token_is() != "NONE") ?
                    dfa_logic_operators.which_token_is() : last_detected_token;  
}

void mini_c_lexer::Scanner::make_dfas_do_transition(char current_character) {
    dfa_identifiers.do_transition(current_character);
    dfa_integers.do_transition(current_character);
    dfa_math_symbols.do_transition(current_character);
    dfa_point_numbers.do_transition(current_character);
    dfa_relational_operators.do_transition(current_character);
    dfa_logic_operators.do_transition(current_character);
    dfa_bit_operators.do_transition(current_character);
    dfa_grouping_operators.do_transition(current_character);
    dfa_string_literals.do_transition(current_character);
    dfa_special_symbols.do_transition(current_character);
    dfa_char_literals.do_transition(current_character);
};

void mini_c_lexer::Scanner::restart_dfas() {
    dfa_identifiers.restart();
    dfa_integers.restart();
    dfa_math_symbols.restart();
    dfa_point_numbers.restart();
    dfa_relational_operators.restart();
    dfa_logic_operators.restart();
    dfa_bit_operators.restart();
    dfa_grouping_operators.restart();
    dfa_string_literals.restart();
    dfa_special_symbols.restart();
    dfa_char_literals.restart();
};

bool mini_c_lexer::Scanner::is_current_prefix_a_lexem() {
    if (dfa_bit_operators.is_lexem() || dfa_grouping_operators.is_lexem() || dfa_identifiers.is_lexem() ||
        dfa_integers.is_lexem() || dfa_logic_operators.is_lexem() || dfa_math_symbols.is_lexem() ||
        dfa_point_numbers.is_lexem() || dfa_relational_operators.is_lexem() || dfa_string_literals.is_lexem() ||
        dfa_special_symbols.is_lexem() || dfa_char_literals.is_lexem() ||
        prefix == "auto" || prefix == "double" || prefix == "int" ||
        prefix == "struct" || prefix == "break" || prefix == "else" ||
        prefix == "long" || prefix == "switch" || prefix == "case" ||
        prefix == "enum" || prefix == "register" || prefix == "typedef" ||
        prefix == "char" || prefix == "extern" || prefix == "return" ||
        prefix == "union" || prefix == "const" || prefix == "float" ||
        prefix == "short" || prefix == "unsigned" || prefix == "continue" ||
        prefix == "for" || prefix == "signed" || prefix == "void" ||
        prefix == "default" || prefix == "goto" || prefix == "sizeof" ||
        prefix == "volatile" || prefix == "do" || prefix == "if" ||
        prefix == "static" || prefix == "while") {
        return true;
    }
    return false;
}

void mini_c_lexer::Scanner::remove_comments(std::string& input) {
    bool is_comment = false;
    int start_comment_index = -1;
    for (size_t i = 0; i < input.length(); i++) {
        if (i < input.length() - 1 && input[i] == '/' && input[i + 1] == '/' && !is_comment) {
            start_comment_index = i;
            is_comment = true;
        }
        if (is_comment) { // A comment is checking if is_comment equals true
            if (input[i] == '\n' || i == input.length() - 1) { // End of comment is arrived
                if (i == input.length() - 1) {
                    input.erase(start_comment_index, i - start_comment_index + 1);
                }
                else {
                    input.erase(start_comment_index, i - start_comment_index); // if comment ends with line break
                                                                                // then the line break is not erased 
                }
                is_comment = false;
                i = start_comment_index - 1;
            }
        }
    }
};

bool mini_c_lexer::Scanner::is_scanning_string_or_char_literal() {
    return dfa_char_literals.is_scanning_char_literal() || dfa_string_literals.is_scanning_string_literal();
}

bool mini_c_lexer::Scanner::is_a_longer_prefix_possible() {
    // The prefix can be a point number
    bool is_possible = (dfa_point_numbers.get_current_state() == 2 ||
                        dfa_point_numbers.get_current_state() == 3 ||
                        dfa_point_numbers.get_current_state() == 4);
    return is_possible;
}