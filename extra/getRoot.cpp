# include <iostream>
# include <regex>
# include <map>
# include <vector>
# include <fstream>
# include <filesystem>

# include "argparse.hpp"

std::map<std::string, std::string> getEntry(std::string filename, std::string id) {  

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

std::map< std::string, std::string > getChildren(std::string filename,
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

std::map< std::string, std::string > getParents(std::string filename,
                                                         std::string id) {

    std::map< std::string, std::string > parents = {}; 
    std::map< std::string, std::string > entry = {}; 

    std::string is_a_string = "";

    std::regex is_a("is_a[0-9]+");
    std::regex is_a_split("(GO:[0-9]{7}) ! ([a-zA-z ]+)");

    entry = getEntry(filename, id);

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

int main(int argc, char const *argv[]) {

    using namespace std;
    namespace fs = std::filesystem;

    vector< string > commands = { "getEntry", "getChildren", "getParents" };

    argparse::ArgumentParser parser("GoUtil: Gene Ontology .obo file utilities");
    
    parser.add_argument("-f", "--filename")
        .help("Specify filename of the .obo file")
        .required()
        .action([](const std::string& value) {
                if (!fs::exists(value)) {
                    cout << "File " << value << " does not exist!\n";
                    exit(1);
                }
                return (value); 
            });

    parser.add_argument("-i", "--id")
        .help("Which OBO Id to look for")
        .required()
        .action([](const std::string& value) {
            if (!regex_match(value, regex("^GO:[0-9]{7}$"))) {
                std::cerr << "Supplied id " << value << " is not a valid GO Id.\n";
                std::exit(1); 
            }

            return (value);
        });

    string command_help = "Specify which command to execute. One of ";

    // construct help string from vector of allowed commands
    for (auto i = commands.begin(); i != commands.end(); i ++) {
        command_help = command_help + * i;

        if (i + 1 != commands.end()) {
            command_help = command_help + ", ";
        }
    }

    parser.add_argument("-c", "--command")
        .help(command_help)
        .default_value((string) "")
        .action([commands](const std::string& value) {
            // check if command is represented in list of commands
            if (find(commands.begin(), commands.end(), value) != commands.end()) {                
                return (value);
            }
            cerr << "Unknown command " << value << ".\n";
            
            exit(1);

            // token return statement
            return ((string) "");
        });

    try {
        parser.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << parser;
        exit(0);
    }

    std::string command = parser.get<std::string>("--command");
    std::string filename = parser.get<std::string>("--filename");
    std::string id = parser.get<std::string>("--id");

    if (command == "getEntry") {

        auto entry  = getEntry(filename, id);

        cout << "The entry matching " << id << " is:\n";
        
        for (auto i : entry) {
            cout << i.first << ": " << i.second << "\n";
        }

    } else if (command == "getChildren") {

        auto children = getChildren(filename, id);

        cout << "Children" << "\n";

        for (auto i : children) {
            cout << "\t" << i.first << "\t" << i.second << "\n";
        }

    } else if (command == "getParents") {
        
        auto parents = getParents(filename, id);

        cout << "Parents" << "\n";

        for (auto i : parents) {
            cout << "\t" << i.first << "\t" << i.second << "\n";
        }
    }

    return 0;
}