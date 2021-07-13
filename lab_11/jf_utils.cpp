# include <string>
# include <vector>
# include <regex>

# include <iostream>

namespace jfutils {    

    bool grepl(std::string str, const std::string pattern) {

        bool out;
            
        auto match = std::regex_search(str, std::regex(pattern));

        out = match;

        return out;

    }

    std::vector<bool> grepl(std::vector<std::string> string_vec, const std::string pattern) {

        std::vector<bool> out_vec;

        for (auto i : string_vec) {
            auto match = std::regex_search(i, std::regex(pattern));

            out_vec.push_back(match);
        }       

        return out_vec;

    }

    std::string gsub(const std::string pattern,
                        const std::string replacement,
                        std::string x) {

        std::string out;

        out = std::regex_replace(x, std::regex(pattern), replacement);

        return(out);
    }

    std::vector<std::string> gsub(const std::string pattern,
                                    const std::string replacement,
                                    std::vector<std::string> x) {
        
        std::vector<std::string> out = {  };
        std::string sub = "";

        for (auto i : x) {

            std::string sub = std::regex_replace(i, std::regex(pattern), replacement);

            out.push_back(sub);
        }

        return(out);
    }

    bool any(std::vector<bool> x) {

        int sum = 0;

        for (auto i : x) {
            if (i == true) {
                sum ++;
            }
        }

        return(sum > 0);

    }

    bool all(std::vector<bool> x) {

        int sum = 0;

        for (auto i : x) {
            if (i == true) {
                sum ++;
            }
        }

        return(sum == x.size());

    }

}


int main(int argc, char const *argv[]) {

    using namespace std;

    string str = "Applesauce";

    // Grepl
    cout << "Grepl string: " << jfutils::grepl(str, "pp") <<
        endl;

    std::vector<std::string> string_vec = { "Yes",
                                            "No",
                                            "Maybe"};

    vector<bool> grepl_vec = jfutils::grepl(string_vec, "e");

    cout << "Grepl vector: " << endl;

    for (auto i : grepl_vec) {
        cout << "\t" << i << endl;
    }

    // Gsub
    cout << "Gsub string: " << jfutils::gsub("e", "*", str) <<
        endl;

    vector<string> gsub_vec = jfutils::gsub("e", "*", string_vec);

    cout << "Gsub vector: " << endl;

    for (auto i : gsub_vec) {        
        cout << "\t" << i << endl;
    }

    // Any All
    std::vector<bool> bool_vec = { 1, 1, 1, 0 };

    std::cout << "Any: " << jfutils::any(bool_vec) << "\n";

    std::cout << "All: " << jfutils::all(bool_vec) << "\n";

    return 0;
}

