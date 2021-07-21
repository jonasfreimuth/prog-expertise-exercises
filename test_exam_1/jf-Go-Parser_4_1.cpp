# include <iostream>
# include <filesystem>
# include <regex>

# include "argparse.hpp"
// TODO: Include correct class
// # include "class.hpp"

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

    /* parser.add_argument("-i", "--id")
        .help("Which OBO Id to look for")
        .required()
        .action([](const std::string& value) {
            if (!regex_match(value, regex("^GO:[0-9]{7}$"))) {
                cerr << "Supplied id " << value << " is not a valid GO Id.\n";
                exit(1); 
            }

            return (value);
        }); */

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

    return 0;
}
