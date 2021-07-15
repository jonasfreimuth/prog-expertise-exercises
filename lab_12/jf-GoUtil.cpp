# include <iostream>
# include <string>
# include <map>
# include <regex>
# include <fstream>

# include "jf-GoUtil.hpp"


std::string GoUtil::getEntry(std::string filename, std::string id) {  

    std::ifstream infile; 
    std::string line = "";
    std::string entry = "";
    std::regex rxId(id);
    bool match = false;

    std::regex newEntry("^\[TERM\]");
    std::regex stopEntry("^$");

    infile.open(filename); 

    // go through file
    while (std::getline(infile, line)) {

        // check if we are at the entry matching the id
        if (std::regex_search(line, rxId)) {
            std::cout << line << "\n";
            match = true;
        }

        if (match) {
            // if we are in the right entry, save the current line
            entry.append(line);

        }

        // check if we are done with the current entry
        if (std::regex_search(line, stopEntry)) {
            
            if (match) {
                // if we had found the entry we were looking for
                // we dont need to look further
                break;
            }
        }

        if (match) {
            // if we are in the right entry, and have not 
            // stopped with appending, add a spearation sign
            // we wouldnt need to do this if we put in the work and
            // did everything with maps
            entry.append("; ");
        }
    }

    return (entry);
};


std::string GoUtil::getName(std::string filename, std::string id) {

    std::regex rxName("^name: ");
    // std::regex rxNameExtract("(?<=^name: )[a-zA-Z ]");    
    std::string name = "";
    std::string entry = "";
    // std::vector <std::string> result = {  };

    entry = GoUtil::getEntry(filename, id);

    name = std::regex_replace(entry, std::regex("(?=name: )[^;]+"), "$1");

    return (name);
};

bool GoUtil::isObsolete(std::string filename, std::string id) {
    std::cout << "Checking if obsolete...\n";

    return (false);
};
