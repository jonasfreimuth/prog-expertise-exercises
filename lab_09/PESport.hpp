# ifndef PESPORT_HPP
#  define PESPORT_HPP

# include <string>
# include <array>

class PESport {
    public:

        int randint(int min, int max);

        int pseudo2idx(int pseudo_idx);

        int get_rnd_aa_idx();

        int find_aa_idx(std::string aa_code);

        void setOpts (); 

        void aaa2a();

        void a2aaa();

        void a2size ();

        void lookup_aa();

        void menu(int n_qs);

    protected:

        // Record current time in object 
        // (at least i hope its in the object and not the class)
        void start_time();

        // check how much time has passed since the last call to 
        // start_time and compare with max allowed time
        bool check_time();

        // Coloring
        struct ANSII_col {
            std::string reset    = "\e[0m";
            std::string yellow   = "\e[0;33m";
            std::string green    = "\e[0;32m";
            std::string red      = "\e[0;31m";
        };

        ANSII_col cols;

        // Options
        int maxTries = 10;
        int maxTime = 5;
        float tol = 20;

        // Scoring system
        float score;
        time_t last_start_time;


        // Data and associated vars
        std::array<std::string, 20> sl_code = { "A", "C", "D", "E", "F", "G", "H", "I", "K",
                                    "L", "M", "N", "P", "Q", "R", "S", "T", "V",
                                    "W", "Y" };
        std::array<std::string, 20> tl_code = { "Ala", "Cys", "Asp", "Glu", "Phe", "Gly", "His", "Ile",
                                    "Lys", "Leu", "Met", "Asn", "Pro", "Gln", 
                                    "Arg", "Ser", "Thr", "Val", "Trp", "Tyr" };
        // according to this random website: https://www.webqc.org/aminoacids.php
        std::array<float, 20> ml_mass = { 89.0935, 121.1590, 133.1032, 147.1299, 165.1900, 
                                    155.1552, 131.1736, 146.1882, 131.1736,
                                    149.2124, 132.1184, 115.1310, 146.1451, 
                                    174.2017, 105.0930, 119.1197, 117.1469,
                                    204.2262, 181.1894 };

        int n_aminos = sizeof(sl_code) / sizeof(sl_code[0]);

        std::array<bool, 20> aa_used = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0 };
        int n_aa_used = 0;

};



# endif