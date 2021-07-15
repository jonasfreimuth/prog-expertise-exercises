# include <iostream>
# include <filesystem>

# include "argparse.hpp"
# include "jf-GoUtil.hpp"

int main(int argc, char const *argv[]) {

    using namespace std;
    namespace fs = std::filesystem;

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
            // TODO: Check for validity of ID
            return (value);
        });

    try {
        parser.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << parser;
        exit(0);
    }

    std::string filename = parser.get<std::string>("--filename");
    std::string id = parser.get<std::string>("--id");

    GoUtil go_util = GoUtil();

    auto entry  = go_util.getEntry(filename, id);
    auto name   = go_util.getName(filename, id);
    auto is_obs = go_util.isObsolete(filename, id);

    cout << "The entry matching " << id << " is:\n";
    
    /* for (auto i : entry) {
        cout << i.first() << ": " << i.second() << "\n";
    } */

    cout << "Name of " << id << " is " << name << "\n";

    return 0;
}
