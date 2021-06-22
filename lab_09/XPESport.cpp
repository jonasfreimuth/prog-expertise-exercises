# include <iostream>
# include "PESport.h"
# include "XPESport.h"

using namespace std; 

void XPESport::menu(int n_qs) {
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

string XPESport::hdrpty2class(float hdrpty) {
    if (hdrpty >= hydrophobe_cut) {
        return "b";
    } else if (hdrpty < hydrophobe_cut && 
                hdrpty >= neutral_cut) {
        return "n";
    } 
    
    return "l";
}

void XPESport::a2hydropathy () {
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

