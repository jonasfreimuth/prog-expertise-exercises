# include <stdio.h>

int rec_pwr_2(int x) {

    if (x == 0) {

        return (1);

    } else if (x <= 1) {

        return (2);

    } else {

        x = 2 * rec_pwr_2(x - 1);

    }

    return (x);

}

int main() {

    int input, out;

    printf("Enter which power of two you want: ");
    scanf("%d", &input);

    out = rec_pwr_2(input);

    printf("\n2 to the power of %d is %d.\n", input, out);

    return (0);

}