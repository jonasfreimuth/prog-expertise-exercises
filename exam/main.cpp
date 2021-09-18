# include <iostream>
# include <filesystem>
# include <regex>

# include "argparse.hpp"
// TODO: Include correct class
# include "class.hpp"

int main(int argc, char const *argv[]) {

    using namespace std;
    namespace fs = std::filesystem;

    vector< string > valid_commands = { "cmdA", "cmdB" };

    // TODO: Fit correct name
    argparse::ArgumentParser parser("PROGRAM.bin");
    
    parser.add_argument("-f", "--files")
        .help("Specify filenames of the .obo files."
            " All trailing arguments will be interpreted as such.")
        .required()
        .remaining();

    parser.add_argument("-i", "--id")
        // TODO: If time allows, specify patterns
        .help("Which Id to look for. "
            "Multiple ids must be prepended with -i or --id again.")
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

    vector< string > ids = {};
    
    // get ids and check validity
    try {  
        // ids are only retrieved if required by the command
        ids = parser.get<vector<string>>("--id");      

        for (auto id = ids.begin(); id != ids.end(); id ++) {

            // TODO: fill in appropriate command
            if (find(commands.begin(), commands.end(), valid_commands[0]) != commands.end()) {
                // TODO: Put in appropirate pattern
                if (!regex_match( * id, regex("PATTERN"))) {
                        cout << "ID " << * id << " is not valid!\n";
                        exit(1);
                }
            } else {
                // TODO: Extend if different commands require different ids
            }
        }

    } catch (std::logic_error& e) {
        std::cout << "No ids supplied." << std::endl;
    }

    auto tmp_object = TmpClass();

    // TODO: Ensure the types fit
    vector< tuple< string, string, string > > res = {};
    vector< tuple< string, string, string > > tmp_res = {};

    for (auto cmd = commands.begin(); cmd != commands.end(); cmd ++) {
        if (* cmd == valid_commands[0]) {
            for (auto file = files.begin(); file != files.end(); file ++) {
                
                for (auto id = ids.begin(); id != ids.end(); id ++) {
                    tmp_res = tmp_object.tmp_function(* file, * id);                    
                    res.insert(res.end(), tmp_res.begin(), tmp_res.end());
                }               
            }
        } else if (* cmd == "") {
            // TODO: Expand for more commands
        }
    }

    cout << "length of res is " << res.size() << "\n";

    // print results
    for (auto entry = res.begin(); entry != res.end(); entry ++) {
        cout << get<0>( * entry) << "\t" << get<1>( * entry) << "\t" << get<2>( * entry) << "\n";
    }

    return 0;
}
