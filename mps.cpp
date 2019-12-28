#include <Eigen/Core>
#include <iostream>
#include "particle.h"
#include "mk_particle.h"

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
    mk_pcls.make_bar(pcls);
    for(auto pcl : pcls){
        std::cout << pcl.typ << ",";
    }
    std::cout << std::endl;
    return 0;
}