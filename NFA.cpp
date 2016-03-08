//
// Created by dinosaur on 16-3-5.
//

#include "NFA.h"
#include <stack>
#include <iostream>

//
// 单个字符的NFA
//
NFA::NFA(char input) {
    statges_num = 2;
    final_statges.insert(statges_num - 1);

    // 申请内存
    move = new SetType*[statges_num];
    for (int i = 0; i != statges_num; ++i)
        move[i] = new SetType[ALPHA_SIZE];

    move[0][input].insert(1);
}

//
// NFA克林闭包
//
NFA::NFA(NFA* n, int op) {
    switch (op) {
        case NFA_OP_KLEENE:
            statges_num = n->statges_num + 2;
            // 终结状态集合
            final_statges.insert(statges_num - 1);

            // 申请内存
            move = new SetType*[statges_num];
            for (int i = 0; i != statges_num; ++i)
                move[i] = new SetType[ALPHA_SIZE];

            // 转移表
            move[0][EPSILON].insert(1);
            move[0][EPSILON].insert(n->statges_num + 1);

            for (int i = 0; i != n->statges_num; ++i)
                for (int j = 0; j != ALPHA_SIZE; ++j)
                    for (int k = SetType::MIN; k != SetType::MAX; ++k)
                        if (n->move[i][j].has(k))
                            move[i+1][j].insert(k+1);

            move[n->statges_num][EPSILON].insert(1);
            move[n->statges_num][EPSILON].insert(n->statges_num + 1);

            break;
    }
}

//
// NFA连接和或操作
//
NFA::NFA(NFA* n1, NFA* n2, int op) {
    int statges_num1 = n1->statges_num;
    int statges_num2 = n2->statges_num;

    switch (op) {
        case NFA_OP_OR:
            statges_num = n1->statges_num + n2->statges_num + 2;
            break;
        case NFA_OP_AND:
            statges_num = n1->statges_num + n2->statges_num - 1;
            break;
        case NFA_OP_MEGRE:
            statges_num = n1->statges_num + n2->statges_num + 1;
    }

    // 申请内存
    move = new SetType*[statges_num];
    for (int i = 0; i != statges_num; ++i)
        move[i] = new SetType[ALPHA_SIZE];

    switch (op) {
        case NFA_OP_OR:
            // 终结状态
            final_statges.insert(statges_num - 1);
            // 转移表
            move[0][EPSILON].insert(1);
            move[0][EPSILON].insert(statges_num1 + 1);

            for (int i = 0; i != statges_num1; ++i)
                for (int j = 0; j != ALPHA_SIZE; ++j)
                    for (int k = SetType::MIN; k != SetType::MAX; ++k)
                        if (n1->move[i][j].has(k))
                            move[i+1][j].insert(k+1);

            move[statges_num1][EPSILON].insert(statges_num1 + statges_num2 + 1);

            for (int i = 0; i != statges_num2; ++i)
                for (int j = 0; j != ALPHA_SIZE; ++j)
                    for (int k = SetType::MIN; k != SetType::MAX; ++k)
                        if (n1->move[i][j].has(k))
                            move[i+statges_num1+1][j].insert(k + statges_num1 + 1);

            move[statges_num1 + statges_num2][EPSILON].insert(statges_num1 + statges_num2 + 1);

            break;

        case NFA_OP_AND:
            // 终结状态
            final_statges.insert(statges_num - 1);
            // 转移表
            for (int i = 0; i != statges_num1; ++i)
                for (int j = 0; j != ALPHA_SIZE; ++j)
                    move[i][j] = n1->move[i][j];

            for (int i = 0; i != statges_num2; ++i)
                for (int j = 0; j != ALPHA_SIZE; ++j)
                    for (int k = SetType::MIN; k != SetType::MAX; ++k)
                        if (n2->move[i][j].has(k))
                            move[i+statges_num1-1][j].insert(k + statges_num2 - 1);

            break;

        case NFA_OP_MEGRE:
            // 终结状态
            final_statges.insert(statges_num1);
            final_statges.insert(statges_num1 + statges_num2);
            // 转移表
            move[0][EPSILON].insert(1);
            move[0][EPSILON].insert(statges_num1 + 1);

            for (int i = 0; i != statges_num1; ++i)
                for (int j = 0; j != ALPHA_SIZE; ++j)
                    for (int k = SetType::MIN; k != SetType::MAX; ++k)
                        if (n1->move[i][j].has(k))
                            move[i+1][j].insert(k+1);

            for (int i = 0; i != statges_num2; ++i)
                for (int j = 0; j != ALPHA_SIZE; ++j)
                    for (int k = SetType::MIN; k != SetType::MAX; ++k)
                        if (n2->move[i][j].has(k))
                            move[i+statges_num1+1][j].insert(k + statges_num1 + 1);
            break;
    }
}

NFA::~NFA() {
    for (int i = 0; i != statges_num; ++i)
        delete[] move[i];
    delete[] move;
}

//
// 计算一个状态的epsilon闭包
//
NFA::SetType NFA::epsilon_closure(int statge) {
    SetType s = move[statge][EPSILON];
    s.insert(statge);
    return epsilon_closure(s);
}

//
// 计算一个状态集合的epsilon闭包
//
NFA::SetType NFA::epsilon_closure(SetType set) {
    SetType final_set = set;
    std::stack<int> statges_stack;
    for (int i = SetType::MIN; i != SetType::MAX; ++i)
        if (final_set.has(i))
            statges_stack.push(i);

    int temp_statge;
    SetType temp_set;
    while (!statges_stack.empty()) {
        temp_statge = statges_stack.top();
        statges_stack.pop();
        temp_set = move[temp_statge][EPSILON];
        for (int u = SetType::MIN; u != SetType::MAX; ++u)
            if (temp_set.has(u) && !final_set.has(u)) {
                final_set.insert(u);
                statges_stack.push(u);
            }
    }

    return final_set;
}

//
// 计算一个状态集合在接收一个输入所得到的状态集合
//
NFA::SetType NFA::moveto(SetType s, char c) {
    SetType final_set;
    SetType temp_set;
    for (int i = SetType::MIN; i != SetType::MAX; ++i)
    {
        if (!s.has(i))
            continue;

        temp_set = move[i][c];
        for (int j = SetType::MIN; j != SetType::MAX; ++j)
            if (temp_set.has(j))
                final_set.insert(j);
    }
    return final_set;
}

//
// 匹配字符串
//
bool NFA::match(char* b, char* e) {
    SetType set = epsilon_closure(0);
    char* cp = b;
    while (cp != e) {
        SetType s = moveto(set, *cp);
        set = epsilon_closure(moveto(set, *cp));
        cp++;
    }

    SetType cross = set & final_statges;
    return !cross.empty();
}

void NFA::print() {
    for (int i = 0; i != statges_num; ++i) {
		std::cout << i << ": ";
        for (int j = 0; j != ALPHA_SIZE; ++j) {
			move[i][j].print();
        }
        std::cout << std::endl;
    }

    std::cout << "Final:";
    final_statges.print();
    std::cout << std::endl;
}