# include <iostream>
# include <regex>
# include <string>
# include <vector>
# include <filesystem>

# include "argparse.hpp"

int main(int argc, char const *argv[]) {

    using namespace std;
    namespace fs = std::filesystem;

    std::string commands = "summary, ECsummary";
    
    argparse::ArgumentParser parser("jf-Go-Util");
    
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

    parser.add_argument("files")
        .remaining()
        .required();

    try {
        parser.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cout << "Gene Ontology Obofile Parser by Jonas\n";
        std::cout << err.what() << std::endl;
        std::cout << parser;
        exit(0);
    }

    std::string command = parser.get<std::string>("--command");

    // get files and check validity
    try {
        auto files = parser.get<std::vector<std::string>>("files");
        
        for (auto& file : files) {
            if (!fs::exists(file)) {
                    cout << "File " << file << " does not exist!\n";
                    exit(1);
                }
        }
    } catch (std::logic_error& e) {
        std::cout << "No files provided" << std::endl;
    }

    return 0;
}
