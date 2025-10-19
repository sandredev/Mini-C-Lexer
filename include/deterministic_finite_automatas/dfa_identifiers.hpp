#pragma once

#include "dfa.hpp"

namespace mini_c_lexer {
    class DFAIdentifiers : public DFA {
        public:
            DFAIdentifiers();
            void do_transition(char& input) override;
            void test() override;
            bool is_lexem() const override;
    };
};