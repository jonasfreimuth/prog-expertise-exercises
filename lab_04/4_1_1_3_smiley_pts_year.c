# include <stdio.h>
# include <stdbool.h>
# include <string.h>

int main() {

    int input, month, day, i, j = 0;

    int max_month = 31;
    int n_month = 12;

    int sm_pts[max_month][n_month];

    memset(sm_pts, 0, max_month * n_month * sizeof(int));

    while (true) {   

        printf("Enter date in [d.m] format (-1 anywhere cancels): ");
        scanf("%d.%d.", &day, &month);
        printf("\n");

        day = day - 1;
        month = month - 1;

        if (day < 0 | month < 0 | day > max_month | month > n_month) {
            break;
        }
        
        printf("Enter your happiness points for the %d.%d (-1 cancels): ", day + 1, month + 1);
        scanf("%d", &input);
        printf("\n");

        if (input == -1) {
            break;
        }

        sm_pts[day][month] = input;

    }

    printf("Month\tDay\tHappiness\n");

    for (i = 0; i < n_month; i ++) {

        for (j = 0; j < max_month; j ++) {

            if (sm_pts[j][i] > 0){
                printf("%d\t%d\t%d\n", j + 1, i + 1, sm_pts[j][i]);
            }
        }

    }

    return (0);
}