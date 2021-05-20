# include <stdio.h>

float arr_avg(float * arr, int arr_size) {
    float sum = 0;
    float avg;

    for (int i = 0; i < arr_size; i ++) {
        sum = sum + *arr;
        arr ++;
    }

    avg = sum / arr_size;

    return (avg);
}

/* 
int main() {
    float test_arr[5] = {1.1, 2.2, 3.3, 4.4, 5.5};

    float test_avg = arr_avg(test_arr, 3);

    printf("Average of array ");

    for (int i = 0; i < 5; i ++) {
        printf("%f", test_arr[i]);

        if (i != 5 - 1) {
            printf(", ");
        }
    }

    printf(" is %f.", test_avg);

    return (0);
} */