# ifndef XPESPORT_H
#  define XPESPORT_H

# include "PESport.h"
# include <array>
# include <string>

class XPESport : public PESport {

    public:   

        void menu(int n_qs);

    protected:

        std::string hdrpty2class(float hdrpty);

        void a2hydropathy();
         
        std::array<double, 20> hydropathys;
        float hydrophobe_cut;
        float neutral_cut;

};

# endif