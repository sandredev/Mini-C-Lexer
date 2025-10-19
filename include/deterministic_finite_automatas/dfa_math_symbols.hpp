#pragma once

#include "dfa.hpp"
#include <string>

namespace mini_c_lexer {
    class DFAMathSymbols : public DFA {
        public:
            DFAMathSymbols();         
            void do_transition(char& input) override;
            bool is_lexem() const override;
            void test() override;
            std::string which_token_is();
    };
};