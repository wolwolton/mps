#include <Eigen/Core>
#include <vector>
#include <iostream>
#include "particle.h"
#include "mps.h"

Mps::Mps(std::vector<Particle> &p)
:pcls(p),
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
        if(Particle::FLD == pcl.typ()){
            pcl.updAcc(g);
            pcl.updVel(pcl.vel()+g*dt);
        }
    }
}

void Mps::calcN_0(){
    float n = 0;
    auto& pcl1 = pcls[1000];
    for(auto &pcl2 : pcls){
        if(pcl1!=pcl2){
            n += w(pcl1.pos(),pcl2.pos());
        }
    }
    n_0 = n;
}

void Mps::calcViscosity(){
}

void Mps::moveParticleTmp(){

}

void Mps::calcPressure(){

}

void Mps::run(){
    int i=0;
    re = dx*2.1;
    calcN_0();
    std::cout << "n_0 is" << n_0 << std::endl;
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