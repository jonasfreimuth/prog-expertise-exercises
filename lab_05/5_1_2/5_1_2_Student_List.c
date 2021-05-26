# include <stdio.h>
# include <string.h>
# include "../5_1_1/5_1_1_1_num_students.h"
# include "../5_1_1/5_1_1_2_collect_marks.h"
# include "../5_1_1/5_1_1_3_arr_avg.h"

# include "../5_1_1/5_1_1_1_num_students.c"
# include "../5_1_1/5_1_1_2_collect_marks.c"
# include "../5_1_1/5_1_1_3_arr_avg.c"

# define MAX_NAME 100

void collect_studs(char * first_names[], char * last_names[], int n_studs);

void print_studs(char * first_names[], char * last_names[], float marks[], int n_studs);

int main() {

    int max_name = MAX_NAME;
    int n_studs = 30;

    n_studs = num_students();

    char first_names[n_studs][max_name] = {"0"};
    char last_names[n_studs][max_name] = {"0"};
    float marks[n_studs];

    collect_studs(&first_names, &last_names, n_studs);

    collect_marks(marks, n_studs);

    print_studs(first_names, last_names, marks, n_studs);

    for (int i = 0; i < n_studs; i ++) {
        printf("%s", first_names[i]);
        printf("%s", last_names[i]);
    }
    
}

void collect_studs(char * first_names[], char * last_names[], int n_studs) {

    char f_name[MAX_NAME];
    char l_name[MAX_NAME];


    for (int i = 0; i < n_studs; i ++) {
        printf("Enter first and last name of student number %d:", i + 1);
        scanf(" %s ", f_name);
        scanf(" %s ", l_name);
        printf("\n");
        
        first_names[i] = f_name;
        last_names[i] = l_name;
        /* strcpy(first_names[i], f_name);
        strcpy(last_names[i], l_name); */
    }

    return;
}

void print_studs(char * first_names[], char * last_names[], float marks[], int n_studs) {

    puts("First Name\tLast name\tMark");
    for (int i = 0; i < n_studs; i++) {
        printf("%s\t%s\t%f\n", first_names[i], last_names[i], marks[i]);
    }

    float avg = arr_avg(marks, n_studs);

    printf("\nClass average mark\t\t%f", avg);

    return;
}