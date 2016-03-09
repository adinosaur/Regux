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

    NFA ab_cd(&ab, &cd, 0);

    ab_cd.print();
    assert(ab_cd.match(buf2, buf2+2));
    return 0;
}