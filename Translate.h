//
// Created by dinosaur on 16-3-5.
//

#ifndef REGUX_TRANSLATE_H
#define REGUX_TRANSLATE_H

#include "ExprParser.h"

class Translate : public ExprParser
{
public:
    Translate(char* b, char* e):
            ExprParser(b, e) { }

    void expr1();
    void expr2();
    void expr3();
    void term();

    void do_somethong(char c);
};

#endif

