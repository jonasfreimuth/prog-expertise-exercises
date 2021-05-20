# include <stdio.h>

float square(float x) {
    return(x * x);
}

float cube(float x) {
    return(x * x * x);
}

float div_two(float x) {
    return(x / 2);
}

int main() {

    float input, square_in, cube_in, div_two_in;

    printf("Enter integer or float:\n");
    scanf("%f", &input);

    square_in = square(input);
    cube_in = cube(input);
    div_two_in = div_two(input);

    printf("%f squared is %f\n", input, square_in);
    printf("%f cubed is %f\n", input, cube_in);
    printf("%f divided by two is %f\n", input, div_two_in);

    return(0);
}