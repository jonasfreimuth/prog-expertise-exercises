# include <iostream>
# include <map>
# include <filesystem>
# include <regex>
# include <fstream>

# include "argparse.hpp"

// function adapted from fasta-scan.cpp: scan()
std::vector< std::pair<std::string,int> > scan (std::string filename) {

    std::ifstream infile; 
    std::string line;
    std::regex rxId("^>");
    std::string id;
    int nchar = 0;
    std::vector< std::pair<std::string,int> > result;

    infile.open(filename); 

    while (std::getline(infile, line)) {

        if (std::regex_search(line, rxId)) {

        if (nchar > 0) {

            //std::cout << id << "\t" << nchar << std::endl;
            result.push_back( { id, nchar } );

        }

        id = std::regex_replace(line, std::regex(">([^ ]+) *.*"), "$1");
        nchar = 0;

        } else {

        nchar += line.length();

        }
    }

    //std::cout << id << "\t" << nchar << std::endl;
    result.push_back( { id, nchar } );
    infile.close();

    return(result);
}

int main(int argc, char const *argv[]) {

    namespace fs = std::filesystem;
    
    argparse::ArgumentParser parser("FASTA parser");

    parser.add_argument("-i", "--infile")
        .help("Specify input .FASTA/.fasta file")
        .required()

        // check right away if the given file exists
        .action( [](const std::string& value) { 

                if (!fs::exists(value)) {
                    std::cout << "File " << value << 
                        " does not exist!\n";

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



    return 0;
}
