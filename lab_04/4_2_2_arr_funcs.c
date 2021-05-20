# include <stdio.h>
# include <stdlib.h>

int max(int array[]);
int min(int array[]);

int main() {

    int arr_size, i;

    printf("Enter size of array:");
    scanf("%d", &arr_size);
    printf("\n");

    int rnd_arr[arr_size];

    for (i = 0; i < arr_size; i ++) {
        rnd_arr[i] = rand();
        printf("%d\n", rnd_arr[i]);
    }

    printf("Max val in array is %d\n", max(rnd_arr));

    return (0);
}

int max(int array[]) {
    
    int i, max = 0;

    int arr_length;

    arr_length = sizeof(array);

    return (arr_length); 
   
}