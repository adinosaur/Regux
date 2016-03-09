#include "Translate.h"
#include "MiniSet.h"
#include "NFA.h"
#include <iostream>
#include <assert.h>

using namespace std;

int main()
{
    char buf3[] = "(a|b)*&b";
    Translate translate(buf3, buf3 + 8); 
    translate.expr1();
    return 0;
}
