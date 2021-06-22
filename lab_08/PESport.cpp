# include "PESport.h"

# include <iostream>
# include <string>
# include <array>
# include <ctime>

using namespace std;

class PESport {
    public:

        int randint(int min, int max) {
            if (min == max) {
                return (min);
            }

            srand((int) time(NULL));

            int rnd = rand();

            int len = max - min;

            rnd = (rnd % len + 1) + min;

            return (rnd);
        }

        int pseudo2idx (int pseudo_idx) {
            int i, j;

            j = 0;

            // find the i'th unused aa
            for (i = 0; i <= pseudo_idx; i ++) {
                // skip over used amino acids between last i and next i
                while (aa_used[j]) {
                    j ++;
                }

                // when we have found the i'th unused aa, 
                j ++;
            }

            return (j);
        }

        int get_rnd_aa_idx() {

            /* this might be an example how not to do it, but to avoid long search
            times when many aas are already used, instead of repeatedly choosing a 
            random index in the aa array, a random number of maximally the number
            of unused aas is chosen. This number specifies the i'th unused aa.
            That index is then converted to the index of that aa in the pseudo2idx 
            function. */
            int pseudo_aa_idx = randint(0, n_aminos - n_aa_used - 1);

            int aa_idx = pseudo2idx(pseudo_aa_idx);

            if (n_aa_used >= n_aminos) {
                cout << "All Amino Acids used up!" << endl;

                // TODO: When we have a finishing function in place, call
                //  that instead of exiting.
                exit(1);
            }

            aa_used[aa_idx] = true;
            n_aa_used ++;

            return (aa_idx);
        }

        int find_aa_idx(string aa_code) {
            auto s_arr = sl_code;

            if (aa_code.length() > 2) {
                s_arr = tl_code;
            }

            for (int i = 0; i < n_aminos; i ++) {
                if (s_arr[i] == aa_code) {
                    return (i);
                }
            }

            cout << "Amino acid code was invalid." << endl;

            return (-1);
        }

        void setOpts () {
            string input;

            cout << "What option should be modified?" << endl;
            cout << "Input one of (n)umber of Tries, " << 
                "(t)ime for one guess, or (q)uit:" << endl;
            cin >> input;

            if (input == "q") {
                return;
            } else if (input == "n") {

                cout << "Current number of tries is " << maxTries <<
                    endl;

                cout << "How many tries do you want to do?" <<
                    // "(changing this will reset your score)" << 
                    endl;
                
                // TODO: Secure input here
                int new_tries;
                cin >> new_tries;

                /* 
                if (new_tries == maxTries) {
                    cout << "Number of tries has not changed" << endl;
                    return;
                } 
                 */

                maxTries = new_tries;

                cout << "Number of tries set to " << maxTime << "." << endl;

                return;

            } else if (input == "t") {
                cout << "Current time per try is " << maxTime <<
                    "s." << endl;

                cout << "How many seconds of time would you like" <<
                    " per try?" << endl;

                // TODO: Secure input here
                int new_time;
                cin >> new_time;

                /* 
                if (new_time == maxTime) {
                    cout << "Number of secpnds per try has not" <<
                    " changed..." << endl;
                    return;
                } 
                 */

                maxTime = new_time;

                cout << "Time per try set to " << maxTime << "s." << endl;

                return;
            } 

            return;
        } 

        void aaa2a() {
            int aa_idx = get_rnd_aa_idx();
            string rnd_code = tl_code[aa_idx];

            string ans;

            cout << "Random amino acid code is " << rnd_code << "." << endl;
            cout << "What is its one letter code? Enter below:" << endl;

            start_time();

            cin >> ans;

            bool in_time = check_time();

            if (ans == sl_code[aa_idx] && in_time) {
                cout << cols.green << "Correct! +1 point" << endl << cols.reset;

                score ++;

            } else if (ans == sl_code[aa_idx] && !in_time) {

                cout << cols.red << 
                    "Correct, but you did not manage it in time" <<
                    cols.reset << endl;

            } else {
                cout << cols.red << "Wrong!" << " Correct answer would have been " <<
                    sl_code[aa_idx] << endl << cols.reset;
            }
            
            return;
        }

        void a2aaa() {
            int aa_idx = get_rnd_aa_idx();
            string rnd_code = sl_code[aa_idx];

            string ans;

            cout << "Random amino acid code is " << rnd_code << "." << endl;
            cout << "What is its three letter code? Enter below:" << endl;

            start_time();

            cin >> ans;

            bool in_time = check_time();

            if (ans == sl_code[aa_idx] && in_time) {
                cout << cols.green << "Correct! +1 point" << endl << cols.reset;

                score ++;

            } else if (ans == sl_code[aa_idx] && !in_time) {

                cout << cols.red << 
                    "Correct, but you did not manage it in time" <<
                    cols.reset << endl;

            } else {
                cout << cols.red << "Wrong!" << " Correct answer would have been " <<
                    sl_code[aa_idx] << endl << cols.reset;
            }
            
            return;
        }

        void a2size () {
            int aa_idx = get_rnd_aa_idx();
            string rnd_code = sl_code[aa_idx];
            
            float ans;

            cout << "Random amino acid code is " << rnd_code << "." << endl;
            cout << "What is its molecular mass in g/mol?" <<
                " Enter below:" << endl;

            start_time();

            cin >> ans;

            bool in_time = check_time();

            float cor_ans = ml_mass[aa_idx];

            float up_lim = cor_ans + tol;
            float lo_lim = cor_ans - tol;

            float mw_score = 20 - abs(ans - cor_ans);

            if (ans > lo_lim && ans < up_lim && in_time) {

                cout << cols.green << "Correct! +" << mw_score << "point(s)!" <<
                    endl << cols.reset;
                    
                score += mw_score;
            } else if (ans > lo_lim && ans < up_lim && !in_time) {

                cout << cols.red << "Correct, but you were out of time." <<
                    " You would have gotten " << mw_score << " point(s)." <<
                    cols.reset << endl;

            } else if (ans < lo_lim || ans > up_lim) {
                cout << cols.red << "Wrong. The correct answer would have been " <<
                    cor_ans << "\u00B1" << tol << "." << endl << cols.reset;                
            }

            return;
        }

        void lookup_aa() {
            cout << "Enter a valid amino acid code, either in long " <<
                "or short form: " << endl;

            string aa_code;

            cin >> aa_code;

            int aa_idx = find_aa_idx(aa_code);

            if (aa_idx < 0) {
                return;
            }
            cout << "Data for amino acid with code " << aa_code << endl;

            printf("Long code\tShort code\tmol. mass [g/mol]\n");
            printf("%s\t\t%s\t\t%f\n", tl_code[aa_idx].c_str(), sl_code[aa_idx].c_str(),
                ml_mass[aa_idx]);

            return;
        }

        void menu(int n_qs) {
            int try_no;
            
            for (try_no = 1; try_no <= n_qs; try_no ++) {

                string choice = "";

                // check whether one of the options that consume a try is selected
                while (choice != "t" && choice != "s" && choice != "q" && choice != "i" &&
                        choice != "s") {
                    cout << "Try #" << try_no << ", choose (s)ingle letter," <<
                        " (t)riplett, s(i)ze, (l)ookup, (o)ptions, or (q)uit:" << endl;
                    cin >> choice;
                    cout << endl;

                    if (choice == "t") {
                        aaa2a();
                    } 
                    if (choice == "s") {
                        a2aaa();
                    } 
                    if (choice == "i") {
                        a2size();
                    }
                    if (choice == "l") {
                        lookup_aa();
                    }
                    if (choice == "q") {
                        break;
                    } 
                    if (choice == "o") {
                        setOpts();
                    }
                }

                // If we wish to quit, we also need to break out of this loop
                if (choice == "q") {
                    break;
                }

            }

            cout << "You did " << try_no << " tasks." << endl;
            cout << "You managed to score " << score << " points." << endl;
        }

    protected:

        // Record current time in object 
        // (at least i hope its in the object and not the class)
        void start_time() {
            last_start_time = time(NULL);

            cout << last_start_time << endl;
        }

        // check how much time has passed since the last call to 
        // start_time and compare with max allowed time
        bool check_time() {
            time_t diff_time = time(NULL) - last_start_time;

            if (diff_time <= maxTime) {
                return (true);
            }

            return (false);
        }

        // Coloring
        struct ANSII_col {
            string reset    = "\e[0m";
            string yellow   = "\e[0;33m";
            string green    = "\e[0;32m";
            string red      = "\e[0;31m";
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
        array<string, 20> sl_code{ "A", "C", "D", "E", "F", "G", "H", "I", "K",
                                    "L", "M", "N", "P", "Q", "R", "S", "T", "V",
                                    "W", "Y" };
        array<string, 20> tl_code{ "Ala", "Cys", "Asp", "Glu", "Phe", "Gly", "His", "Ile",
                                    "Lys", "Leu", "Met", "Asn", "Pro", "Gln", 
                                    "Arg", "Ser", "Thr", "Val", "Trp", "Tyr" };
        // according to this random website: https://www.webqc.org/aminoacids.php
        array<float, 20> ml_mass{ 89.0935, 121.1590, 133.1032, 147.1299, 165.1900, 
                                    155.1552, 131.1736, 146.1882, 131.1736,
                                    149.2124, 132.1184, 115.1310, 146.1451, 
                                    174.2017, 105.0930, 119.1197, 117.1469,
                                    204.2262, 181.1894 };

        int n_aminos = sizeof(sl_code) / sizeof(sl_code[0]);

        array<bool, 20> aa_used = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0 };
        int n_aa_used = 0;

};

