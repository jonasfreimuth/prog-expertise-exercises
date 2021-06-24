# include <iostream>
# include <string>
# include <array>

using namespace std;

int levenstein(string src, string dst) {

    if (src == dst) {
	return 0;
    } else if (src.length() == 0) {
	return  dst.length();
    } else if (dst.length() == 0) {
	return  src.length();
    }

    return 1;
}

int main(int argc, char const *argv[])
{    
    string src = "";

    string dst = "";

    if (argc >=  2) {
        src = argv[1];
    }

    if (argc >= 3) {
        dst = argv[2];
    }

    int dist = levenstein(src, dst);

    cout << dist << endl;

    return 0;
}
