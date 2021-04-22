# include <stdio.h>

int main() {

    int sum, in;

    sum = 0;

    while (1) {

        printf("Enter a number to add to the sum. (0 will cancel the programm)\n");
        
        scanf("%i", &in);

        if (in == 0) {
            break;
        }

        sum = sum + in;

        printf("Sum so far is %i.\n", sum);

    }

    return(0);
}