# include <string>
# include <vector>
# include <tuple>

# include "class.hpp"

std::vector< std::tuple< std::string, std::string, std::string > > TmpClass::tmp_function (std::string filename, std::string input) {

            std::vector< std::tuple< std::string, std::string, std::string > > output = { };

            output.push_back( std::make_tuple( filename, input, input ) );

            return (output);
        }