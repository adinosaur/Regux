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
    int i, j, s = 0;
    typedef std::map<MiniSet, int> MapType;
    MapType Dstates;
    std::queue<MiniSet> Queue;

    MiniSet A = nfa.epsilon_closure(0);
    Dstates[A] = s++;
    Queue.push(A);

    while (!Queue.empty()) {
        MiniSet T = Queue.front();
        Queue.pop();

        move[Dstates[T]] = HashMap();

        for (int i = 0; i != NFA::ALPHA_SIZE; ++i) {
            MiniSet U = nfa.epsilon_closure(nfa.moveto(T, i));
            if (U.empty())
                continue;
            MapType::iterator end = Dstates.end();
            if (Dstates.find(U) == end) {
                Dstates[U] = s++;
                Queue.push(U);
            }

            move[i][j] = Dstates[U];
        }
    }
}

void DFA::print() {
    for (int i = 0; i != move.size(); ++i) {
        std::cout << i<< ": ";
        for (auto it : move[i]) {
            std::cout << "(" << it.first << "->";
            std::cout << it.second;
            std::cout << ")";
        }
        std::cout << std::endl;
    }
}