# include <stdio.h>

int main (void) {

  static int in_sum;
  int input;

  in_sum = 0;
  input = 1;

  while (input != 0) {

    printf("Current sum is %d.\n", in_sum);
    printf("Enter a whole number to add or stop with 0.\n");
    scanf("%d", &input);

    in_sum += input;
  }

    return (0);
}