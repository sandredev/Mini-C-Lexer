#pragma once

#include <string>
#include "deterministic_finite_automatas/dfa_identifiers.hpp"
#include "deterministic_finite_automatas/dfa_integers.hpp"
#include "deterministic_finite_automatas/dfa_math_symbols.hpp"
#include "deterministic_finite_automatas/dfa_point_numbers.hpp"
#include "deterministic_finite_automatas/dfa_relational_operators.hpp"
#include "deterministic_finite_automatas/dfa_logic_operators.hpp"
#include "deterministic_finite_automatas/dfa_bit_operators.hpp"
#include "deterministic_finite_automatas/dfa_grouping_operators.hpp"
#include "deterministic_finite_automatas/dfa_string_literals.hpp"
#include "deterministic_finite_automatas/dfa_special_symbols.hpp"
#include "deterministic_finite_automatas/dfa_char_literals.hpp"

namespace mini_c_lexer {
    // Class that scans a C code and outputs each token that finds
    class Scanner { 
        private:
            std::string prefix;
            std::string last_detected_token;
            DFAIdentifiers dfa_identifiers;
            DFAIntegers dfa_integers;
            DFAMathSymbols dfa_math_symbols;
            DFAPointNumbers dfa_point_numbers;
            DFARelationalOperators dfa_relational_operators;
            DFALogicOperators dfa_logic_operators;
            DFABitOperators dfa_bit_operators;
            DFAGroupingOperators dfa_grouping_operators;
            DFAStringLiterals dfa_string_literals;
            DFASpecialSymbols dfa_special_symbols;
            DFACharLiterals dfa_char_literals;
        public:
            Scanner();

            /* 
               This function simulates a lexical scanner that iterates character by character 
               through the input string, using multiple DFAs (deterministic finite automata) 
               to detect valid lexemes such as identifiers, numbers, operators, and keywords.

               The algorithm works as follows:

                  - A null terminator ('\0') is appended to the input to ensure the last token is processed.
                  - Each character is read sequentially and appended to the current prefix buffer.
                  - The DFAs are updated with the current character to maintain their state transitions.
                  - When a delimiter (space, newline, tab, or EOF) is found, or when the prefix is no longer
                    recognized by any DFA, the last detected token is emitted.
                  - The scanner resets and continues processing the next token.
            */
            void scan(std::string& input);

            // Make the DFAs used to detect tokens do a transition with the current character
            // that is being scanned
            void make_dfas_do_transition(char current_caracter);

            // When a token is found, this function restart all the dfas so new tokens can be
            // detected 
            void restart_dfas();

            // Update the last detected token if it's a keyword          
            bool update_last_detected_token_if_keyword();

            // Update the last detected token if it's not a keyword (uses the DFAs)
            void update_last_detected_token_if_not_keyword();

            // Checks if the current prefix buffered corresponds to at least 1 pattern 
            // (1 posible token)
            bool is_current_prefix_a_lexem();  

            // Remove comments from the code before scanning it
            void remove_comments(std::string& input);

            // Checks if a string literal or char literal is being scanned
            bool is_scanning_string_or_char_literal();

            // Checks if a current prefix is not a lexem but it can be converted into a lexem
            // with more characters (like "12.34e" can be converted into a lexem if it's concatenated with "+2")
            bool is_a_longer_prefix_possible();
    };
};