# include <stdio.h>
# include <limits.h>

int main() {

    int i;
    char c;

    printf("int\tchar\n");

    for (i = 1; i <= UCHAR_MAX; i++) {

        char c = (char) i;

        printf("%d\t%c\n", i, c);

    }

    return (0);
}