# include <iostream>

using namespace std;

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

int main() {
    cout << "Guessing game: I choose a random" <<
        "number, and you have to guess it." << endl;

    int rnd_int = randint(1, 20);

    cout << rnd_int << endl;

    int ans = 0;

    while (true) {
        cout << "Enter your guess (-1 to quit): ";
        cin >> ans;
        cout << endl;

        if (ans == rnd_int) {
            cout << "Congratulations! That is the correct number!"
                << endl;
            break;
        } else if (ans > rnd_int) {
            cout << "Not quite. Too high..." << endl;
        } else if (ans < rnd_int && ans >= 0) {
            cout << "Not quite. Too low..." << endl;
        } else {
            cout << "Quitting..." << endl;
            break;
        }
    }
}

