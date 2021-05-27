# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "../../lab_03/3_0_4_1_a_square.c"
# include "../../lab_03/3_0_4_1_b_cube.c"

# define START 0
# define STOP 1000
# define STEP 1

int main() {

    float i_square, i_cube, i_sqrt;

    char f_path[] = "out.tab";

    FILE * f_pt;

    if ((f_pt = fopen(f_path, "w")) == NULL) {
        fprintf(stderr, "File %s does not exist or can't be opened.", f_path);
        exit(1);
    }

    fprintf(f_pt, "x\tx^2\tx^3\tsqrt(x)\n");

    for (int i = START; i <= STOP; i += STEP) {
        i_square = square(i);
        i_cube = cube(i);
        i_sqrt = sqrt(i);

        fprintf(f_pt, "%d\t%f\t%f\t%f\n", i, i_square, i_cube, i_sqrt);
    }

    fclose(f_pt);

    return (0);
}