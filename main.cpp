#include "Regux.h"
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

int main()
{
    string s1 = "caacd";
    string s2 = "(a|b)*cd";

    Regux re(s2);
    assert(re.match(s1));

    return 0;
}
