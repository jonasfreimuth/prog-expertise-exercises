// TODO: Set the correct names
# ifndef CLASS_HPP
    # define CLASS_HPP

# include <string>
# include <vector>

class jf_FASTA_parser {
    public:
        std::vector< std::tuple< std::string, std::string, std::string > > getN (std::string filename);
        std::vector< std::tuple< std::string, std::string, std::string > > getSeq (std::string filename, std::string id);
        std::vector< std::tuple< std::string, std::string, std::string > > grepSeq (std::string filename, std::string id);

};

# endif