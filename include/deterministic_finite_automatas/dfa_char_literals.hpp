#pragma once

#include "dfa.hpp"
#include <string>

namespace mini_c_lexer {
    class DFACharLiterals : public DFA {
        public:
            DFACharLiterals();         
            void do_transition(char& input) override;
            bool is_lexem() const override;
            void test() override;
            std::string which_token_is() override;
            bool is_scanning_char_literal();
    };
};