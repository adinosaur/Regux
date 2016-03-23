//
// Created by dinosaur on 16-3-13.
//

#ifndef REGUX_DFA_H
#define REGUX_DFA_H

#include "MiniSet.h"
#include <unordered_map>
#include <vector>

class NFA;

class DFA {
public:
    DFA(NFA& nfa);

    bool match(const char* b, const char* e);

    void print();
private:

    // 子集构造法
    void subset_construction(NFA& nfa);
    typedef std::unordered_map<int, int> HashMap;

    //MiniSet final_statge;
    std::vector<HashMap> move;
};


#endif //REGUX_DFA_H
