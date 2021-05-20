# include <stdio.h>
# include "3_0_4_2_a_is_upper.c"

int main() {

    int i, n_letters;
    static int upper_count, lower_count;
    char input;

    n_letters = 10;

    printf("Enter your letter: \n");

    for (i = 0; i < n_letters; i ++) {

        printf("\nLetter %d:", i + 1);
        scanf(" %1c", &input);

        printf("Letter is %c.", input);

        if (is_upper(input) == 0) {
            upper_count ++;
        } else if (is_upper(input) == 1) {
            lower_count ++;
        } else {
            printf("\nI have no idea what you just typed...\n");
        }

    }

    printf("The symbols you gave contained %d upper and %d lower case letters.\n", upper_count, lower_count);

    return (0);

}