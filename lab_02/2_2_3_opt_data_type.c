# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>

int main(int argc, char const *argv[])
{
    int in, size;
    char dat_t[80];

    printf("Enter the integer:");
    scanf("%d", &in);
    printf("\n"); 

    // turn 0 into a 1, shouldnt make a difference for data types
    if (in == 0) {
        in = 1;
    }   

    size = 0;
    size = (int) floor((log(abs(in)) / log(2)) / 8) + 1;
    
    printf("Bytesize of input is %d.\n", size);
    
    if (size <= sizeof(short int)) {
        strcpy(dat_t, "short int");

    } else if (size <= sizeof(int)) {
        strcpy(dat_t, "int");

    } else if (size <= sizeof(long int)) {
        strcpy("long int", dat_t);
        
    } else if (size <= sizeof(long long int)) {
        strcpy("long long int", dat_t);
    } else {
        printf("Maybe try an unsigned long long integer?\n");

        return 0;
    }

    printf("Best type is %s, for signed integers.\n", dat_t);

    return 0;
}
