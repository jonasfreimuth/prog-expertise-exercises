# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main() {

    long var;

    long *varpoint;

    varpoint = &var;

    printf("Enter any integer:");
    scanf("%li", varpoint);
    printf("\n");

    printf("Value at %p is %li.\n", varpoint, *varpoint);    

    printf("\nNow the array\n");

    long int arr[23] = { 0 };

    long int *arrpoint;

    arrpoint = arr;

    int i = 0;

    for (i = 0; i < 23; i ++) {        
        printf("Value at %p is %li.\n", arrpoint ++, *arrpoint);
    }

    return (0);
}