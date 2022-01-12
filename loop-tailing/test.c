#include <stdio.h>

int main() {
    int A[20], B[20], C[20];
    
    for (int i = 0; i < 3; ++i) {
        B[i] = A[i];
        C[i] = B[i];
        printf("%d\n", i);
    }
}