# include <string>
# include <vector>
# include <tuple>
# include <regex>
# include <fstream>
# include <iostream>

# include "jf-FASTA-parser.hpp"

std::vector< std::tuple< std::string, std::string, std::string > > jf_FASTA_parser::getN (std::string filename) {

    std::vector< std::tuple< std::string, std::string, std::string > > output = { };
    std::ifstream infile;
    std::string line = "";
    std::string seq = "";
    std::string id = "";
    std::regex rxStart("^>");
    std::regex rxId("^>([a-zA-Z0-9_|]+) .+");
    
    infile.open(filename);
    
    while (std::getline(infile, line)) {
        if (std::regex_search(line, rxStart)) {
            id = std::regex_replace(line, rxId, "$1");
            if (seq.size() > 0) {
                output.push_back( std::make_tuple( filename, id, std::to_string(seq.size()) ) );
                seq = "";
            }
        }

        if (! std::regex_search(line, rxStart)) {
            seq = seq + line;
        } 
    }

    infile.close();

    return (output);
}

std::vector< std::tuple< std::string, std::string, std::string > > jf_FASTA_parser::getSeq (std::string filename, std::string id) {

    std::vector< std::tuple< std::string, std::string, std::string > > output = { };

    std::ifstream infile;
    std::string line = "";
    std::string header = "";
    std::string seq = "";

    bool match = false;

    std::regex rxid("^>" + id);
    std::regex rxHeader("^>(.+)");
    std::regex rxStart("^>");
    
    infile.open(filename);
    
    while (std::getline(infile, line)) {

        if (std::regex_search(line, rxStart)) {
            
            if (match && seq.size() > 0) {
                output.push_back( std::make_tuple( filename, header, seq ) );
            } 

            seq = "";
            match = false;

            if (std::regex_search(line, rxid)) {
                match = true;

                // std::cout << "Matched line " << line << "\n";

                header = std::regex_replace(line, rxHeader, "$1"); 

                // std::cout << "Header is " << header << "\n";                          
            }
        }
        

        if (match && ! std::regex_search(line, rxStart)) {
            seq = seq + line;
        } 
    }

    // handle last seq
    if (seq.size() > 0) {
        output.push_back( std::make_tuple( filename, header, seq ) );
        seq = "";
        match = false;
    }
    
    infile.close();

    return (output);
}