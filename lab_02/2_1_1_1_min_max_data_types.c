# include <stdio.h>
# include <limits.h>

int main() {    

    printf("Type\tBytesize\tmin\tmax\n");

    printf("Signed char:\t%ld\t%d\t%d\n", sizeof(char), 0, UCHAR_MAX);
    printf("Unsigned char:\t%ld\t%d\t%d\n", sizeof(unsigned char), CHAR_MIN, CHAR_MAX);
    printf("Short Integer:\t%ld\t%d\t%d\n", sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("Unsigned short Integer:\t%ld\t%d\t%d\n", sizeof(unsigned short), 0, USHRT_MAX);
    printf("Integer:\t%ld\t%d\t%d\n", sizeof(int), INT_MIN, INT_MAX);
    printf("Unsigned Integer:\t%ld\t%d\t%ld\n", sizeof(unsigned int), 0, UINT_MAX);
    printf("Long Integer:\t%ld\t%ld\t%ld\n", sizeof(long int), LONG_MIN, LONG_MAX);
    printf("Unsigned long Integer:\t%ld\t%d\t%lld\n", sizeof(unsigned long), 0, ULONG_MAX);
    printf("Long long Integer:\t%ld\t%lld\t%lld\n", sizeof(long long int), LLONG_MIN, LLONG_MAX);
    printf("Unsigned long long Integer:\t%ld\t%d\t%lld\n", sizeof(unsigned long long), 0, ULLONG_MAX);

    return(0);
}