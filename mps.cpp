#include <Eigen/Core>
#include <vector>
#include <iostream>
#include "particle.h"
#include "mps.h"

Mps::Mps(std::vector<Particle> &p)
:pcls(p),
 nu(1e-6),
 dt(0),
 max_time(0),
 dx(0),
 dim(0),
 t(0),
 g(0.0f,0.0f,-9.8f),
 n_0(0),
 lambda_0(0),
 re(0),
 ex(),
 filename()
{}

float Mps::w(const Eigen::Vector3f &a, const Eigen::Vector3f &b){
    float r = (a-b).norm();
    if(r>re){
        return r/re -1;
    }else{
        return 0;
    }
}

float Mps::w(const Particle &a, const Particle &b){
    return w(a.pos,b.pos);
}

void Mps::setDt(float t){
    dt = t;
}

void Mps::setMaxTime(float t){
    max_time = t;
}

void Mps::setDx(float x){
    dx = x;
}

void Mps::setDimension(int d){
    dim = d;
}

void Mps::setName(std::string name){
    filename=name;
}

void Mps::calcGravity(){
    for(auto &pcl : pcls){
        if(Particle::FLD == pcl.typ){
            pcl.acc=g;
            pcl.vel+=g*dt;
        }
    }
}

void Mps::calcN_0(const Particle& pcl1){
    float n = 0;
    for(auto &pcl2 : pcls){
        if(pcl1!=pcl2){
            n += w(pcl1,pcl2);
        }
    }
    n_0 = n;
}

void Mps::calcLambda_0(const Particle& pcl1){
    float l = 0;
    for(auto &pcl2: pcls){
        if(pcl1!=pcl2){
            l += (pcl1.pos-pcl2.pos).norm()*(pcl1.pos-pcl2.pos).norm()*w(pcl1,pcl2);
        }
    }
    lambda_0 = l/n_0;
}

void Mps::calcParameter(){
    re = dx*2.1;
    calcN_0(pcls[2000]);
    calcLambda_0(pcls[2000]);
}

void Mps::calcViscosity(){
    for(auto &pcl1 : pcls){
        if(pcl1.typ==Particle::FLD){
            Eigen::Vector3f a(0.0,0.0,0.0);
            for(auto &pcl2 : pcls){
                if(pcl2.typ!=Particle::GST){
                    a+=(pcl1.vel-pcl2.vel)*w(pcl1,pcl2);
                } 
            }
            pcl1.acc+=a*2*dim/n_0/lambda_0;
        }
    }
}

void Mps::moveParticleTmp(){
    for(auto& pcl : pcls){
        pcl.vel += pcl.acc*dt;
        pcl.pos += pcl.vel*dt;
        pcl.acc = Eigen::Vector3f::Zero();
    }
}

void Mps::calcPressure(){

}

void Mps::run(){
    int i=0;
    calcParameter();
    while(t<max_time){
        std::cout << "calc" << i << std::endl;
        calcGravity();
        calcViscosity();
        moveParticleTmp();
        calcPressure();
        ex.exportPara(filename,i, pcls);
        i++;
        t+=dt;
    }
    std::cout << "end" << std::endl;
}