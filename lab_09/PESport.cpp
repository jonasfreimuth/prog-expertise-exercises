# include "PESport.hpp"

# include <iostream>
# include <string>
# include <array>
# include <ctime>

using namespace std;

int PESport::randint(int min, int max) {
    if (min == max) {
        return (min);
    }

    srand((int) time(NULL));

    int rnd = rand();

    int len = max - min;

    rnd = (rnd % len + 1) + min;

    return (rnd);
}

int PESport::pseudo2idx (int pseudo_idx) {
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

int PESport::get_rnd_aa_idx() {

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

int PESport::find_aa_idx(string aa_code) {
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

void PESport::setOpts () {
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

void PESport::aaa2a() {
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

void PESport::a2aaa() {
    int aa_idx = get_rnd_aa_idx();
    string rnd_code = sl_code[aa_idx];

    string ans;

    cout << "Random amino acid code is " << rnd_code << "." << endl;
    cout << "What is its three letter code? Enter below:" << endl;

    start_time();

    cin >> ans;

    bool in_time = check_time();

    if (ans == tl_code[aa_idx] && in_time) {
        cout << cols.green << "Correct! +1 point" << endl << cols.reset;

        score ++;

    } else if (ans == tl_code[aa_idx] && !in_time) {

        cout << cols.red << 
            "Correct, but you did not manage it in time" <<
            cols.reset << endl;

    } else {
        cout << cols.red << "Wrong!" << " Correct answer would have been " <<
            tl_code[aa_idx] << endl << cols.reset;
    }
    
    return;
}

void PESport::a2size () {
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

void PESport::lookup_aa() {
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

void PESport::menu(int n_qs) {
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

// Record current time in object 
// (at least i hope its in the object and not the class)
void PESport::start_time() {
    last_start_time = time(NULL);
}

// check how much time has passed since the last call to 
// start_time and compare with max allowed time
bool PESport::check_time() {
    time_t diff_time = time(NULL) - last_start_time;

    if (diff_time <= maxTime) {
        return (true);
    }

    return (false);
}

