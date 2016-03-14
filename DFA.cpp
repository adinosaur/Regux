//
// Created by dinosaur on 16-3-13.
//

#include "DFA.h"
#include "NFA.h"

#include <map>
#include <queue>
#include <iostream>

DFA::DFA(NFA& nfa) {
    subset_construction(nfa);
}

//
// 子集构造法
//
void DFA::subset_construction(NFA& nfa) {
    int s = 0;
    std::map<MiniSet, int> Dstates;
    std::queue<MiniSet> Queue;

    MiniSet A = nfa.epsilon_closure(0);
    Dstates[A] = s++;
    Queue.push(A);

    while (!Queue.empty()) {
        MiniSet T = Queue.front();
        Queue.pop();

        move[Dstates[T]] = HashMap();

        for (int i = 0; i != ALPHA_SIZE; ++i) {
            MiniSet U = nfa.epsilon_closure(nfa.moveto(T, i));
            if (U.empty())
                continue;

            std::map<MiniSet,int>::iterator end = Dstates.end();
            if (Dstates.find(U) == end) {
                Dstates[U] = s++;
                Queue.push(U);
            }
            move[Dstates[T]][i] = Dstates[U];
        }
    }
}

void DFA::print() {
    for (auto i : move) {
        std::cout << i.first << ": ";
        for (auto it : i.second) {
            std::cout << "(" << it.first << "->";
            std::cout << it.second;
            std::cout << ")";
        }
        std::cout << std::endl;
    }
}