//
// Created by dinosaur on 16-3-5.
//

#include "Translate.h"
#include <iostream>

//
// NFA语义到动作：求并
//
NFAProxy NFAAction::Union(NFAProxy n1, NFAProxy n2) {
    std::cout << "|";
    return NFAProxy(n1, n2, NFAProxy::NFA_OP_OR);
}

//
// NFA语义到动作：连接
//
NFAProxy NFAAction::Connect(NFAProxy n1, NFAProxy n2) {
    return NFAProxy(n1, n2, NFAProxy::NFA_OP_AND);
}

//
// NFA语义到动作：克林闭包
//
NFAProxy NFAAction::Kleene(NFAProxy n) {
    std::cout << "*";
    return NFAProxy(n, NFAProxy::NFA_OP_KLEENE);
}

//
// NFA语义到动作：终结字符
//
NFAProxy NFAAction::Terminal(char c) {
    std::cout << c;
    return NFAProxy(c);
}