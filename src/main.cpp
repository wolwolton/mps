#include <iostream>
#include <vector>
#include <memory>
#include "mps.h"
#include "particle.h"
#include "mk_particle.h"
#include "export.h"
#include <Eigen/Core>

#include "mmm.h"

/*
class A{
public:
    bool flg;
    int value;
    A():flg(false), value(0){}
};

void tst(const std::vector<std::unique_ptr<const A>>& array){
    for(auto &a: array){
        //a->value++;
        std::cout<<a->value << std::endl;
    }
}
*/


int main(){
    double pcl_dist = 0.025;
    std::vector<std::unique_ptr<Particle>> pcls;
    MakeParticle mk_pcls;
    mk_pcls.make_bar_ex(pcls, pcl_dist);
    Export ex;
    ex.exportPara("tst1.vtu", pcls);
    //mmm.make_bar_MMM_ex(pcls);

    Mps mps(std::move(pcls));
    
    std::cout<<"TST"<<std::endl;
    mps.setDt(1e-3);
    mps.setMaxTime(2);
    mps.setDx(pcl_dist);
    mps.setCOR(0.2);
    mps.setDimension(2);
    mps.setName("../output/tst1_");
    std::cout<<"TST"<<std::endl;
    ex.exportPara("tst2.vtu", pcls);
    std::cout<<"TST"<<std::endl;
    mps.run();
    return 0;
}