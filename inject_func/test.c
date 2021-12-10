
#include "test.h"
#include <stdio.h>

int foo(int a) {
    return a + 1;
}

int bar(int b) {
    return b + 2;
}

int main() {

    int c, d, e, f, g;

    c = foo(1);
    d = bar(2);
    e = bar(3);
    f = foo(4);
    
    g = baz(e, f);

    return f;
}