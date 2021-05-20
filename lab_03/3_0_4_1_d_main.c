# include <stdio.h>
# include "3_0_4_a_square.c"
# include "3_0_4_b_cube.c"
# include "3_0_4_c_div_by_two.c"

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