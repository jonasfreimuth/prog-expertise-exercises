# include <stdio.h>

int num_students(void) {

    int n;

    puts("Enter the number of your students:\n");
    scanf("%d", &n);

    return (n);
}

/* int main() {

    int n_stud;
    n_stud = num_students();
    printf("Num students is %d:", n_stud);

    return (0);
} */