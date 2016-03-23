//
// Created by dinosaur on 16-3-5.
//

#ifndef REGUX_NFA_H
#define REGUX_NFA_H

#include "MiniSet.h"
#include <unordered_map>
#include <vector>

//
// 常量定义类
//
struct NFA_Const_Define {
    // 静态成员
    static const int NFA_OP_OR;
    static const int NFA_OP_AND;
    static const int NFA_OP_KLEENE;
    static const int EPSILON;
    static const int ALPHA_SIZE;
};

//
// 非确定性有限状态自动机
//
class NFA : public NFA_Const_Define {

    // 友元函数
    friend NFA operator+(const NFA& n1, const NFA& n2);

public:
    // 类型别名
    typedef MiniSet SetType;
    typedef std::unordered_map<int, SetType> HashMap;

public:

    NFA();
    NFA(char input);
    NFA(NFA* n, int op);
    NFA(NFA* n1, NFA* n2, int op);

    SetType epsilon_closure(int s);
    SetType epsilon_closure(SetType s);
    SetType moveto(SetType s, char c);

    bool match(const char* b, const char* e);
    void print();

private:
    void init();

private:
    int statges_num;
    SetType final_statges;
    std::vector<HashMap> move;
};


#endif //REGUX_NFA_H
