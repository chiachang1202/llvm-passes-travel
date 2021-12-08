#include <stdio.h>

int foo(int a) {
    return a + 1;
}

int bar(int b) {
    return b + 2;
}

int main() {

    int c = foo(1) + bar(2);

    return c;
}