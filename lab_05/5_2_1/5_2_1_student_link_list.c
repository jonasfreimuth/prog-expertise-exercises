# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# include "../5_1_1/5_1_1_1_num_students.h"

# include "../5_1_1/5_1_1_1_num_students.c"

# define MAX_NAME 100

typedef struct student {
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    float mark;
    struct student * next_student;
} student;

student * fill_stud_list(int n_studs);

int main() {   

    int n_studs = num_students();

    student * stud_list = fill_stud_list(n_studs);

    student * current;

    current = stud_list;

    printf("First Name\tLast name\tMark\n");

    float sum;

    while (1) {

        printf("%s\t%s\t%f\n",
         current->first_name, current->last_name, current->mark);

        sum += current->mark;

        current = current->next_student;

        if (current == NULL) {
            break;
        }
    }

    float avg = sum / n_studs;

    printf("\nClass average mark\t\t%f\n", avg);

    return (0);
}


student * fill_stud_list(int n_studs) {

    student * new, * current, * head;

    head = NULL;

    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    float mark;

    for (int i = 0; i < n_studs; i ++) {

        printf("Enter first name of student %d: ", i + 1);
        scanf(" %s", & first_name);
        puts("");
        printf("Enter last name of student %d: ", i + 1);
        scanf(" %s", & last_name);
        puts("");
        printf("Enter mark of student %d: ", i + 1);
        scanf(" %f", & mark);
        puts("\n");

        new = (student *) malloc(sizeof(student));
        
        strcpy(new->first_name, first_name);
        strcpy(new->last_name, last_name);
        new->mark = mark;
        new->next_student = NULL;


        // if this is the first student, perform additional steps
        if (head == NULL) {
            head = new;
        } else {
            /* if this is not the first student,
             there already exists a current student, so we
             can safely link there */
            current->next_student = new;
        }   

        current = new;

    }

    return (head);
}

/* 
A linked list may be sorted by finding the minimum/maximum of a field value
 by which one would like to sort int the linked list by running down the list
 pointer to pointer. The element with the min/max value is then placed at the
 start of the list by linking its parent to its child and linking the element
 itself to the previous head. The the same is repeated with the list starting
 again at the previous head. A pointer to the first min/max element is kept and 
 returned.


 */