# include <stdio.h>

int main() {

    int i, max_i;

    max_i = 100;

    for (i = 1; i <= max_i; i += 10) {

        int j;

        for (j = 0; j <= 9; j ++) {
            printf("%i", j + i);

            if (i+j < max_i) {
                printf(", ");
            }

        }

        printf("\n");
    }

    return(0);
}