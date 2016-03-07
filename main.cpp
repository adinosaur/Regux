#include "Translate.h"
#include "MiniSet.h"
#include "NFA.h"
#include <iostream>
#include <assert.h>

using namespace std;

int main()
{
    char buf1[] = "ab";
    char buf2[] = "cd";

    NFA a('a');
    NFA b('b');
    NFA c('c');
    NFA d('d');

    NFA ab(&a, &b, 1);
    NFA cd(&c, &d, 1);
    assert(cd.match(buf2, buf2+2));

    NFA ab_or_cd(&ab, &cd, 3);
    ab_or_cd.print();
    assert(ab_or_cd.match(buf2, buf2+2));

//    NFA ba(&b, &a, 1);
//
//    NFA aaba(&ab, &ba, 1);
//
//    aaba.print();
    //assert(aaba.match(buf, buf+sizeof(buf)));
    return 0;
}