//
// Created by dinosaur on 16-2-27.
//

#ifndef REGUX_EXPRPARSER_H
#define REGUX_EXPRPARSER_H


class ExprParser {
public:
    ExprParser(const char* b, const char* e);

protected:
    void match(char t);
    void print(char c);

    const char* beg;
    const char* end;
    const char* lookahead;
};


#endif //REGUX_EXPRPARSER_H