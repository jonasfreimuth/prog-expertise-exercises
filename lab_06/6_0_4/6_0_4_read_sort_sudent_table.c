# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX_NAME 100
# define MAX_FILE 1000

typedef struct student {
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    float mark;
    struct student * next_student;
} student;

student * get_stud_list(char * infile);
void print_file(char * infile);
void print_stud_list(student * head);

int main() {
    char f_path[] = "marks.tab";

    // print_file(f_path);

    student * s_list = get_stud_list(f_path);

    print_stud_list(s_list);
    
    return (0);
}

void print_file(char * infile) {

    FILE * f_pt;

    if ((f_pt = fopen(infile, "r")) == NULL) {
        fprintf(stderr, "File %s does not exist or can't be opened.", infile);
        exit(1);
    }

    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char mark[MAX_NAME];

    while(fscanf(f_pt, " %100[^\t]\t%100[^\t]\t%100[^\t\n]\n ", &first_name, &last_name, &mark) == 3) {       

        printf("%s\t%s\t%s\n", first_name, last_name, mark);

    }

    return;
}

void print_stud_list(student * head) {
    
    student * current;

    current = head;

    while (current != NULL) {
        printf("%s\t%s\t%d\n", current->first_name, current->last_name,
                current->mark);

        current = current->next_student;
    }

    return;
}

student * get_stud_list(char * infile) {

    FILE * f_pt;

    if ((f_pt = fopen(infile, "r")) == NULL) {
        fprintf(stderr, "File %s does not exist or can't be opened.", infile);
        exit(1);
    }

    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char mark[MAX_NAME];
    student * new, * current, * head;

    head = NULL;

    while(fscanf(f_pt, " %100[^\t]\t%100[^\t]\t%100[^\t\n]\n ", &first_name, &last_name, &mark) == 3) {       

        printf("%s\t%s\t%s\n", first_name, last_name, mark);

        double mark = (double) mark;

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