//
// Created by dinosaur on 16-3-6.
// 迷你整数集合，只能存放0-63范围内的小整数
//

#ifndef REGUX_MINISET_H
#define REGUX_MINISET_H

#include <sys/types.h>
#include <stdint.h>

class MiniSet {
public:
    static const int MAX = 63;
    static const int MIN = 0;

    // 友元重载
    friend bool operator==(const MiniSet& s1, const MiniSet& s2);
    friend bool operator!=(const MiniSet& s1, const MiniSet& s2);
    friend MiniSet operator|(const MiniSet& s1, const MiniSet& s2);
    friend MiniSet operator&(const MiniSet& s1, const MiniSet& s2);
    friend MiniSet operator<<(const MiniSet& s1, int i);

    // 成员重载
    MiniSet& operator<<=(int i);

    MiniSet();

    void insert(int v);
    void remove(int v);
    void clean();

    bool has(int v);
    bool empty();

    void print();
private:
    uint64_t _set;
};


#endif //REGUX_MINISET_H
