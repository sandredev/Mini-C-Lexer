#pragma once

#include <vector>

namespace mini_c_lexer {
    // Abstract class that represents a DFA
    class DFA { 
        protected:
            int current_state;             

            /* 
               Table of transitions where each column (except the last) is an input and
               each row is an state.

               The last column says if an state is of acceptance or not.
            */
            std::vector<std::vector<int>> transitions_table;

        public:
            DFA();

            // Transitionates from an state to another one according to an input
            virtual void do_transition(char& input) = 0;

            // Says if the current input is accepted by the DFA
            virtual bool is_lexem() const = 0;

            // Method used for testing DFAs
            virtual void test() = 0;

            // I don't know why this is important yet
            virtual ~DFA();

            virtual void restartDFA();
    };
}