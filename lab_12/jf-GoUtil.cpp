# include <iostream>
# include <string>
# include <map>
# include <regex>
# include <fstream>

// debugging
# include <filesystem>

# include "jf-GoUtil.hpp"


std::map<std::string, std::string> GoUtil::getEntry(std::string filename, std::string id) {  

    std::ifstream infile; 
    std::string line = "";

    std::map< std::string, std::string > entry = {};
    std::string key = "";
    std::string val = "";
    bool match = false;

    std::cmatch m_obj;
    std::regex rxId(id);
    std::regex stopEntry("^$");
    std::regex splitField("^([^:]+): (.*)$");

    infile.open(filename); 

    // go through file
    while (std::getline(infile, line)) {

        // check if we are at the entry matching the id
        if (std::regex_search(line, rxId)) {
            std::cout << line << "\n";
            match = true;
        }

        if (match) {

            // if (std::regex_search(line, splitField)) {

                std::cout << "Key: " << std::regex_replace(line, splitField, "$1") <<
                    "\n\tValue: " << std::regex_replace(line, splitField, "$2") << "\n";

                entry.insert( 
                    { std::regex_replace(line, splitField, "$1"),
                      std::regex_replace(line, splitField, "$2") } );
            // }
        }

        // check if we are done with the current entry
        if (std::regex_search(line, stopEntry)) {
            
            if (match) {
                // if we had found the entry we were looking for
                // we dont need to look further
                break;
            }
        }
    }

    return (entry);
};


std::string GoUtil::getName(std::string filename, std::string id) {

    std::map< std::string, std::string > entry = {}; 
    std::string name = "";

    entry = GoUtil::getEntry(filename, id);

    // TODO: Handle name not being in entry
    name = entry["name"];   

    return (name);
};

bool GoUtil::isObsolete(std::string filename, std::string id) {
    std::cout << "Checking if obsolete...\n";

    return (false);
};

int main(int argc, char const *argv[])
{
    using namespace std;
    namespace fs = std::filesystem;
    
    GoUtil go_util = GoUtil();

    auto entry  = go_util.getName("go.obo", "GO:0000001");

    return 0;
}

