# include <iostream>
# include "PESport.h"
# include "XPESport.h"

using namespace std;

class XPESport : public PESport {

    public:   

        void menu(int n_qs) {
            int try_no;
            
            for (try_no = 1; try_no <= n_qs; try_no ++) {

                string choice = "";

                // check whether one of the options that consume a try is selected
                while (choice != "t" && choice != "s" && choice != "i" && choice != "h"&& choice != "q"  &&
                        choice != "s") {
                    cout << "Try #" << try_no << ", choose (s)ingle letter," <<
                        " (t)riplett, s(i)ze, (h)ydropathy, (l)ookup, (o)ptions, or (q)uit:" << endl;
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
                    if (choice == "h") {
                        a2hydropathy();
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

        string hdrpty2class(float hdrpty) {
            if (hdrpty >= hydrophobe_cut) {
                return "b";
            } else if (hdrpty < hydrophobe_cut && 
                       hdrpty >= neutral_cut) {
                return "n";
            } 
            
            return "l";
        }

        void a2hydropathy () {
            int aa_idx = get_rnd_aa_idx();
            string rnd_code = sl_code[aa_idx];
            
            string ans;

            cout << "Random amino acid code is " << rnd_code << "." << endl;
            cout << "What is its hydropathy class? Answer hydropho(b)ic, hydrophi(l)ic, or (n)eutral" <<
                " Enter below:" << endl;

            start_time();

            cin >> ans;

            bool in_time = check_time();

            float hdrpty = hydropathys[aa_idx];

            string cor_ans = hdrpty2class(hdrpty);

            if (ans == cor_ans && in_time) {
                cout << cols.green << "Correct! + 1 point!" << endl << cols.reset;
                    
                score += 1;
            } else if (ans == cor_ans && in_time) {
                
                cout << cols.red << 
                    "Correct, but you did not manage it in time" <<
                    cols.reset << endl;


            } else {
                cout << cols.red << "Wrong. The correct answer would have been " <<
                    cor_ans << endl << cols.reset;                
            }

            return;
         }

        // Order:   "A", "C", "D", "E", "F", "G", "H", "I", "K", "L", "M", "N",
        //          "P", "Q", "R", "S", "T", "V", "W", "Y"
        array<double, 20> hydropathys = { 1.8, 2.5, -3.5, -3.5, 2.8, -0.4, -3.2,
                                          4.5, -3.9, 3.8, 1.9, -3.5, -1.6, -3.5,
                                          -4.5, -0.8, -0.7, 4.2, -0.9, -1.3 };
        float hydrophobe_cut = -0.9;
        float neutral_cut = -3.2;

};

