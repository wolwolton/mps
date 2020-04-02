#include <Eigen/Core>
#include <vector>
#include "mk_particle.h"
#include "particle.h"
#include "environment.h"

using namespace MPS;
void MakeParticle::make_bar(Environment &env, const double pcl_dist){
    env.pcls.clear();
    for(int ix=0; ix<70; ix++){
        for(int iy=0; iy<1; iy++){
            for(int iz=0; iz<30; iz++){
                std::unique_ptr<Particle> p1(new Particle);
                p1->pos=pcl_dist*(Eigen::Vector3d::UnitX()*(double)ix
                                       +Eigen::Vector3d::UnitY()*(double)iy
                                       +Eigen::Vector3d::UnitZ()*(double)iz);
                p1->acc=Eigen::Vector3d::Zero();
                p1->vel=Eigen::Vector3d::Zero();
                p1->prr=0;
                env.pcls.push_back(std::move(p1));
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
                env.pcls[ix*1*30+iy*30+iz]->typ=typ_tmp;
            }
        }
    }
}

void MakeParticle::make_bar(Environment &env){
    double pcl_dist = 0.025;
    make_bar(env, pcl_dist);
}

void MakeParticle::make_bar_ex(Environment &env, const double pcl_dist){
    env.pcls.clear();

    double eps = 0.01 * pcl_dist;
    const bool OFF = false;
    const bool ON = true;
    int iX, iZ;
    int nX, nZ;
    double x, y, z;
    int i=0;
    bool flagOfParticleGeneration;

    nX = (int)(1.0 / pcl_dist) + 5;
    nZ = (int)(1.0 / pcl_dist) + 5;
    for(iX = -4; iX < nX; iX++){
        for(iZ = -4; iZ < nZ; iZ++){
            x = pcl_dist * (double)iX;
            z = pcl_dist * (double)iZ;
            y = 0.0;
            int pcl_typ = Particle::GST;
            flagOfParticleGeneration = OFF;

            /*dummy wall region*/
            if(((x > -4.0*pcl_dist + eps) && (x <= 1.0 + 4.0*pcl_dist+ eps))
             && ((z> 0.0 - 4.0*pcl_dist + eps) && (z <= 0.6 + eps))){
                pcl_typ = Particle::DMY;
                flagOfParticleGeneration = ON;
            }

            /*wall region*/
            if(((x > -2.0*pcl_dist + eps) && (x <= 1.0 + 2.0*pcl_dist + eps))
             && ((z > 0.0 -2.0*pcl_dist + eps) && (z <= 0.6 + eps))){
                 pcl_typ = Particle::WLL;
                 flagOfParticleGeneration = ON;
             }
            
            /*wall region*/
            if(((x > -4.0*pcl_dist + eps) && (x <= 1.0 + 4.0*pcl_dist + eps))
             && ((z > 0.6 -2.0*pcl_dist + eps) && (z <= 0.6 + eps))){
                 pcl_typ = Particle::WLL;
                 flagOfParticleGeneration = ON;
             }
            
            /*empty region*/
            if(((x > 0.0 + eps) && (x <= 1.0 + eps)) && (z > 0.0 + eps)){
                flagOfParticleGeneration = OFF;
            }

            /*fluid region*/
            if(((x > 0.0 + eps) && (x <= 0.25 + eps)) && ((z > 0.0 + eps) && (z <= 0.5 + eps))){
                pcl_typ = Particle::FLD;
                flagOfParticleGeneration = ON;
            }

            if(flagOfParticleGeneration == ON){
                std::unique_ptr<Particle> p(new Particle);
                Eigen::Vector3d tmppos(x, y, z);
                p->pos=tmppos;
                p->acc=Eigen::Vector3d::Zero();
                p->vel=Eigen::Vector3d::Zero();
                p->prr=0;
                p->typ=pcl_typ;
                env.pcls.push_back(std::move(p));
            }

        }
    }
}
