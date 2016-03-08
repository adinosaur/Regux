//
// Created by dinosaur on 16-3-6.
//

#include "MiniSet.h"
#include <assert.h>
#include <iostream>

const uint64_t ONE = 1;

//
// 友元函数，相等性判断
//
bool operator==(const MiniSet& s1, const MiniSet& s2) {
    return s1._set == s2._set;
}

//
// 友元函数，集合求并
//
MiniSet operator|(const MiniSet& s1, const MiniSet& s2) {
    MiniSet s;
    s._set = s1._set | s2._set;
    return s;
}

//
// 友元函数，集合求交
//
MiniSet operator&(const MiniSet& s1, const MiniSet& s2) {
    MiniSet s;
    s._set = s1._set & s2._set;
    return s;
}

//
// 集合左移
//
MiniSet operator<<(const MiniSet& s1, int i) {
	MiniSet s;
	if (i > 0) {
		s._set <<= i;
		assert(s._set > s1._set);
	}
	return s;
}

MiniSet::MiniSet(): _set(0) {
}

void MiniSet::insert(int v) {
    assert(v >= MiniSet::MIN && v <= MiniSet::MAX);
	_set |= (ONE << v);
}

void MiniSet::remove(int v) {
    assert(v >= MiniSet::MIN && v <= MiniSet::MAX);
	_set &= !(ONE << v);
}

bool MiniSet::has(int v) {
    assert(v >= MiniSet::MIN && v <= MiniSet::MAX);
	return _set & (ONE << v);
}

bool MiniSet::empty() {
    return _set == 0;
}

void MiniSet::clean() {
    _set = 0;
}

void MiniSet::print() {
    std::cout << "[";
    for (int i = MiniSet::MIN; i != MiniSet::MAX; ++i)
    {
        if (has(i))
            std::cout << i << ",";
    }
    std::cout << "]";
}