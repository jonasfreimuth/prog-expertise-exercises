5_1_1_5_calc_class_avg : 5_1_1_1_num_students.o 5_1_1_2_collect_marks.o \
							5_1_1_3_arr_avg.o 5_1_1_4_print_avg.o \
							5_1_1_5_calc_class_avg.o
	gcc -o class_avg 5_1_1_1_num_students.o 5_1_1_2_collect_marks.o \
		5_1_1_3_arr_avg.o 5_1_1_3_arr_avg.o

5_1_1_1_num_students.o : 5_1_1_1_num_students.c 
	gcc -c 5_1_1_1_num_students.c
5_1_1_2_collect_marks.o : 5_1_1_2_collect_marks.c
	gcc -c 5_1_1_2_collect_marks.c
5_1_1_3_arr_avg.o : 5_1_1_3_arr_avg.c
	gcc -c 5_1_1_3_arr_avg.c
5_1_1_4_print_avg.o : 5_1_1_4_print_avg.c 
	gcc -c 5_1_1_4_print_avg.c
5_1_1_5_calc_class_avg.o : 5_1_1_5_calc_class_avg.c
	gcc -c 5_1_1_5_calc_class_avg.c

clean: 
	rm -f 5_1_1_*.o