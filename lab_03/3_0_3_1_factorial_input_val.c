# include <stdio.h>

int factorial(int x) {

    if (x <= 1) {

        return (1);

    } else if (x <= 2) {

        return (x);

    } else {

        x = x * factorial(x - 1);

    }

    return (x);

}

int main() {

    int input, out;

    printf("Enter number to be factorialised: ");
    scanf("%d", &input);

    out = factorial(input);

    printf("\n%d factorial is %d.\n", input, out);

    return (0);

}