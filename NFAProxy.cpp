//
// Created by dinosaur on 16-3-11.
//

#include "NFAProxy.h"

// NFAProxy空对象
NFAProxy NFAProxy_None;

// NFA_With_RefCnt构造函数
NFA_With_RefCnt::NFA_With_RefCnt(): NFA()
{

}

// NFA_With_RefCnt构造函数
NFA_With_RefCnt::NFA_With_RefCnt(char input):NFA(input)
{

}

// NFA_With_RefCnt构造函数
NFA_With_RefCnt::NFA_With_RefCnt(NFA_With_RefCnt* n, int op):NFA(n, op)
{

}

// NFA_With_RefCnt构造函数
NFA_With_RefCnt::NFA_With_RefCnt(NFA_With_RefCnt* n1, NFA_With_RefCnt* n2, int op):NFA(n1, n2, op)
{

}

// 构造函数，显示转换接口
NFA_With_RefCnt::NFA_With_RefCnt(const NFA& n):NFA(n)
{

}

//
// 友元函数
// todo: 还未测试
//
NFAProxy operator+(const NFAProxy& n1, const NFAProxy& n2) {
    NFA n = *(n1._nfa) + *(n1._nfa);
    return NFA_With_RefCnt(n);
}

// 相等性测试
bool operator==(const NFAProxy& n1, const NFAProxy& n2) {
    return n1._nfa == n2._nfa;
}

// 不等性测试
bool operator!=(const NFAProxy& n1, const NFAProxy& n2) {
    return !(n1 == n2);
}

// 不带参数的构造函数，NFAProxy对象内置指针初始为空指针
NFAProxy::NFAProxy():
        _nfa(nullptr) {
}

NFAProxy::NFAProxy(const NFA_With_RefCnt& n):
        _nfa(new NFA_With_RefCnt(n)) {
}

NFAProxy::NFAProxy(char input):
        _nfa(new NFA_With_RefCnt(input)) {
}

NFAProxy::NFAProxy(const NFAProxy& n, int op):
        _nfa(new NFA_With_RefCnt(n._nfa, op)) {
}

NFAProxy::NFAProxy(const NFAProxy& n1, const NFAProxy& n2, int op):
        _nfa(new NFA_With_RefCnt(n1._nfa, n2._nfa, op)) {
}

NFAProxy::NFAProxy(const NFAProxy& n):
        _nfa(n._nfa) {
    _nfa->_reference_count++;
}

NFAProxy& NFAProxy::operator=(const NFAProxy& n) {
    if (&n == this)
        return *this;

    NFA_With_RefCnt* temp = _nfa;
    _nfa = n._nfa;
    _nfa->_reference_count++;
    if (temp && --temp->_reference_count == 0)
        delete temp;
}

NFAProxy::~NFAProxy() {
    if (_nfa && --_nfa->_reference_count == 0) {
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

