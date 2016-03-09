#include "Translate.h"
#include "MiniSet.h"
#include "NFA.h"
#include <iostream>
#include <assert.h>

using namespace std;

int main()
{
	/*
    char buf1[] = "ab";
    char buf2[] = "cd";
	
    NFA a('a');
    NFA b('b');
    NFA c('c');
    NFA d('d');

    NFA ba(&b, &a, 1);
    NFA cd(&c, &d, 1);

    ba.print();
    cd.print();
	*/

	char buf3[] = "(a|b)*&b";
	Translate translate(buf3, buf3 + 8); 
	translate.expr1();
    return 0;
}