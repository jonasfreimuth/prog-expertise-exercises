# include <string>
# include <vector>
# include <regex>

# include <iostream>

namespace jfutils {

    bool grepl(std::vector<std::string> string_vec, const std::string pattern) {

        return false;

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

}


int main(int argc, char const *argv[])
{
    std::vector<bool> bool_vec = { 0, 0, 0, 0 };

    std::cout << jfutils::any(bool_vec) << "\n";

    return 0;
}

