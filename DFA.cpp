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
	typedef std::unordered_map<MiniSet, int, hash_miniset> MapType;
	MapType Dstates;
    std::queue<MiniSet> Queue;

    MiniSet A = nfa.epsilon_closure(0);
    Dstates[A] = s++;
    Queue.push(A);

    while (!Queue.empty()) {
        MiniSet T = Queue.front();
        Queue.pop();

		move.push_back(HashMap());
		i = move.size() - 1;
        for (j = 0; j != ALPHA_SIZE; ++j) {
            MiniSet U = nfa.epsilon_closure(nfa.moveto(T, j));
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