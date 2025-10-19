#pragma once

#include "dfa.hpp"
#include <string>

namespace mini_c_lexer {
    class DFAPointNumbers : public DFA {
        public:
            DFAPointNumbers();         
            void do_transition(char& input) override;
            bool is_lexem() const override;
            void test() override;
            std::string which_token_is();
    };
};