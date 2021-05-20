# include <stdio.h>

int main()  {

    // general initializations
    float out;
    static float sum; 
    int i, n_vals;   

    // determine array size
    printf("Enter number of values you want to calculate the average of:\n");
    scanf("%d", &n_vals);
 
    // now we know the array size, declare it
    float in_arr[n_vals];


    // get sequence of values
    printf("Enter a sequence of %d values of which to calculate the average\n", n_vals);

    i = 0;

    while (i < n_vals) {

        printf("\nValue #%d:", i + 1);
        scanf("%f", &in_arr[i]);

        // also increment sum while we are at the array position
        sum += in_arr[i];

        i ++;

    }

    // calculate average
    out = sum / n_vals;

    printf("Average of the entered values is: %f\n", out);
    
    return (0);
}