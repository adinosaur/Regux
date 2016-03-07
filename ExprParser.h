//
// Created by dinosaur on 16-2-27.
//

#ifndef REGUX_EXPRPARSER_H
#define REGUX_EXPRPARSER_H


class ExprParser {
public:
    ExprParser(char* b, char* e);

protected:
    void match(char t);
    void print(char c);

    char* beg;
    char* end;
    char* lookahead;
};


#endif //REGUX_EXPRPARSER_H