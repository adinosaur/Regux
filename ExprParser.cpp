//
// Created by dinosaur on 16-3-5.
//

#include "ExprParser.h"
#include <iostream>

ExprParser::ExprParser(char* b, char* e):
        beg(b),
        end(e),
        lookahead(b) { }

void ExprParser::match(char t) {
    if (*lookahead == t && lookahead < end)
        lookahead++;
    else
        std::cout << "语法错误!" << std::endl;
}

void ExprParser::print(char c) {
    std::cout << c;
}