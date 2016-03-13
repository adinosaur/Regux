//
// Created by dinosaur on 16-3-13.
//

#include "DFA.h"
#include "NFA.h"
#include "MiniSet.h"
#include <unordered_set>
#include <queue>
#include <iostream>

DFA::DFA(NFA& nfa) {
    subset_construction(nfa);
}

void DFA::subset_construction(NFA& nfa) {
    std::unordered_set<MiniSet> Dstates;
    std::queue<MiniSet> Queue;

    MiniSet A = nfa.epsilon_closure(0);
    Dstates.insert(A);
    Queue.push(A);

    while (!Queue.empty()) {
        MiniSet T = Queue.front();
        Queue.pop();

        move.push_back(HashMap());

        for (int i = 0; i != ALPHA_SIZE; ++i) {
            MiniSet U = nfa.epsilon_closure(nfa.moveto(T, i));
            std::unordered_set<MiniSet>::iterator end = Dstates.end();
            if (Dstates.find(U) != end) {
                Dstates.insert(U);
                Queue.push(U);
            }

            move.back()[i] = U;
        }
    }
}

void DFA::print() {
    for (int i = 0; i != move.size(); ++i) {
        std::cout << i << ": ";
        for (auto it : move[i]) {
            std::cout << "(" << it.first << "->";
            it.second.print();
            std::cout << ")";
        }
        std::cout << std::endl;
    }
}