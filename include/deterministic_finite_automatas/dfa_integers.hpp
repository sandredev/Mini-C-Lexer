#pragma once

#include "dfa.hpp"

namespace mini_c_lexer {
    class DFAIntegers : public DFA {
        public:
            DFAIntegers();         
            void do_transition(char& input) override;
            bool is_lexem() const override;
            void test() override;
    };
};