# include <iostream>
# include <filesystem>
# include <fstream>
# include <string>
# include <vector>
# include <tuple>
# include <regex>

# include "argparse.hpp"

class GooboParser {
    public:
        std::vector< std::tuple< std::string, std::string, std::string > > getSlimTab (std::string filename, std::string search_slim) {

            // std::cout << search_slim << "\n";

            std::vector< std::tuple< std::string, std::string, std::string > > output = {};

            std::ifstream infile;
            std::string line = "";

            std::regex rxStop("^$");
            std::regex rxGoId("^id: (GO:[0-9]{7})$");
            std::regex rxName("^name: ([A-Za-z ]+)$");
            std::regex rxSlim("^subset: goslim_([a-z]+)$");

            if (search_slim != "") {        
                rxSlim = std::regex("^subset: goslim_(" + search_slim + ")$");
            }

            std::string id = "";
            std::string slim = "";
            std::string name = "";

            // TODO disable debug
            int i = 0;
            int k = 10000;
            
            infile.open(filename);
            
            while (std::getline(infile, line)) {
                // save every id and name
                if (std::regex_search(line, rxGoId)) {
                    id = std::regex_replace(line, rxGoId, "$1");   
                    // std::cout << "ID: " << id << "\n";         
                }

                if (std::regex_search(line, rxName)) {
                    name = std::regex_replace(line, rxName, "$1");
                    // std::cout << "Name: " << name << "\n";
                }

                // if it is the right slim, save it onto output
                if (std::regex_search(line, rxSlim)) {
                    slim = std::regex_replace(line, rxSlim, "$1");
                    // std::cout << "Slim: " << slim << "\n";

                    output.push_back( std::make_tuple( id, name, slim ));
                }

                // if we are at a new entry, reset name and id
                // may not be needed
                if (std::regex_search(line, rxStop)) {
                    name = "";
                    id = "";
                }  

                // TODO: disable debug
                i ++;
                if (i > k) break; 
            }

            infile.close();

            return (output); 
        }

    std::vector< std::tuple< std::string, std::string, std::string > > getSlimStats (std::string filename, std::string search_slim) {
        
            std::vector< std::tuple< std::string, std::string, std::string > > output = {};

            std::map< std::string, int > nmspc_count;

            std::ifstream infile;
            std::string line = "";

            std::regex rxNmspc("^namespace: ([a-z_]+)$");
            std::regex rxSlim("^subset: goslim_([a-z]+)$");
            std::regex rxStop("^$");

            if (search_slim != "") {        
                rxSlim = std::regex("^subset: goslim_(" + search_slim + ")$");
            }

            std::string nmspc = "";
            std::string slim = "";

            /* // TODO: Disable debug
            int i = 0;
            int k = 10000; */
            
            infile.open(filename);
            
            while (std::getline(infile, line)) {
                // record every namespace
                if (std::regex_search(line, rxNmspc)) {
                    nmspc = std::regex_replace(line, rxNmspc, "$1");
                }

                // check if slim is present
                if (std::regex_search(line, rxSlim)) {
                    slim = std::regex_replace(line, rxSlim, "$1");

                    // if so update counter or intialize it
                    if (nmspc_count.find(nmspc) == nmspc_count.end()) {
                            nmspc_count[nmspc] = 1;
                        } else {
                            nmspc_count[nmspc] ++;
                        }
                }

                // reset on stop
                if (std::regex_search(line, rxStop)) {
                    nmspc = "";
                    slim = "";
                }                

                /* // TODO: disable debug
                i ++;
                if (i > k) break; */
            }

            // for every slim, push counts onto output
            for (auto i = nmspc_count.begin(); i != nmspc_count.end(); i ++) {
                output.push_back( std::make_tuple( std::to_string(i->second), i->first, search_slim ) );
            }
             
            infile.close();

            return (output);
        }
};




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
        cout << "Example call: ./GooboParser3.bin -c getSlimStats -i yeast -i plant  -f go.obo\n";
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
                        cerr << "ID " << * id << " is not valid!\n";
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

    auto obo_parser = GooboParser();

    for (auto cmd = commands.begin(); cmd != commands.end(); cmd ++) {
        /* cout << * cmd << "\n"; */
        if (* cmd == "getSlimTab") {
            for (auto file = files.begin(); file != files.end(); file ++) {
                /* cout << * file << "\n"; */
                for (auto id = ids.begin(); id != ids.end(); id ++) {
                    /* cout << "Calling getSlimTab " << * id << "\n"; */
                    tmp_res = obo_parser.getSlimTab(* file, * id);                    
                    res.insert(res.end(), tmp_res.begin(), tmp_res.end());
                }               
            }
        } else if (* cmd == "getSlimStats") {
            for (auto file = files.begin(); file != files.end(); file ++) {
                /* cout << * file << "\n"; */
                for (auto id = ids.begin(); id != ids.end(); id ++) {
                    /* cout << "Calling getSlimStats " << * id << "\n"; */
                    tmp_res = obo_parser.getSlimStats(* file, * id);                    
                    res.insert(res.end(), tmp_res.begin(), tmp_res.end());
                }               
            }
        }
    }

    // print results
    for (auto entry = res.begin(); entry != res.end(); entry ++) {
        cout << get<0>( * entry) << "\t" << get<1>( * entry) << "\t" << get<2>( * entry) << "\n";
    }

    return 0;
}
