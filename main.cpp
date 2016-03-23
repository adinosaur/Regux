#include "Regux.h"
#include "DFA.h"
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

int main()
{
    string s1 = "bbbbbbbcd";
    string s2 = "(a|b)*cd";

    Regux re(s2);
    assert(re.match(s1));

//    NFA n1('a');
//    NFA n2('b');
//    NFA n3(&n1, &n2, 1);
//
//
//    DFA d1(n1);
//    d1.print();
    return 0;
}
