#include <stdio.h>

int int_multiply(int a, int b, int c) {
    int res;

    res = a * b * c;

    return(res);
}

int main() {
    int a, b, c, res;

    a = 2;

    b = 5;

    c = 13;

    res = int_multiply(a, b, c);

    printf("Product of %d, %d, %d is %d. \n", a, b, c, res);

    return(0);
}