//
// Created by dinosaur on 16-3-6.
// 迷你整数集合，只能存放0-63范围内的小整数
//

#ifndef REGUX_MINISET_H
#define REGUX_MINISET_H

#include <sys/types.h>
#include <stdint.h>
#include <functional>

//
// 适用于存放自动机状态的集合
// 目前集合仅支持插入64个元素
//
class MiniSet {
public:

    static const int MAX = 63;
    static const int MIN = 0;
	// 友元类
	friend class hash_miniset;

    // 友元重载
    friend bool operator==(const MiniSet& s1, const MiniSet& s2);
    friend bool operator!=(const MiniSet& s1, const MiniSet& s2);
    friend bool operator<(const MiniSet& s1, const MiniSet& s2);
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

//
// MiniSet类的Hash函数对象
//
struct hash_miniset {
	size_t operator()(const MiniSet& s) {
		// 这里有可能存在截断问题
		const unsigned long* p = reinterpret_cast<const unsigned long*>(&s._set);
		return std::hash<unsigned long>()(*p);
	}
};

#endif //REGUX_MINISET_H
