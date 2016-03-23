//
// Created by dinosaur on 16-3-13.
//

#include "Regux.h"

Regux::Regux(const std::string& str):
        Regux(str.c_str(), str.c_str() + str.size()) {
}

Regux::Regux(const char* b, const char* e) {
    Translate<NFAAction> translate(b, e);
    _nfa = translate.expr1();
}

bool Regux::match(const std::string& str) {
    const char* cp = str.c_str();
    return match(cp, cp + str.size());
}

bool Regux::match(const char* b, const char* e) {
    return _nfa.match(b, e);
}