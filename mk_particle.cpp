#include <Eigen/Core>
#include <vector>
#include "mk_particle.h"
#include "particle.h"

void MakeParticle::make_bar(std::vector<Particle> &pcls){
    std::vector<Particle> pcls_tmp(70*30);
    pcls = pcls_tmp;
    float pcl_dist = 0.025;
    for(int ix=0; ix<70; ix++){
        for(int iy=0; iy<1; iy++){
            for(int iz=0; iz<30; iz++){
                int idx = ix*1*30+iy*30+iz;
                pcls[idx].pos=pcl_dist*(Eigen::Vector3f::UnitX()*(float)ix
                                       +Eigen::Vector3f::UnitY()*(float)iy
                                       +Eigen::Vector3f::UnitZ()*(float)iz);
                pcls[idx].acc=Eigen::Vector3f::Zero();
                pcls[idx].vel=Eigen::Vector3f::Zero();
                pcls[idx].prr=0;
            }
        }
    }
    for(int ix=0; ix<70; ix++){
        for(int iy=0; iy<1; iy++){
            for(int iz=0; iz<30; iz++){
                int typ_tmp = Particle::GST;
                if(7<ix && ix < 14  && 3<iz && iz < 30){
                    typ_tmp = Particle::FLD;
                }
                if(iz<8 || (iz<30 && (ix<8 || 61<ix ))){
                    typ_tmp = Particle::WLL;
                }
                if(iz<4 || (iz<30 && (ix<4 || 65<ix ))){
                    typ_tmp = Particle::DMY;
                }
                /*
                if(7<ix && ix < 10  && iz < 30){
                    typ_tmp = Particle::FLD;
                }*/
                pcls[ix*1*30+iy*30+iz].typ=typ_tmp;
            }
        }
    }
}