# include <stdio.h>
# include <stdlib.h>

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


int main() {
    char f_path[] = "marks.tab";

    print_file(f_path);
/* 
    student * s_list = get_stud_list(f_path);

     */
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

student * get_stud_list(char * infile) {

    FILE * f_pt;

    if ((f_pt = fopen(infile, "r")) == NULL) {
        fprintf(stderr, "File %s does not exist or can't be opened.", infile);
        exit(1);
    }


}