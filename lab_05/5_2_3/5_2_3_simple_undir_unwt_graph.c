# include <stdio.h>
# include <string.h>

# define N 9

float avg_degree(int n, int A[n][n]);

int main() {
    /* graph represented by a adjacency matrix of size n x n,
        n being the number of nodes in the graph. Entries are 1
        if there exists an edge between the node corresponding to
        the row index and the node corresponding to the col index.
        All other entries as well as diagonal entries are 0. */
    int adj_mat[][N] = { 
        { 0, 0, 1, 0, 1, 0, 0, 1, 1 }, 
        { 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 1, 1, 0, 0, 1, 1 },
        { 0, 0, 1, 0, 0, 0, 1, 0, 0 },
        { 1, 1, 1, 0, 0, 1, 1, 0, 1 },
        { 0, 0, 0, 0, 1, 0, 1, 0, 0 },
        { 0, 0, 0, 1, 1, 1, 0, 0, 1 },
        { 1, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 0, 1, 1, 0 }
                    };

    int * arr_pt = & adj_mat;

    printf("Average number of neighbors of the given ");
    printf("graph is: %f", avg_degree(N, adj_mat));

    return (0);
}

float avg_degree(int n, int A[n][n]) {

    int deg_sum = 0;
    int row_sum = 0;

    for (int i = 0; i < n; i ++) {
        row_sum = 0;

        for (int j = 0; i < n; j ++) {
            row_sum += A[i][j];
        }

        deg_sum += row_sum;

    }

    return (deg_sum / n);    

}