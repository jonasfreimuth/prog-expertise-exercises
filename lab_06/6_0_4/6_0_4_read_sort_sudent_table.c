# include <stdio.h>
# include <stdbool.h>
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
void print_list_to_file(student * head, char * outfile);
void print_stud_list(student * head);
student * sort_sl_lname(student * head);
student * sort_sl_mark(student * head);

int main() {
    char f_path[] = "marks.tab";

    student * s_list = get_stud_list(f_path);

    print_stud_list(s_list);

    // sorting functions modify list in place
    s_list = sort_sl_mark(s_list);
    print_list_to_file(s_list, "marks_mark_sort.tab");

    s_list = sort_sl_lname(s_list);
    print_list_to_file(s_list, "marks_lname_sort.tab");
    
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

void print_list_to_file(student * head, char * outfile) {  
    FILE * f_pt;

    if ((f_pt = fopen(outfile, "w")) == NULL) {
        fprintf(stderr, "File %s can't be opened/created for writing.", outfile);
        exit(1);
    }

    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char mark[MAX_NAME];
    
    student * current;

    current = head;

    while (current != NULL) {
        fprintf(f_pt, "%s\t%s\t%f\n", current->first_name, current->last_name,
                current->mark);

        current = current->next_student;
    }

    return;
}


void print_stud_list(student * head) {    
    student * current;

    current = head;

    while (current != NULL) {
        printf("%s\t%s\t%f\n", current->first_name, current->last_name,
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
    char mark_char[MAX_NAME];
    student * new, * current, * head;

    head = NULL;

    while(fscanf(f_pt, " %100[^\t]\t%100[^\t]\t%100[^\t\n]\n ", &first_name, &last_name, &mark_char) == 3) {       

        // printf("%s\t%s\t%s\n", first_name, last_name, mark_char);

        double mark = strtod(mark_char, NULL);

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


// strcmp(current->last_name, opt->last_name) < 0
student * sort_sl_lname(student * head) {
    student * prev, * current, * prev_opt, * opt, * new_head, * prev_new_opt;

    /* Go through list linearily, find opt value,
    Prepend value to head
    Start from head anew */

    current = head;
    opt = current;  
    prev_opt = NULL;
    prev = NULL;  
    new_head = head;
    prev_new_opt = NULL;

    bool update_new_head = true;

    while (head->next_student != NULL) {

        current = head;
        opt = current;

        // going through the list to find its optimum
        while (current != NULL) {
            if (strcmp(current->last_name, opt->last_name) < 0) {
                opt = current;
                prev_opt = prev;
            }

            prev = current;
            current = current->next_student;
        }

        if (opt != head) {
            prev_opt->next_student = opt->next_student;

            opt->next_student = head;

        } else {
        // opt == head
            head = opt->next_student;            
        }

        // if this is the first time a new opt is found, we need to
        // update the head of the sorted list
        if (update_new_head) {
            new_head = opt;
            update_new_head = false;

            // update the previous entry for the next optimum
            prev_new_opt = new_head;
        } else {
        // otherwise update the entry preceeding the current optimum
            prev_new_opt->next_student = opt;
            prev_new_opt = opt;
        }
    }

    return (new_head);
}


// sod it im just copy pasting the functions
// current->mark < opt->mark
student * sort_sl_mark(student * head) {
    student * prev, * current, * prev_opt, * opt, * new_head, * prev_new_opt;

    /* Go through list linearily, find opt value,
    Prepend value to head
    Start from head anew */

    current = head;
    opt = current;  
    prev_opt = NULL;
    prev = NULL;  
    new_head = head;
    prev_new_opt = NULL;

    bool update_new_head = true;

    while (head->next_student != NULL) {

        current = head;
        opt = current;

        // going through the list to find its optimum
        while (current != NULL) {
            if (current->mark < opt->mark) {
                opt = current;
                prev_opt = prev;
            }

            prev = current;
            current = current->next_student;
        }

        if (opt != head) {
            prev_opt->next_student = opt->next_student;

            opt->next_student = head;

        } else {
        // opt == head
            head = opt->next_student;            
        }

        // if this is the first time a new opt is found, we need to
        // update the head of the sorted list
        if (update_new_head) {
            new_head = opt;
            update_new_head = false;

            // update the previous entry for the next optimum
            prev_new_opt = new_head;
        } else {
        // otherwise update the entry preceeding the current optimum
            prev_new_opt->next_student = opt;
            prev_new_opt = opt;
        }
    }

    return (new_head);
}