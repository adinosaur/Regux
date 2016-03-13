//
// Created by dinosaur on 16-3-13.
//

#ifndef REGUX_REGUX_H
#define REGUX_REGUX_H

#include "Translate.h"
#include "NFAProxy.h"
#include <string>

class Regux {
public:
    Regux(const std::string& str);
    Regux(const char* b, const char* e);

    bool match(const std::string& str);
    bool match(const char*b, const char* e);
private:
    NFAProxy _nfa;
};


#endif //REGUX_REGUX_H
