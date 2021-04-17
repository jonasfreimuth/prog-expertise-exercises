# include <stdio.h>

int main()
{
    int a, b, c;

    /* Simple swap with additional variable */
    a = 1;
    b = 2;
    c = 0;

    printf("Before simple swap: a = %d, b = %d, c = %d.\n", a, b, c);

    c = a;
    a = b;
    b = c;

    printf("After simple swap: a = %d, b = %d, c = %d.\n", a, b, c);

    /* Swap without additional variable */
    a = 1;
    b = 2;

    printf("Before advanced swap: a = %d, b = %d.\n", a, b);

    a = a + b;
    b = a - b;  /* b becomes what was previously only a */
    a = a - b;  /* as b is now what was only a, the same operation 
                gives us what was only b*/

    printf("After advanced swap: a = %d, b = %d.\n", a, b);

    return 0;
}
