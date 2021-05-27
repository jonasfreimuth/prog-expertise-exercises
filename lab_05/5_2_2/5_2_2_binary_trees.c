# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define N_NODES 7

typedef struct node {
    int value;
    struct node * left_child;
    struct node * right_child;
} node;

int n_nodes(node * root);
void preorder_traversal(node * root, int * n); 

int main() {

    // this array stores nodes from left to right, level after level
    // it uses 0 for missing nodes
    int tree_array[N_NODES] = { 2, 9, 3, 7, 4, 0, 99 };
    node * pt_arrary[N_NODES];
    
    int i = 0;
    int lvl = 0;
    int p = 0;
    int l = 0;
    node * root = NULL;
    node * parent = NULL;

    for (int k = 0; k < N_NODES; k ++) {

        printf("%d", k);

        // don't perform an action if the array contains a missing node at k
        if (tree_array[k] == 0) {
            continue;
        }

        node * curr_node = (node * ) malloc(sizeof(node));

        curr_node->value = tree_array[k];
        curr_node->left_child = NULL;
        curr_node->right_child = NULL;
        
        /* 
        for that find the index of the parent via floor(k/2) 
        save left or right via k % 2, find parent pointer in pt_array
        */    
        
        // +1 for array indexing offset
        p = floor((k + 1) / 2);
        l = k % 2;
        
        if (p > 0) {
            // and - 1 again for array offset
            parent = pt_arrary[p - 1];

            if (l) {
                parent->left_child = curr_node;
            } else {
                parent->right_child = curr_node;
            }
        } else {
            root = curr_node;
        }

        pt_arrary[k] = curr_node;
    }

    printf("Size of tree is %d", n_nodes(root));

    return (0);
}

int n_nodes(node * root) {
    
    int n = 0;
    int * n_pt = &n;

    preorder_traversal(root, n_pt);

    return (n);

}

void preorder_traversal(node * root, int * n) {

    if (root == NULL) {
        return;
    }

    printf("Current node: %d\n", root->value);

    (* n) ++;

    preorder_traversal(root->left_child, n);
    preorder_traversal(root->right_child, n);

    return;
}

