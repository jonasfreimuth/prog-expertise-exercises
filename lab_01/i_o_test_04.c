# include <stdio.h>
# include <string.h>

int main() {
    int a, i;
    
    char sign[20];

    for (i = 0; i < 15; i++)
    {   
        printf("Integer number %d!\n", i+1);

        scanf("%d", &a);

        if (a >= 0) {
           strcpy(sign, "positive");
        } else {
           strcpy(sign, "negative");
        }

        printf("%d is %s.\n", a, sign);
    }

    return(0);
}