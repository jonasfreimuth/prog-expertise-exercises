# include <iostream>
# include <filesystem>
# include <fstream>
# include <regex>
# include <map>

# include "argparse.hpp"
// TODO: Include correct class
// # include "class.hpp"

std::string getInfo(std::string filename, std::string id) {  

    std::ifstream infile; 
    std::string line = "";

    std::string entry = {};
    bool match = false;

    std::regex rxId(id);
    std::regex stopEntry("^$");

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

                // if we had found the entry we were looking for
                // we dont need to look further
                break;
            }
        }

        if (match) {

            entry = entry + line + "\n" ;

        }
    }

    return (entry);
};

std::map< std::string, std::string > searchEC(std::string filename,
                                                         std::string id) {

    std::map< std::string, std::string > ec_match;
    std::ifstream infile;
    std::string line = "";
    std::string xrefGOID = "";
    std::string xrefName = "";

    bool match = false;

    std::regex rxxrefGOID("^id: (GO:[0-9]{7})");
    std::regex rxxrefName("name: ([a-zA-z ]+)");
    std::regex rxId("^xref: " + id);
    std::regex stop("^$");

    std::cout << "Looking for pattern \"^xref: " << id << "\"\n";
    
    infile.open(filename);
    
    while (std::getline(infile, line)) {

        // record id of each entry
        if (std::regex_search(line, rxxrefGOID)) {
            xrefGOID = std::regex_replace(line, rxxrefGOID, "$1");
        }

        // record name of each entry
        if (std::regex_search(line, rxxrefName)) {
            xrefName = std::regex_replace(line, rxxrefName, "$1");
        }

        // check if entry is a child of searched id
        if (std::regex_search(line, rxId)) {
            match = true;            
        }
        
        // if we are at the end of an entry that is a child,
        // push info onto map
        if (std::regex_match(line, stop) && match) {
            match = false;

            ec_match[xrefGOID] = xrefName;
        }

    }

    return (ec_match);
};

int main(int argc, char const *argv[]) {

    using namespace std;
    namespace fs = std::filesystem;

    std::string commands = "searchEC, getInfo";

    argparse::ArgumentParser parser("GO-Obo Parser: Extract information from Gene "
                                    "Ontology .obo files.");
    
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
        .default_value("");

    parser.add_argument("-c", "--command")
        .help("Specify which command to execute. One of " + commands)
        .required()
        .action([commands](const std::string& value) {
            if (!regex_search(commands, regex(value))) {
                cerr << "Unknown command " << value << ".\n";
                exit(1);
            }
            return (value);
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

    if (command == "getInfo" && id == "") {
        cerr << "Command getInfo requires a goId.\n";
        exit(1);
    }

    if (command == "getInfo") {

        if (!regex_match(id, regex("^GO:[0-9]{7}$"))) {
            cerr << "Supplied id " << id << " is not a valid GO Id.\n";
            exit(1); 
        }

        auto entry = getInfo(filename, id);

        cout << entry << "\n";

    } else if (command == "searchEC") {

        if (!regex_match(id, regex("^EC:[0-9\.]*$"))) {
            cerr << "Supplied id " << id << " is not a valid EC Id.\n";
            exit(1); 
        }

        auto entries = searchEC("go-basic.obo", "EC:2.4.1");

        for (auto i = entries.begin(); i != entries.end(); i ++) {
            cout << i->first << "\t" << i->second << "\n";
        }

    } else {
        cerr << "Unknown command " << command << ".\n";
        exit(1);
    }

    return 0;
}
