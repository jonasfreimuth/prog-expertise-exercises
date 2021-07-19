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
    std::map< std::string, int > key_num = {};
    std::string key = "";
    std::string val = "";
    bool match = false;

    std::regex rxId(id);
    std::regex stopEntry("^$");
    std::regex splitField("^([^:]+): (.*)$");

    infile.open(filename); 

    // go through file
    while (std::getline(infile, line)) {

        // check if we are at the entry matching the id
        if (std::regex_search(line, rxId)) {
            match = true;
        }

        // check if we are done with the current entry
        if (std::regex_search(line, stopEntry)) {
            
            if (match) {

                // reset map for keys in the entry
                key_num = {};

                // if we had found the entry we were looking for
                // we dont need to look further
                break;
            }
        }

        if (match) {

            auto key = std::regex_replace(line, splitField, "$1");
            auto value = std::regex_replace(line, splitField, "$2");

            if (!(key_num.find(key) == key_num.end())) {
                // if we dont have that key already add an entry for it
               key_num[key] = 0;
            }

            // append current number for the key to it
            key = key + std::to_string(key_num[key] ++);

            entry.insert( 
                { key, value } );                    
        }
    }

    return (entry);
};


std::string GoUtil::getName(std::string filename, std::string id) {

    std::map< std::string, std::string > entry = {}; 
    std::string name = "";

    entry = GoUtil::getEntry(filename, id);

    // TODO: Handle name not being in entry
    name = entry["name0"]; 

    return (name);
};

bool GoUtil::isObsolete(std::string filename, std::string id) {

    std::map< std::string, std::string > entry = {}; 
    std::string is_obsolete = "";
    bool out = false;

    entry = GoUtil::getEntry(filename, id);
    is_obsolete = entry["is_obsolete0"];

    if (is_obsolete != "") {
        out = true;
    }

    return (out);
};

std::map< std::string, std::string > GoUtil::getChildren(std::string filename,
                                                         std::string id) {

    std::map< std::string, std::string > children;
    std::ifstream infile;
    std::string line = "";
    std::string childID = "";
    std::string childName = "";

    bool match = false;

    std::regex rxChildID("^id: (GO:[0-9]{7})");
    std::regex rxChildName("name: ([a-zA-z ]+)");
    std::regex is_a_split("(GO:[0-9]{7}) ! ([a-zA-z ]+)");
    std::regex rxId("^is_a: " + id);
    std::regex stop("^$");
    
    infile.open(filename);
    
    while (std::getline(infile, line)) {

        // record id of each entry and push previous
        if (std::regex_search(line, rxChildID)) {
            childID = std::regex_replace(line, rxChildID, "$1");
        }

        // record name of each entry
        if (std::regex_search(line, rxChildName)) {
            childName = std::regex_replace(line, rxChildName, "$1");
        }

        // check if entry is a child of searched id
        if (std::regex_search(line, rxId)) {
            match = true;            
        }
        
        // if we are at the end of an entry that is a child,
        // push info onto map
        if (std::regex_match(line, stop) && match) {
            match = false;

            children[childID] = childName;
        }

    }

    return (children);
};

// Coded this function by accident, decided to leave it in
std::map< std::string, std::string > GoUtil::getParents(std::string filename,
                                                         std::string id) {

    std::map< std::string, std::string > parents = {}; 
    std::map< std::string, std::string > entry = {}; 

    std::string is_a_string = "";

    std::regex is_a("is_a[0-9]+");
    std::regex is_a_split("(GO:[0-9]{7}) ! ([a-zA-z ]+)");

    entry = GoUtil::getEntry(filename, id);

    int i = 0;

    auto map_pos = entry.find("is_a" + std::to_string(i ++));

    while (map_pos != entry.end()) {

        is_a_string = map_pos->second;
        
        auto key = std::regex_replace(is_a_string, is_a_split, "$1");
        auto value = std::regex_replace(is_a_string, is_a_split, "$2");

        parents[key] = value;

        map_pos = entry.find("is_a" + std::to_string(i ++));

    }

    return (parents);
};


// Used for debugging with VScode
/* int main(int argc, char const *argv[])
{
    using namespace std;
    namespace fs = std::filesystem;
    
    GoUtil go_util = GoUtil();

    string file = "go.obo";
    string id = "GO:0000018";

    auto name  = go_util.getName(file, id);

    cout << "Name: " << name << "\n";

    auto is_obsole  = go_util.isObsolete(file, id);

    cout << "Is obsolete: " << is_obsole << "\n";

    auto children = go_util.getChildren(file, id);

    cout << "Children" << "\n";

    for (auto i : children) {
        cout << "\t" << i.first << "\t" << i.second << "\n";
    }
    
    auto parents = go_util.getParents(file, id);

    cout << "Parents" << "\n";

    for (auto i : parents) {
        cout << "\t" << i.first << "\t" << i.second << "\n";
    }

    return 0;
} */

