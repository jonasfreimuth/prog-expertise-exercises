# include <iostream>
# include <string>
# include <vector>
# include <array>
# include <algorithm>

# include "argparse.hpp"
# include "Blosum.cpp"

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


int needle(string src, string dst, int in_del, Blosum score_mat) {

    if (src.length() == 0) {
	    return  dst.length() * in_del;
    } else if (dst.length() == 0) {
	    return  src.length() * in_del;
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

            // get match score 
            int mat_mis = score_mat(src.at(i - 1), dst.at(j - 1));

            // determine new cell value
            edit_mat.at(i).at(j) = max( 
                {above  + in_del,
                 left   + in_del,
                 diag   + mat_mis} );
        }
    }

    return edit_mat.at(src.length()).at(dst.length());
}

int main(int argc, char const *argv[]) {    
    
    argparse::ArgumentParser program("Needleman-Wunsch");

    program.add_argument("source_string")
        .default_value<string>("CQYEMLPFFL")
        .help("String to which the destination string will be compared");

    program.add_argument("destination_string")
        .default_value<string>("RAFLQRAHNQNHRDQARPIV")
        .help("String to compare to source string");

    program.add_argument("-l", "--levenshtein")
        .help("Calculate Levenshtein distance of both strings instead of the "
              "alignment score")
        .default_value<bool>(false)
        .implicit_value(true);

    program.add_argument("-c", "--gapcost")
        .help("Specify the cost to assign to a gap in the alignment")
        .default_value<int>(-10)
        .action([](const std::string& value) {
            return std::stoi(value);
        });

    program.add_argument("-m", "--blosumfile")
        .help("Specify a file containing a formatted BLOSUM matrix")
        .default_value<string>("");

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }

    auto src = program.get<std::string>("source_string");
    auto dst = program.get<std::string>("destination_string");

    auto gap_cost = program.get<int>("--gapcost");
    auto do_levenshtein = program.get<bool>("--levenshtein");

    if (do_levenshtein) {

        int dist = levenstein(src, dst, -1, gap_cost);

        cout << "Distance between the strings " << src << " and "
            << dst << " is " << dist << endl;

    } else {

        // CAUTION: Currently there are no checks whether there are 
        //  chars outside of one letter AA codes in any of the strings.
        //  This can lead to crashes

        Blosum score_mat = Blosum();

        auto blosumfile = program.get<std::string>("--blosumfile");

        if (blosumfile != "") {
            score_mat.read_matrix(blosumfile);
        }

        int score = needle(src, dst, gap_cost, score_mat);

        cout << "The alignment score of " << src << " against " << dst <<
            "is " << score << endl;
    
    }

    return 0;
}
