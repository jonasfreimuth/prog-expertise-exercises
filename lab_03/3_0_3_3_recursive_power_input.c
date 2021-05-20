# include <stdio.h>

int rec_pwr_base(int pwr, int base) {

    if (pwr == 0) {

        return (1);

    } else if (pwr <= 1) {

        return (base);

    } else {

        pwr = base * rec_pwr_base(pwr - 1, base);

    }

    return (pwr);

}

int main() {

    int in_1, in_2, out;

    printf("Enter number of powers and the base: ");
    scanf("%d %d", &in_1, &in_2);

    out = rec_pwr_base(in_1, in_2);

    printf("\n%d to the power of %d is %d.\n", in_2, in_1, out);

    return (0);

}