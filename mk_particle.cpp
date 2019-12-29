#include <Eigen/Core>
#include <vector>
#include "mk_particle.h"
#include "particle.h"

void MakeParticle::make_bar(std::vector<Particle> &pcls){
    std::vector<Particle> pcls_tmp(100*40*70);
    pcls = pcls_tmp;
    std::vector<Eigen::Vector3f> acc_tmp(100*40*70);
    std::vector<Eigen::Vector3f> vel_tmp(100*40*70);
    std::vector<Eigen::Vector3f> pos_tmp(100*40*70);
    std::vector<int> typ_tmp(100*40*70); 
    float pcl_dist = 0.025;
    for(int ix=0; ix<100; ix++){
        for(int iy=0; iy<40; iy++){
            for(int iz=0; iz<70; iz++){
                int idx = ix*40*70+iy*70+iz;
                pcls[idx].pos=pcl_dist*(Eigen::Vector3f::UnitX()*(float)ix
                                       +Eigen::Vector3f::UnitY()*(float)iy
                                       +Eigen::Vector3f::UnitZ()*(float)iz);
                pcls[idx].acc=Eigen::Vector3f::Zero();
                pcls[idx].vel=Eigen::Vector3f::Zero();
                pcls[idx].prr=0;
            }
        }
    }
    for(int ix=0; ix<100; ix++){
        for(int iy=0; iy<40; iy++){
            for(int iz=0; iz<70; iz++){
                int typ_tmp = Particle::GST;
                if(3<ix && ix < 95 && 3<iy && iy<35 && 3<iz && iz < 50){
                    typ_tmp = Particle::FLD;
                }
                if(iz<4 || (iz<50 && (ix<4 || 95<ix || iy<4 || 35<iy))){
                    typ_tmp = Particle::DMY;
                }
                if(iz<2 || (iz<50 && (ix<2 || 97<ix || iy<2 || 37<iy))){
                    typ_tmp = Particle::WLL;
                }
                pcls[ix*40*70+iy*70+iz].typ=typ_tmp;
            }
        }
    }
}
