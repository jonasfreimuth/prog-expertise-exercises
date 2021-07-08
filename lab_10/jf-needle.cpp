# include <iostream>
# include <string>
# include <vector>
# include <array>
# include <algorithm>

using namespace std;

int levenstein(string src, string dst, int in_del, int gap_cost) {

    if (src == dst) {
	    return 0;
    } else if (src.length() == 0) {
	    return  dst.length();
    } else if (dst.length() == 0) {
	    return  src.length();
    }
    
    vector< vector<int> > edit_mat;
    vector<int> row;

    // initialize edit matrix
    for (int i = 0; i < src.length() + 1; i ++) {
        row = {};

        for (int j = 0; j < dst.length() + 1; j ++) {
            if (i == 0) {
                row.push_back(j);
            } else if (j == 0) {
                row.push_back(i);
            } else {
                row.push_back(0);
            }            
        } 

        edit_mat.push_back(row);       
    }

    // fill edit matrix    
    for (int i = 1; i < src.length() + 1; i ++) {
        for (int j = 1; j < dst.length() + 1; j ++) {

            // get cell values
            int above   = edit_mat.at(i - 1)  .at(j)    ;
            int left    = edit_mat.at(i)      .at(j - 1);
            int diag    = edit_mat.at(i - 1)  .at(j - 1);

            // determine whether to add a gap or a match
            int mat_mis = gap_cost;

            if (src.at(i - 1) == dst.at(j - 1)) {
                mat_mis = 0;
            }

            // determine new cell value
            edit_mat.at(i).at(j) = min( 
                {above  + in_del,
                 left   + in_del,
                 diag   + mat_mis} );
        }
    }

    return edit_mat.at(src.length()).at(dst.length());
}

int main(int argc, char const *argv[])
{    
    string src = "book";
    string dst = "back";

    int in_del      = 1;
    int gap_cost    = 1;

    if (argc >=  2) {
        src = argv[1];
    }

    if (argc >= 3) {
        dst = argv[2];
    }

    if (argc >= 4) {
        in_del = stoi(argv[3]);
    }

    if (argc >= 5) {
        gap_cost = stoi(argv[4]);
    }

    int dist = levenstein(src, dst, in_del, gap_cost);

    cout << dist << endl;

    return 0;
}
