# include <iostream>
# include <filesystem>
# include <vector>
# include <tuple>
# include <regex>

# include "argparse.hpp"

int main(int argc, char const *argv[]) {

    using namespace std;
    namespace fs = std::filesystem;

    vector< string > valid_commands = { "getSlimTab", "getSlimStats" };
    vector< string > valid_slims = { "generic", "pir", "plant", "pombo", "yeast" };

    // TODO: Fit correct name
    argparse::ArgumentParser parser("GooboParser1.bin");
    
    parser.add_argument("-f", "--files")
        .help("Specify filenames of the .obo files."
            " All trailing arguments will be interpreted as such.")
        .required()
        .remaining();    
    
    string slims_help = "Which GO slim to look for. One of ";

    for (auto i = valid_slims.begin(); i != valid_slims.end(); i ++) {
        slims_help = slims_help + * i;

        if (i + 1 != valid_slims.end()) {
            slims_help = slims_help + ", ";
        }
    }

    parser.add_argument("-i", "--id")
        .help(slims_help + 
            " Multiple slims must be prepended with -i or --id again.")
        .append();

    string command_help = "Specify which command to execute. One of ";

    for (auto i = valid_commands.begin(); i != valid_commands.end(); i ++) {
        command_help = command_help + * i;

        if (i + 1 != valid_commands.end()) {
            command_help = command_help + ", ";
        }
    }

    parser.add_argument("-c", "--command")
        .help(command_help + " Multiple commands must be prepended with -c or --command again.")
        .append()
        .required();

    try {
        parser.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        cout << "Example call: ./GooboParser1.bin -c getSlimStats -i yeast -f go.obo\n";
        std::cout << err.what() << std::endl;
        std::cout << parser;
        exit(0);
    }

    vector< string > commands = {};
    
    // get commands and check validity
    try {
        commands = parser.get<std::vector<std::string>> ("--command");
        
        for (auto& cmd : commands) {
            if (find(valid_commands.begin(), valid_commands.end(), cmd) == valid_commands.end()) {
                    cout << "Command " << cmd << " is not valid!\n";
                    exit(1);
                }
        }
    } catch (std::logic_error& e) {
        std::cout << "No commands provided" << std::endl;
    }
    
    std::vector<std::string> files = {};

    // get files and check validity
    try {
        files = parser.get<std::vector<std::string>>("--files");
        
        for (auto& file : files) {
            if (!fs::exists(file)) {
                    cout << "File " << file << " does not exist!\n";
                    exit(1);
                }
        }
    } catch (std::logic_error& e) {
        std::cout << "No files provided" << std::endl;
    }

    vector< string > ids = { "" };
    
    // get ids and check validity
    if (parser.is_used("--id")) {   
        try {  
            ids = parser.get<vector<string>>("--id");      

            for (auto id = ids.begin(); id != ids.end(); id ++) {

                if (find(commands.begin(), commands.end(), "getSlimTab") != commands.end()) {

                    if (find(valid_slims.begin(), valid_slims.end(), * id) == valid_slims.end()) {
                        cout << "ID " << * id << " is not valid!\n";
                        exit(1);
                    }
                }
            }

        } catch (std::logic_error& e) {
            std::cout << "No ids supplied." << std::endl;
        }
    }

    // TODO: Ensure the types fit
    vector< tuple< string, string, string > > res = {};
    vector< tuple< string, string, string > > tmp_res = {};

    for (auto cmd = commands.begin(); cmd != commands.end(); cmd ++) {
        if (* cmd == "getSlimTab") {
            for (auto file = files.begin(); file != files.end(); file ++) {
                
                for (auto id = ids.begin(); id != ids.end(); id ++) {
                    /* tmp_res = getSlimTab(* file, * id);                    
                    res.insert(res.end(), tmp_res.begin(), tmp_res.end()); */
                }               
            }
        } else if (* cmd == "") {
            // TODO: Expand for more commands
        }
    }

    // print results
    for (auto entry = res.begin(); entry != res.end(); entry ++) {
        cout << get<0>( * entry) << "\t" << get<1>( * entry) << "\t" << get<2>( * entry) << "\n";
    }

    return 0;
}
