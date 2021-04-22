# include <stdio.h>

int main() {
    char c;

    printf("Enter letter: ");
    scanf("%c", &c);

    int c_as_i = (int) c;

    printf("\nNumeric representation of %c is %d\n", c, c_as_i);

    return(0);
}