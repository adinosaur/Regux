//
// Created by dinosaur on 16-3-5.
//

#ifndef REGUX_TRANSLATE_H
#define REGUX_TRANSLATE_H

#include "ExprParser.h"
#include "NFAProxy.h"

class Translate : public ExprParser
{
public:
    Translate(const char* b, const char* e):
            ExprParser(b, e) { }

    NFAProxy expr1();

private:
    NFAProxy expr2();
    NFAProxy expr3();
    NFAProxy term();

    void do_somethong(char c);
    bool is_terminal_flag(char c);
};

#endif

