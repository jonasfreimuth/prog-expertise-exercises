# include <stdlib.h>
# include <math.h>

# define MAX_LEVEL 7

typedef struct node {
    int value;
    struct node * left_child;
    struct node * right_child;
} node;

int main() {

    // this array stores nodes from left to right, level after level
    // it uses 0 for missing nodes
    int tree_array[MAX_LEVEL] = { 2, 9, 3, 7, 4, 0, 99 };
    
    int k = 0;
    int i = 0;
    int lvl = 0;
    node * root = NULL;

    while (k < MAX_LEVEL) {

        // TODO: find parent pointer    
        /* for that find the index of the parent via floor(k/2) 
            save left or right via k % 2, follow tree down to p
            */    

        int l_r[lvl]; 
        int p = k;

        while (p != 0) {
            
        }

        node * curr_node = (node * ) malloc(sizeof(node));

        curr_node->value = tree_array[k];
        curr_node->left_child = NULL;
        curr_node->right_child = NULL;

        //TODO: add curr_node as child to parent pointer

        k ++;
    }
}