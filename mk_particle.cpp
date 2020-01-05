#include <Eigen/Core>
#include <vector>
#include "mk_particle.h"
#include "particle.h"

void MakeParticle::make_bar(std::vector<Particle> &pcls){
    std::vector<Particle> pcls_tmp(70*30);
    pcls = pcls_tmp;
    double pcl_dist = 0.025;
    for(int ix=0; ix<70; ix++){
        for(int iy=0; iy<1; iy++){
            for(int iz=0; iz<30; iz++){
                int idx = ix*1*30+iy*30+iz;
                pcls[idx].pos=pcl_dist*(Eigen::Vector3d::UnitX()*(double)ix
                                       +Eigen::Vector3d::UnitY()*(double)iy
                                       +Eigen::Vector3d::UnitZ()*(double)iz);
                pcls[idx].acc=Eigen::Vector3d::Zero();
                pcls[idx].vel=Eigen::Vector3d::Zero();
                pcls[idx].prr=0;
            }
        }
    }
    for(int ix=0; ix<70; ix++){
        for(int iy=0; iy<1; iy++){
            for(int iz=0; iz<30; iz++){
                int typ_tmp = Particle::GST;
                if(3<ix && ix < 14  && 3<iz && iz < 30){
                    typ_tmp = Particle::FLD;
                }
                if(iz<4 || (iz<30 && (ix<4 || 65<ix ))){
                    typ_tmp = Particle::WLL;
                }
                if(iz<2 || (iz<30 && (ix<2 || 67<ix ))){
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