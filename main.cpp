#include <iostream>
#include <vector>
#include "mps.h"
#include "particle.h"
#include "mk_particle.h"
#include "export.h"
#include <Eigen/Core>

int main(){
    std::cout<<"TST"<<std::endl;
    std::vector<Particle> pcls;
    MakeParticle mk_pcls;
    std::cout<<"TST"<<std::endl;
    mk_pcls.make_bar(pcls);
    std::cout<<"TST"<<std::endl;
    Export ex;
    Mps mps(pcls);
    std::cout<<"TST"<<std::endl;
    mps.setDt((double)1e-3);
    mps.setMaxTime((double)2);
    mps.setDx((double)0.025);
    mps.setDimension(2);
    mps.setName("./output3/tst1_");
    std::cout<<"TST"<<std::endl;
    ex.exportPara("tst2.vtu", pcls);
    std::cout<<"TST"<<std::endl;
    mps.run();
    return 0;
}