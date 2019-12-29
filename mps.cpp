#include <Eigen/Core>
#include <vector>
#include <iostream>
#include "particle.h"
#include "mps.h"

Mps::Mps(std::vector<Particle> &p):pcls(p), dt(0), max_time(0), t(0), ex(), g(0.0f,0.0f,-9.8f), filename()
{}

void Mps::setDt(float t){
    dt = t;
}

void Mps::setMaxTime(float t){
    max_time = t;
}

void Mps::setName(std::string name){
    filename=name;
}

void Mps::calcGravity(){
    for(auto &pcl : pcls){
        if(Particle::FLD == pcl.typ()){
            pcl.updAcc(g);
            pcl.updVel(pcl.vel()+g*dt);
            pcl.updPos(pcl.pos()+pcl.vel()*dt);
        }
    }
}

void Mps::calcViscosity(){

}

void Mps::calcPressure(){

}

void Mps::run(){
    int i=0;
    while(t<max_time){
        std::cout << "calc" << i << std::endl;
        calcGravity();
        calcViscosity();
        calcPressure();
        ex.exportPara(filename,i, pcls);
        i++;
        t+=dt;
    }
    std::cout << "end" << std::endl;
}