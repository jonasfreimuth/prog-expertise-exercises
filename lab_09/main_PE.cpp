# include "PESport.h"

int main(int argc, char const *argv[]) {

    auto pe = PESport();

    int n_qs = 10;

    if (argc > 1) {
        n_qs = std::stoi(argv[1]);
    }
    
    pe.menu(n_qs);

    return 0;
}
