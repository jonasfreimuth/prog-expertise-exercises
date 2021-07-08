# ifndef XPESPORT_H
#  define XPESPORT_H

# include "PESport.hpp"
# include <array>
# include <string>

class XPESport : public PESport {

    public:   

        void menu(int n_qs, std::string pre_choice);

    protected:

        std::string hdrpty2class(float hdrpty);

        void a2hydropathy();

        // Order:   "A", "C", "D", "E", "F", "G", "H", "I", "K", "L", "M", "N",
        //          "P", "Q", "R", "S", "T", "V", "W", "Y"
        std::array<double, 20> hydropathys = { 1.8, 2.5, -3.5, -3.5, 2.8, -0.4, -3.2,
                                          4.5, -3.9, 3.8, 1.9, -3.5, -1.6, -3.5,
                                          -4.5, -0.8, -0.7, 4.2, -0.9, -1.3 };
        float hydrophobe_cut = -0.9;
        float neutral_cut = -3.2;

};

# endif