#include <iostream>
#include <vector>
#include "mps.h"
#include "particle.h"
#include "mk_particle.h"
#include "export.h"

int main(){
    std::vector<Particle> pcls;
    MakeParticle mk_pcls;
    mk_pcls.make_bar(pcls);
    Export ex;
    Mps mps(pcls);
    mps.setDt(1e-3);
    mps.setMaxTime(2e-1);
    mps.setDx(0.025);
    mps.setDimension(2);
    mps.setName("./output3/tst1_");
    ex.exportPara("tst2.vtu", pcls);
    mps.run();
    return 0;
}