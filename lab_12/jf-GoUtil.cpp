# include <iostream>
# include <string>
# include <regex>
# include <fstream>

# include "jf-GoUtil.hpp"

std::string GoUtil::getEntry(std::string filename, std::string id) {
    std::cout << "Getting entry...\n";            

    /* std::ifstream infile; 
    std::string line;
    std::regex rxId(id);
    std::string sequence = "";
    std::vector< std::string > result; */

    return ("");
};

std::string GoUtil::getName(std::string filename, std::string id) {
    std::cout << "Getting name...\n";
    
    std::ifstream infile; 
    std::string line = "";
    std::regex newEntry("^\[TERM\]");
    std::regex rxName("^name: ");
    // std::regex rxNameExtract("(?<=^name: )[a-zA-Z ]");
    std::regex rxId(id);
    std::string name = "";
    // std::vector <std::string> result = {  };
    bool match = false;

    infile.open(filename); 

    // go through file
    while (std::getline(infile, line)) {

        // check if we are at a new entry
        if (std::regex_search(line, newEntry)) {
            match = false;
        }

        // check if we are at the entry matching the id
        if (std::regex_search(line, rxId)) {
            std::cout << line << "\n";
            match = true;
        }

        // if we are at the right entry and 
        if (std::regex_search(line, rxName)) {
            // name = std::regex_replace(line, rxNameExtract, "$1");
            name = line;
            //result.push_back(name);

            break;
        }

    }

    return (name);
};

bool GoUtil::isObsolete(std::string filename, std::string id) {
    std::cout << "Checking if obsolete...\n";

    return (false);
};
