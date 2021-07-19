# ifndef JFGOUTIL_H
    # define JFGOUTIL_H

# include <iostream>
# include <string>

class GoUtil {
    public:

        std::map< std::string, std::string > getEntry(std::string filename,
                                                        std::string id);

        std::string getName(std::string filename, std::string id);

        bool isObsolete(std::string filename, std::string id);

        std::map< std::string, std::string > getChildren(std::string filename,
                                                            std::string id);
                                                            
        std::map< std::string, std::string > getParents(std::string filename,
                                                         std::string id);
};

# endif