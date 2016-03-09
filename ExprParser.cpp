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
		std::cout << "syntax error!: expect '" << t << "' but input is '" << *lookahead << "'" << std::endl;
}

void ExprParser::print(char c) {
    std::cout << c;
}