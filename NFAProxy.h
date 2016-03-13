//
// Created by dinosaur on 16-3-11.
// NFA代理
//

#ifndef REGUX_NFAPROXY_H
#define REGUX_NFAPROXY_H

#include "NFA.h"

class NFAProxy {
public:
    typedef NFA::SetType SetType;

    // 友元函数
    friend NFAProxy operator+(const NFAProxy& n1, const NFAProxy& n2);

    NFAProxy();
    NFAProxy(const NFA& n);
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
    NFA* _nfa;
};


#endif //REGUX_NFAPROXY_H
