#pragma once

#include <string>
#include "deterministic_finite_automatas/dfa_identifiers.hpp"
#include "deterministic_finite_automatas/dfa_integers.hpp"

namespace mini_c_lexer {
    class Scanner { 
        private:
            std::string prefix;
            DFAIdentifiers dfa_identifiers;
            DFAIntegers dfa_integers;
            bool is_matching;
        public:
            Scanner();
            void scan(std::string& input);
    };
};