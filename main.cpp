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

	NFA ba(&b, &a, 1);
	NFA cd(&c, &d, 1);

	assert(ba.match(buf1, buf1+2));
    return 0;
}