# include <stdio.h>
# include "5_1_1_1_num_students.h"
# include "5_1_1_2_collect_marks.h"
# include "5_1_1_3_arr_avg.h"
# include "5_1_1_4_print_avg.h"
/* 
# include "5_1_1_1_num_students.c"
# include "5_1_1_2_collect_marks.c"
# include "5_1_1_3_arr_avg.c"
# include "5_1_1_4_print_avg.c"
 */
int main() {
    int n_students;
    float avg;

    n_students = num_students();

    float mark_arr[n_students];

    collect_marks(mark_arr, n_students);

    avg = arr_avg(mark_arr, n_students);

    print_avg(avg);

    return (0);
}