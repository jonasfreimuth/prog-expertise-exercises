# include <iostream>
# include <map>
# include <filesystem>
# include <regex>
# include <fstream>

# include "argparse.hpp"
# include "jf_utils.cpp"

// function adapted from fasta-scan.cpp: scan()
std::vector< std::string > scan_pattern (std::string filename, std::string pattern) {

    std::ifstream infile; 
    std::string line;
    std::regex rxId("^>");
    std::string id;
    std::string sequence = "";
    std::vector< std::string > result;

    infile.open(filename); 

    // go through file
    while (std::getline(infile, line)) {

        // check if we are at the start of a new sequence
        if (std::regex_search(line, rxId)) {
            
            // if we have a previous sequence do all the updating we need
            if (sequence.length() > 0) {
                
                // if found, update result vector with id
                if (jfutils::grepl(sequence, pattern)) {
                    result.push_back(id);
                }

            }

            id = std::regex_replace(line, std::regex(">([^ ]+) *.*"), "$1");

            sequence = "";

        } else {

            sequence.append(line);

        }
    }
            
    // if we have a previous sequence do all the updating we need
    if (sequence.length() > 0) {
        
        // if found, update result vector with id
        if (jfutils::grepl(sequence, pattern)) {
            result.push_back(id);
        }

    }

    infile.close();

    return(result);
}

int main(int argc, char const *argv[]) {

    using namespace std;
    namespace fs = std::filesystem;
    
    argparse::ArgumentParser parser("FASTA parser");

    parser.add_argument("-i", "--infile")
        .help("Specify input .FASTA/.fasta file")
        .required()

        // check right away if the given file exists
        .action( [](const string& value) { 

                if (!fs::exists(value)) {
                    cout << "File " << value << " does not exist!\n";

                    exit(1);
                }

                return (value); 
            }
            );

    parser.add_argument("-p", "--pattern")
        .help("The pattern of base codes to look for in the fasta file")
        .required();

    try {
        parser.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << parser;
        exit(0);
    }

    std::string infile = parser.get<std::string>("--infile");
    std::string pattern = parser.get<std::string>("--pattern");

    vector <string> ids = scan_pattern(infile, pattern);

    cout << "IDs of sequences matching " << pattern << " are:\n";

    for (auto i : ids) {
        cout << "\t" << i << "\n";
    }

    return 0;
}
