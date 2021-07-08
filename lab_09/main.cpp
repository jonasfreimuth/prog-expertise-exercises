# include "XPESport.hpp"
# include "argparse.hpp"

/* // used for debugging with vscode
# include "XPESport.cpp" */

int main(int argc, char const *argv[]) {

    /* for (int i = 0; i < argc; i ++) {
        std::cout << "Arg " << i << " is " << argv[i] <<
            std::endl;
    } */

    argparse::ArgumentParser parser("XPESport");

    parser.add_argument("-n", "--ntries")
        .help("Specify number of games you wish to play.")
        .default_value(10)
        .action([](const std::string& value) { 
            return std::stoi(value);
            });

    parser.add_argument("-t", "--triple")
        .help("Only do triple letter exercises.")
        .default_value(false)
        .implicit_value(true);

    parser.add_argument("-s", "--single")
        .help("Only do single letter exercises.")
        .default_value(false)
        .implicit_value(true);

    parser.add_argument("-p", "--hydropathy")
        .help("Only do hydropathy exerxises.")
        .default_value(false)
        .implicit_value(true);

    parser.add_argument("-m", "--molmass")
        .help("Only do mol. mass guessing exercises.")
        .default_value(false)
        .implicit_value(true);

    try {
        parser.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << parser;
        exit(0);
    }

    auto pe = XPESport();

    int n_try = parser.get<int>("--ntries");


    std::string only_task = "";

    if (parser["--triple"] == true) {
        only_task = "t";
    }
    if (parser["--single"] == true) {
        only_task = "s";
    }
    if (parser["--hydropathy"] == true) {
        only_task = "h";
    }
    if (parser["--molmass"] == true) {
        only_task = "i";
    }    

   pe.menu(n_try, only_task);

    return 0;
}