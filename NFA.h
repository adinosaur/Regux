//
// Created by dinosaur on 16-3-5.
//

#ifndef REGUX_NFA_H
#define REGUX_NFA_H

#include "MiniSet.h"

const int NFA_OP_OR = 0;
const int NFA_OP_AND = 1;
const int NFA_OP_KLEENE = 2;
const int NFA_OP_MEGRE = 3;

const int EPSILON = 256;
const int ALPHA_SIZE = 257;

class NFA {
public:
    typedef MiniSet SetType;

    NFA(char input);
    NFA(NFA* n, int op);
    NFA(NFA* n1, NFA* n2, int op);
    ~NFA();

    SetType epsilon_closure(int s);
    SetType epsilon_closure(SetType s);

    SetType moveto(SetType s, char c);

    bool match(char* b, char* e);
    void print();

private:
    int statges_num;
    SetType final_statges;
    SetType** move;
};


#endif //REGUX_NFA_H
