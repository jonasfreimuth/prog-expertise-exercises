# include <iostream>
# include <string>
# include <array>
# include <ctime>

using namespace std;

bool aaa2a();
bool a2aaa();
void menu(int n_qs);
int find_aa_idx(string aa_code);
int randint(int min, int max);

array<string, 20> sl_code{ "A", "C", "D", "E", "F", "G", "H", "I", "K",
                            "L", "M", "N", "P", "Q", "R", "S", "T", "V",
                            "W", "Y" };
array<string, 20> tl_code{ "Ala", "Cys", "Asp", "Glu", "Phe", "His", "Ile",
                            "Lys", "Leu", "Met", "Asn", "Pro", "Gln", 
                            "Arg", "Ser", "Thr", "Val", "Trp", "Tyr" };
// according to this random website: https://www.webqc.org/aminoacids.php
array<float, 20> ml_mass{ 89.0935, 121.1590, 133.1032, 147.1299, 165.1900, 
                            155.1552, 131.1736, 146.1882, 131.1736,
                            149.2124, 132.1184, 115.1310, 146.1451, 
                            174.2017, 105.0930, 119.1197, 117.1469,
                            204.2262, 181.1894 };
int n_aminos = sizeof(sl_code) / sizeof(sl_code[0]);

int main(int argc, char const *argv[]) {

    for (int i = 0; i <= 10; i ++) {
        cout << randint(0, i) << endl;
    }

    int n_qs = 10;

    if (argc > 1) {
        n_qs = stoi(argv[1]);
    }
    
    menu(n_qs);

    return 0;
}


void menu(int n_qs) {
    for (int try_no = 1; try_no <= n_qs; try_no ++) {

        string choice = "";

        while (choice != "t" && choice != "s" && choice != "q") {
            cout << "Try #" << try_no << ", choose (s)ingle letter, (t)riplett, or (q)uit:" << endl;
            cin >> choice;
            cout << endl;

            if (choice == "t") {
                aaa2a();
            } 
            if (choice == "s") {
                a2aaa();
            } 
            if (choice == "q") {
                break;
            } 
        }

        if (choice == "q") {
            break;
        }
    }
}


bool aaa2a() {
    string rnd_code = tl_code[randint(0, n_aminos - 1)];
    int aa_idx = find_aa_idx(rnd_code);

    string ans;

    cout << "Random amino acid code is " << rnd_code << "." << endl;
    cout << "What is its one letter code? Enter below:" << endl;

    cin >> ans;

    if (ans == sl_code[aa_idx]) {
        cout << "Correct! +1 point" << endl;
        return (true);
    } else {
        cout << "Wrong!";
        return (false);
    }

    // kinda unnecessary, kept for safety though
    return (false);
}


bool a2aaa() {
    string rnd_code = sl_code[randint(0, n_aminos - 1)];
    int aa_idx = find_aa_idx(rnd_code);

    string ans;

    cout << "Random amino acid code is " << rnd_code << "." << endl;
    cout << "What is its three letter code? Enter below:" << endl;

    cin >> ans;

    if (ans == tl_code[aa_idx]) {
        cout << "Correct! +1 point" << endl;
        return (true);
    } else {
        cout << "Wrong!";
        return (false);
    }

    // kinda unnecessary, kept for safety though
    return (false);
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

    return (-1);
}


int randint(int min, int max) {
    if (min == max) {
        return (min);
    }

    cout << time(NULL) << endl;

    srand((int) time(NULL));

    int rnd = rand();

    int len = max - min;

    rnd = (rnd % len + 1) + min;

    return (rnd);
}