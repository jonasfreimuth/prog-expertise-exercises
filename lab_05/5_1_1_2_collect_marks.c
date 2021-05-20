# include <stdio.h>

void collect_marks(float * mark_array, int n_students) {

    int i;
    float in_mark;

    for (i = 0; i < n_students; i ++) {
        printf("Enter mark of student number %d: ", i + 1);
        scanf("%f", &in_mark);
        puts("\n");

        * mark_array = in_mark;

        mark_array ++;

    }

    return;
}

/* int main() {

    int n_stud;
    float arr[5];
    float * arr_pt;

    // arr_pt = & arr;

    n_stud = 5;

    collect_marks(n_stud, arr);

    for (int i = 0; i < n_stud; i ++) {
        printf("Arr at %d is %f\n", i + 1, arr[i]);
    }

    return (0);
} */