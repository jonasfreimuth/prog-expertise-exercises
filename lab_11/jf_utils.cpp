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

    std::vector<bool> bool_vec = { 1, 1, 1, 0 };

    std::cout << "Any: " << jfutils::any(bool_vec) << "\n";

    std::cout << "All: " << jfutils::all(bool_vec) << "\n";

    return 0;
}

