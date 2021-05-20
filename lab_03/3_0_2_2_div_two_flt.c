# include <stdio.h>

int main() {
    float in_1, in_2, out;

    printf("Enter two values, the first to be divided by the second.\n"
            "The second value can't be 0!\n");

    scanf("%f %f", &in_1, &in_2);

    if (in_2 == 0) {
        printf ("I specifically said that the second value must not be 0!\n");
    } else {
        out = in_1 / in_2;
        printf("%f divided by %f equals %f", in_1, in_2, out);
    }

    return (0);
}