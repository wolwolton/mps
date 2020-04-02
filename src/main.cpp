#include <iostream>
#include <vector>
#include <memory>
#include "mps.h"
#include "particle.h"
#include "mk_particle.h"
#include "export.h"
#include "object.h"
#include <Eigen/Core>

int main(){
    double pcl_dist = 0.025;
    std::vector<std::unique_ptr<Particle>> pcls;

    Environment env(std::move(pcls));
    
    MakeParticle mk_pcls;
    mk_pcls.make_bar_ex(env, pcl_dist);
    
    Mps mps(std::move(env));
    
    std::cout<<"TST"<<std::endl;
    mps.setDt(1e-3);
    mps.setMaxTime(2);
    mps.setDx(pcl_dist);
    mps.setCOR(0.2);
    mps.setDimension(2);
    mps.setName("../output/tst1_");
    mps.run();
    return 0;
}