#include "particle.h"
#include <Eigen/Core>
#include <vector>

void Particle::setupPcl_bar(){
    std::vector<Eigen::Vector3f> acc_tmp(100*40*70);
    std::vector<Eigen::Vector3f> vel_tmp(100*40*70);
    std::vector<Eigen::Vector3f> pos_tmp(100*40*70);
    std::vector<int> typ_tmp(100*40*70); 
    float pcl_dist = 0.025;
    acc = acc_tmp;
    vel = vel_tmp;
    pos = pos_tmp;
    typ = typ_tmp;
    for(int ix=0; ix<100; ix++){
        for(int iy=0; iy<40; iy++){
            for(int iz=0; iz<70; iz++){
                pos[ix+iy+iz]=pcl_dist*(Eigen::Vector3f::UnitX()*(float)ix
                                       +Eigen::Vector3f::UnitY()*(float)iy
                                       +Eigen::Vector3f::UnitZ()*(float)iz);
                acc[ix+iy+iz]=Eigen::Vector3f::Zero();
                vel[ix+iy+iz]=Eigen::Vector3f::Zero();
            }
        }
    }
    for(int ix=0; ix<100; ix++){
        for(int iy=0; iy<40; iy++){
            for(int iz=0; iz<70; iz++){
                int typ_tmp = -1;
                if(3<ix && ix < 95 && 3<iy && iy<35 && 3<iz && iz < 50){
                    typ_tmp = FLD;
                }
                if(ix<4 && 95<ix && iy<4 && 35<iy && iz<4 && iz < 50){
                    typ_tmp = DMY;
                }
                if(ix<2 && 97<ix && iy<2 && 37<iy && iz<2 && iz < 50){
                    typ_tmp = WLL;
                }
                typ[ix+iy+iz]=typ_tmp;
            }
        }
    }
}

void Particle::updAcc(){

}

