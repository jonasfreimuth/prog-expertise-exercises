# ifndef PESPORT_H
#  define PESPORT_H

# include <string>
# include <array>

class PESport {
    public:

        int randint(int min, int max);

        int pseudo2idx;

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
            std::string reset;
            std::string yellow;
            std::string green;
            std::string red;
        };

        // Options
        int maxTries;
        int maxTime;
        float tol;

        // Scoring system
        float score;
        time_t last_start_time;

        // Data and associated vars
        std::array<std::string, 20> sl_code;
        std::array<std::string, 20> tl_code;
        // according to this random website: https://www.webqc.org/aminoacids.php
        std::array<float, 20> ml_mass;

        int n_aminos;

        std::array<bool, 20> aa_used;
        int n_aa_used;

};



# endif