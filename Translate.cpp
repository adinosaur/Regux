//
// Created by dinosaur on 16-3-5.
//

#include "Translate.h"
#include <ctype.h>

//
// 识别正则表达式: 或操作
//
void Translate::expr1() {
    expr2();
    while (true) {
        if (*lookahead == '|') {
            match('|');
            expr2();
            do_somethong('|');
            continue;
        }
        break;
    }
}

//
// 识别正则表达式: 与操作
//
void Translate::expr2() {
    expr3();
    while (true) {
        if (*lookahead == '&') {
            match('&');
            expr3();
            do_somethong('&');
            continue;
        }
        break;
    }
}

//
// 识别正则表达式: 克莱因闭包
//
void Translate::expr3() {
    term();
    while (true) {
        if (*lookahead == '*') {
            match('*');
            do_somethong('*');
            continue;
        }
        break;
    }
}

//
// 匹配字符或数字
//
void Translate::term() {
	if (*lookahead == '(') {
		match('(');
		expr1();
		match(')');
	}
    else if (isdigit(*lookahead) || isalpha(*lookahead)) {
        do_somethong(*lookahead);
        match(*lookahead);
    }
	else {
	}
}

//
// 语义动作
//
void Translate::do_somethong(char c) {
    print(c);
}