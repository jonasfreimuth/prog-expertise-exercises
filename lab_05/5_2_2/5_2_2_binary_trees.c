# include <stdlib.h>
# include <math.h>

# define MAX_LEVEL 7

typedef struct node {
    int value;
    struct node * left_child;
    struct node * right_child;
} node;

int main() {

    // for arbitrary solution use an array storing 0 for missing nodes
    int tree_array[MAX_LEVEL] = { 2, 9, 3, 7, 4, 0, 99 };
    
    int k = 0;
    int i = 0;
    int lvl = 0;
    node * root = NULL;

    while (k < MAX_LEVEL) {

        // find parent pointer

        

        node * curr_node = (node * ) malloc(sizeof(node));

        curr_node->value = tree_array[k];

        int left_pos = 2 * k;
        int right_pos = (2 * k) + 1;

        // if we are at MAX_LEVEL, tree_array[left_post] 
        // will be out of bounds
        if (tree_array[left_pos] == 0 || lvl == MAX_LEVEL) {
            curr_node->left_child = NULL;
        } else {
            curr_node->left_child = (node * ) malloc(sizeof(node));
        }

        if (tree_array[right_pos] == 0 || lvl == MAX_LEVEL) {
            curr_node->right_child = NULL;
        } else {
            curr_node->right_child = (node * ) malloc(sizeof(node));
        }

        k ++;
    }
}