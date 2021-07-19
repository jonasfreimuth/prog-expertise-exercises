# include <iostream>
# include <filesystem>
# include <regex>

# include "argparse.hpp"
# include "jf-GoUtil.hpp"

int main(int argc, char const *argv[]) {

    using namespace std;
    namespace fs = std::filesystem;

    std::string commands = "getEntry, getName, getChildren, getParents, isObsolete";

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
                cerr << "Supplied if " << value << " is not a valid GO Id.\n";
                exit(1); 
            }

            return (value);
        });

    parser.add_argument("-c", "--command")
        .help("Specify which command to execute. One of " + commands)
        .default_value("")
        .action([commands](const std::string& value) {
            if (!regex_search(commands, regex(value))) {
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

    GoUtil go_util = GoUtil();

    if (command == "getEntry") {

        auto entry  = go_util.getEntry(filename, id);

        cout << "The entry matching " << id << " is:\n";
        
        for (auto i : entry) {
            cout << i.first << ": " << i.second << "\n";
        }

    } else if (command == "getName") {

        auto name   = go_util.getName(filename, id);

        cout << "Name of " << id << " is " << name << "\n";

    } else if (command == "isObsolete") {

        auto is_obs = go_util.isObsolete(filename, id);

        cout << "Is obsolete: " << is_obs << "\n";

    } else if (command == "getChildren") {

        auto children = go_util.getChildren(filename, id);

        cout << "Children" << "\n";

        for (auto i : children) {
            cout << "\t" << i.first << "\t" << i.second << "\n";
        }

    } else if (command == "getParents") {
        
        auto parents = go_util.getParents(filename, id);

        cout << "Parents" << "\n";

        for (auto i : parents) {
            cout << "\t" << i.first << "\t" << i.second << "\n";
        }

    }

    return 0;
}
