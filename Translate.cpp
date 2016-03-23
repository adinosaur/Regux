//
// Created by dinosaur on 16-3-5.
//

#include "Translate.h"
#include <assert.h>
#include <ctype.h>

//
// 识别正则表达式: 或操作
//
NFAProxy Translate::expr1() {
    NFAProxy n1 = expr2();
    while (true) {
        if (*lookahead == '|') {
            match('|');
            NFAProxy n2 = expr2();
            n1 = do_somethong('|', n1, n2);
            continue;
        }
        break;
    }
    return n1;
}

//
// 识别正则表达式: 与操作
//
NFAProxy Translate::expr2() {
    NFAProxy n1 = expr3();
    while (true) {
        // 为了支持省略正则连接操作，此处做特殊处理
        // 不符合预测分析文法
        if (is_terminal_flag(*lookahead)) {
            NFAProxy n2 = expr3();
            n1 = do_somethong('&', n1, n2);
            continue;
        }
        break;
    }
    return n1;
}

//
// 识别正则表达式: 克莱因闭包
//
NFAProxy Translate::expr3() {
    NFAProxy n = term();
    while (true) {
        if (*lookahead == '*') {
            match('*');
            n = do_somethong('*', n, NFAProxy());
            continue;
        }
        break;
    }
    return n;
}

//
// 匹配字符或数字,或者识别出括号表达式
//
NFAProxy Translate::term() {
    if (*lookahead == '(') {
        match('(');
        NFAProxy n = expr1();
        match(')');
        return n;
    }

    if (isdigit(*lookahead) || isalpha(*lookahead)) {
        NFAProxy n = do_somethong(*lookahead, NFAProxy(), NFAProxy());
        match(*lookahead);
        return n;
    }
}

//
// 语义动作
//
NFAProxy Translate::do_somethong(char c, NFAProxy n1, NFAProxy n2) {
    print(c);
    NFAProxy n;
    switch (c) {
        // 或操作
        case '|':
            assert(n1 != NFAProxy_None);
            assert(n2 != NFAProxy_None);
            n = NFAProxy(n1, n2, NFAProxy::NFA_OP_OR);
            break;
        // 与操作
        case '&':
            assert(n1 != NFAProxy_None);
            assert(n2 != NFAProxy_None);
            n = NFAProxy(n1, n2, NFAProxy::NFA_OP_AND);
            break;
        // 克林闭包
        case '*':
            assert(n1 != NFAProxy_None);
            assert(n2 == NFAProxy_None);
            n = NFAProxy(n1, NFAProxy::NFA_OP_KLEENE);
            break;
        // 终结节点
        default:
            assert(n1 == NFAProxy_None);
            assert(n2 == NFAProxy_None);
            n = NFAProxy(c);
            break;
    }
    return n;
}

//
// 判断字符是否可以终止
//
bool Translate::is_terminal_flag(char c) {
    return c == '(' || isdigit(c) || isalpha(c);
}