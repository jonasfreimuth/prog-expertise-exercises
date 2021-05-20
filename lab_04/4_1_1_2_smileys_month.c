# include <stdio.h>
# include <stdbool.h>
# include <string.h>

int main() {

    int arr_length = 31;

    int *day_point;

    int sm_pts[arr_length];
    memset(sm_pts, 0, arr_length * sizeof(int));

    int i = 0;

    day_point = sm_pts;

    int input, day;

    input = 0;
    day = 0;

    while (true) {   

        printf("Enter day (-1 cancels): ");
        scanf("%d", &day);
        printf("\n");

        if (day == -1) {
            break;
        }

        printf("Enter your happiness points for day %d (-1 cancels): ", day);
        scanf("%d", &input);
        printf("\n");

        if (input == -1) {
            break;
        }
        
        sm_pts[day] = input;
    }

    printf("Day\tHappiness\n");

    for (i = 0; i < arr_length; i ++) {

        if (sm_pts[i] > 0) {
            printf("%d\t%d\n", i, sm_pts[i]);
        }
    }

    return (0);
}