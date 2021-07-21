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

int main(int argc, char const *argv[]) {

    using namespace std;
    namespace fs = std::filesystem;

    std::string commands = "searchEC, getInfo";

    // TODO: Fit correct name
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
        .default_value("")
        .action([](const std::string& value) {
            if (!regex_match(value, regex("^GO:[0-9]{7}$"))) {
                cerr << "Supplied id " << value << " is not a valid GO Id.\n";
                exit(1); 
            }

            return (value);
        });

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
        auto entry = getInfo(filename, id);

        cout << entry << "\n";
    }

    return 0;
}
