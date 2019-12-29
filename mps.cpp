#include <Eigen/Core>
#include <iostream>
#include "particle.h"
#include "mk_particle.h"
#include "export.h"

/*
class Mps{
    public:
        void setupPcl();
        void run();
    private:
        void calcGravity();
        void calcViscosity();
        void calcPressure();
}
*/

int main(){
    std::vector<Particle> pcls;
    MakeParticle mk_pcls;
    Export ex;
    mk_pcls.make_bar(pcls);
    ex.exportPara("tst.vtu",pcls);
    return 0;
}