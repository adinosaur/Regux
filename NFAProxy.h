//
// Created by dinosaur on 16-3-11.
// NFA代理
//

#ifndef REGUX_NFAPROXY_H
#define REGUX_NFAPROXY_H

#include "NFA.h"

//
// 带引用计数的NFA
//
class NFA_With_RefCnt : public NFA {
public:
    // 和父类NFA的构造函数完全相同
    NFA_With_RefCnt();
    NFA_With_RefCnt(char input);
    NFA_With_RefCnt(NFA_With_RefCnt* n, int op);
    NFA_With_RefCnt(NFA_With_RefCnt* n1, NFA_With_RefCnt* n2, int op);

    // 提供一个由NFA的显示转换函数
    explicit NFA_With_RefCnt(const NFA& n);

    // 引用计数
    int _reference_count = 1;
};

//
// NFA_With_RefCnt类的代理
//
class NFAProxy : public NFA_Const_Define {

    // 友元函数
    friend NFAProxy operator+(const NFAProxy& n1, const NFAProxy& n2);
    friend bool operator==(const NFAProxy& n1, const NFAProxy& n2);
    friend bool operator!=(const NFAProxy& n1, const NFAProxy& n2);

public:
    // 类型别称
    typedef NFA::SetType SetType;

public:
    NFAProxy();
    NFAProxy(const NFA_With_RefCnt& n);
    NFAProxy(char input);
    NFAProxy(const NFAProxy& n, int op);
    NFAProxy(const NFAProxy& n1, const NFAProxy& n2, int op);

    // 拷贝控制
    NFAProxy(const NFAProxy& n);
    NFAProxy& operator=(const NFAProxy& n);
    ~NFAProxy();

    SetType epsilon_closure(int s);
    SetType epsilon_closure(SetType s);
    SetType moveto(SetType s, char c);

    bool match(const char* b, const char* e);
    void print();

private:
    NFA_With_RefCnt* _nfa;
};

// NFAProxy空对象
extern NFAProxy NFAProxy_None;

#endif //REGUX_NFAPROXY_H
