//
// Created by dinosaur on 16-3-5.
//

#ifndef REGUX_NFA_H
#define REGUX_NFA_H

#include "MiniSet.h"
#include <unordered_map>
#include <vector>

const int NFA_OP_OR = 0;
const int NFA_OP_AND = 1;
const int NFA_OP_KLEENE = 2;

const int EPSILON = 256;
const int ALPHA_SIZE = 257;

class NFA {
public:
    typedef MiniSet SetType;

    // 友元函数
    friend NFA operator+(const NFA& n1, const NFA& n2);

    NFA();
    NFA(char input);
    NFA(NFA* n, int op);
    NFA(NFA* n1, NFA* n2, int op);

    SetType epsilon_closure(int s);
    SetType epsilon_closure(SetType s);
    SetType moveto(SetType s, char c);

    bool match(const char* b, const char* e);
    void print();

    // 引用技术
    int _reference_count;
private:
    typedef std::unordered_map<int, SetType> HashMap;

    void init();

    int statges_num;
    SetType final_statges;
    std::vector<HashMap> move;
};


#endif //REGUX_NFA_H
