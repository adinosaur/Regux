//
// Created by dinosaur on 16-3-11.
//

#include "NFAProxy.h"

//
// 友元函数
// todo: 还未测试
//
NFAProxy operator+(const NFAProxy& n1, const NFAProxy& n2) {
    NFA n = *(n1._nfa) + *(n1._nfa);
    return n;
}

NFAProxy::NFAProxy():
        _nfa(nullptr) {
}

NFAProxy::NFAProxy(const NFA& n):
        _nfa(new NFA(n)) {
}

NFAProxy::NFAProxy(char input):
        _nfa(new NFA(input)) {
}

NFAProxy::NFAProxy(const NFAProxy& n, int op):
        _nfa(new NFA(n._nfa, op)) {
}

NFAProxy::NFAProxy(const NFAProxy& n1, const NFAProxy& n2, int op):
        _nfa(new NFA(n1._nfa, n2._nfa, op)) {
}

NFAProxy::NFAProxy(const NFAProxy& n):
        _nfa(n._nfa) {
    _nfa->_reference_count++;
}

NFAProxy& NFAProxy::operator=(const NFAProxy& n) {
    if (&n == this)
        return *this;

    NFA* temp = _nfa;
    _nfa = n._nfa;
    _nfa->_reference_count++;
    if (temp && --temp->_reference_count == 0)
        delete temp;
}

NFAProxy::~NFAProxy() {
    if (--_nfa->_reference_count == 0) {
        delete _nfa;
    }
}

NFAProxy::SetType NFAProxy::epsilon_closure(int s) {
    return _nfa->epsilon_closure(s);
}

NFAProxy::SetType NFAProxy::epsilon_closure(SetType s) {
    return _nfa->epsilon_closure(s);
}

NFAProxy::SetType NFAProxy::moveto(SetType s, char c) {
    return _nfa->moveto(s, c);
}

bool NFAProxy::match(const char* b, const char* e) {
    return _nfa->match(b, e);
}

void NFAProxy::print() {
    _nfa->print();
}

