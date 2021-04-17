# include <stdio.h>

int main() {
    int a, i;

    for (i = 0; i < 15; i++)
    {   
        printf("Integer number %d!\n", i+1);

        scanf("%d", &a);

        printf("%d\n", a*a);
    }

    return(0);
}