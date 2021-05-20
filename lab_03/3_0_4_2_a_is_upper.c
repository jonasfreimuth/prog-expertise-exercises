# include <stdbool.h>

int is_upper(char x) {
    if ((int) x >= 65 && (int) x <= 90) {
        // is uppercase
        return (0);

    } else if ((int) x >= 97 && (int) x <= 122) {
        // is lowercase
        return (1);
    } else {
        // who knows what it is
        return (-1);
    }
}