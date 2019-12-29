#include <iostream>
#include "mps.h"
#include "particle.h"
#include "mk_particle.h"
#include "export.h"

int main(){
    std::vector<Particle> pcls;
    MakeParticle mk_pcls;
    Export ex;
    mk_pcls.make_bar(pcls);
    ex.exportPara("tst.vtu",pcls);
    return 0;
}