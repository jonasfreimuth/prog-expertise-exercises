# include <iostream>
# include <regex>
# include <string>
# include <map>
# include <filesystem>
# include <fstream>

# include "argparse.hpp"

std::map< std::string, int > getSummary(std::string filename, 
                                                std::string nmspace) {
    std::ifstream infile;
    std::string line = "";

    std::regex rxNmspace("^namespace: " + nmspace);
    std::regex rxObs("^is_obsolete: true");

    bool match = false;
    bool is_obs = false;

    int non_obs = 0;
    int     obs = 0;

    std::map< std::string, int > res = {};
    
    infile.open(filename);
    
    while (std::getline(infile, line)) {
        
        // check if current entry is in namespace
        if (std::regex_search(line, rxNmspace)) {
            match = true;
            is_obs = false;
        }

        // check if current entry is obsolete
        if (std::regex_search(line, rxObs)) {
            is_obs = true;
        }

        // if entry is finished and not obsolete, count that
        if (line.empty() && match) {
            if (is_obs) {
                obs ++;
            } else {
                non_obs ++;
            }
        }
    }

    infile.close();

    res["is_obsolete"] = obs;
    res["non_obsolete"] = non_obs;

    return (res);
};

std::map< std::string, int > getECSummary(std::string filename, 
                                                std::string nmspace) {

    std::ifstream infile;
    std::string line = "";
    std::string EC_stub = "";

    std::regex rxXref("^xref: (EC:[0-9]+\\.[0-9]+).+");

    std::map< std::string, int > res = {};
    
    infile.open(filename);
    
    while (std::getline(infile, line)) {
        
        if (std::regex_search(line, rxXref)) {
            EC_stub = std::regex_replace(line, rxXref, "$1");

            if (res.find(EC_stub) == res.end()) {
                res[EC_stub] = 1;
            } else {
                res[EC_stub] ++;
            }
        }
        
    }

    infile.close();
                                                
    return (res); 
}

int main(int argc, char const *argv[]) {

    using namespace std;
    namespace fs = std::filesystem;

    std::string commands = "summary, ECSummary";
    std::string namespaces = "molecular_function, cellular_component,"
        " biological_process";    
    
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

    parser.add_argument("-n", "--nmspace")
        .help("For summary a namespace to summarise")
        .default_value("")
        .action([namespaces](const std::string& value) {
            if (!regex_search(namespaces, regex(value))) {
                cerr << "Unknown namespace " << value << ".\n";
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

    std::string nmspace = "";
    if (parser.is_used("--nmspace")) {
        nmspace = parser.get<std::string>("--nmspace");
    }

    std::vector<std::string> files = {};

    // get files and check validity
    try {
        files = parser.get<std::vector<std::string>>("files");
        
        for (auto& file : files) {
            if (!fs::exists(file)) {
                    cout << "File " << file << " does not exist!\n";
                    exit(1);
                }
        }
    } catch (std::logic_error& e) {
        std::cout << "No files provided" << std::endl;
    }

    for (auto& file : files) {

        if (command == "summary") {
            if (nmspace == "empty") {
                cerr << "No namespace provided.\n";
                exit(1);
            }
                    
            auto summary = getSummary(file, nmspace);

            for (auto i = summary.begin(); i != summary.end(); i ++) {
                cout << file << "\t" << i->first << "\t" << i->second << "\n";
            }

        } else if (command == "ECSummary") {

            auto summary = getECSummary(file, nmspace);
            
            for (auto i = summary.begin(); i != summary.end(); i ++) {
                cout << file << "\t" << i->first << "\t" << i->second << "\n";
            }
        }
    }

    return 0;
}
