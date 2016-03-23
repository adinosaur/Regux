//
// Created by dinosaur on 16-3-5.
//

#ifndef REGUX_TRANSLATE_H
#define REGUX_TRANSLATE_H

#include "ExprParser.h"
#include "NFAProxy.h"

//
// 子类继承参数名和一系列接口函数
//
template <typename T>
class Action {
public:
    typedef T ActionReturnType;
    // 纯虚函数
    virtual T Union(T n1, T n2) = 0;
    virtual T Connect(T n1, T n2) = 0;
    virtual T Kleene(T n) = 0;
    virtual T Terminal(char c) = 0;
};

//
// NFA语义动作
//
class NFAAction : public Action<NFAProxy> {
public:
    // 实现接口
    NFAProxy Union(NFAProxy n1, NFAProxy n2);
    NFAProxy Connect(NFAProxy n1, NFAProxy n2);
    NFAProxy Kleene(NFAProxy n);
    NFAProxy Terminal(char c);
};

//
// 正则表达式翻译
// 模板参数T是一个Action类
//
template <typename T>
class Translate : public ExprParser
{
private:
    typedef typename T::ActionReturnType ActionReturnType;

public:

    Translate(const char* b, const char* e):
            ExprParser(b, e), _action(T()) { }

    //
    // 识别正则表达式: 或操作
    //
    ActionReturnType expr1() {
        ActionReturnType n1 = expr2();
        while (true) {
            if (*lookahead == '|') {
                match('|');
                ActionReturnType n2 = expr2();
                n1 = _action.Union(n1, n2);
                continue;
            }
            break;
        }
        return n1;
    }

private:
    //
    // 识别正则表达式: 与操作
    //
    ActionReturnType expr2() {
        ActionReturnType n1 = expr3();
        while (true) {
            // 为了支持省略正则连接操作，此处做特殊处理
            // 不符合预测分析文法
            if (is_terminal_flag(*lookahead)) {
                ActionReturnType n2 = expr3();
                n1 = _action.Connect(n1, n2);
                continue;
            }
            break;
        }
        return n1;
    }

    //
    // 识别正则表达式: 克莱因闭包
    //
    ActionReturnType expr3() {
        ActionReturnType n = term();
        while (true) {
            if (*lookahead == '*') {
                match('*');
                n = _action.Kleene(n);
                continue;
            }
            break;
        }
        return n;
    }

    //
    // 匹配字符或数字,或者识别出括号表达式
    //
    ActionReturnType term() {
        if (*lookahead == '(') {
            match('(');
            ActionReturnType n = expr1();
            match(')');
            return n;
        }

        if (isdigit(*lookahead) || isalpha(*lookahead)) {
            ActionReturnType n = _action.Terminal(*lookahead);
            match(*lookahead);
            return n;
        }
    }

    //
    // 判断字符是否可以终止
    //
    bool is_terminal_flag(char c) {
        return c == '(' || isdigit(c) || isalpha(c);
    }

private:
    T _action;
};

#endif

