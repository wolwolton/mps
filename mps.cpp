#include <Eigen/Core>
#include <Eigen/Sparse>
#include <Eigen/IterativeLinearSolvers>
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
        return re/r -1;
    }else{
        return 0;
    }
}

float Mps::w(const Particle &a, const Particle &b){
    return w(a.pos,b.pos);
}

float Mps::w(const Eigen::Vector3f &a, const Eigen::Vector3f &b, float re_tmp){
    float r = (a-b).norm();
    if(r>re_tmp){
        return re_tmp/r -1;
    }else{
        return 0;
    }
}

float Mps::w(const Particle &a, const Particle &b, float re_tmp){
    return w(a.pos,b.pos,re_tmp);
}

float Mps::n_d(Particle &pcl){
    float n = 0;
    for(auto &pcl1 : pcls){
        if(pcl1 != pcl && pcl1.typ!=Particle::GST){
            n += w(pcl1,pcl);
        }
    }
    return n;
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
    Eigen::Vector3f sum(0.0, 0.0, 0.0);
    int i = 0;
    for(auto &pcl : pcls){
        if(pcl.typ==Particle::FLD){
            sum += pcl.pos;
            i++;
        }
    }
    Eigen::Vector3f center = sum/i;
    float min = 100000;
    int min_idx = 0;
    for(int k=0; k<pcls.size(); k++){
        if(min>(pcls[k].pos-center).norm()){
            min_idx=k;
        }
    }
    re = dx*3.1;
    calcN_0(pcls[min_idx]);
    calcLambda_0(pcls[min_idx]);
    std::cout<<"SAMPLE PARTICLE NUM:"<<min_idx<<std::endl;
}

void Mps::calcViscosity(){
    for(auto &pcl1 : pcls){
        if(pcl1.typ==Particle::FLD){
            Eigen::Vector3f a(0.0,0.0,0.0);
            for(auto &pcl2 : pcls){
                if(pcl2.typ!=Particle::GST){
                    a+=(pcl2.vel-pcl1.vel)*w(pcl1,pcl2);
                } 
            }
            pcl1.acc+=a*2.0*(float)dim/n_0/lambda_0;
        }
    }
}

void Mps::moveParticle(){
    for(auto& pcl : pcls){
        if(pcl.typ == Particle::FLD){
            pcl.vel += pcl.acc*dt;
            pcl.pos += pcl.vel*dt;
            pcl.acc = Eigen::Vector3f::Zero();
        }
    }
}

void Mps::setBoundaryCondition(std::vector<int> &clc_idx, std::vector<int> &prr_defined_idx){
    int k = 0;
    for(int k=0; k<pcls.size(); k++){
        switch(pcls[k].typ){
            case Particle::DMY:
                continue;
                break;
            case Particle::GST:
                continue;
                break;
            case Particle::FLD:
                if(n_d(pcls[k])>n_0*beta){
                    clc_idx.push_back(k);
                }
                prr_defined_idx.push_back(k);
                break;
            default:
                clc_idx.push_back(k);
                prr_defined_idx.push_back(k);
                break;
        }
    }
}

void Mps::calcA(Eigen::SparseMatrix<float, Eigen::RowMajor, int64_t> &M, std::vector<int> &clc_idx){
    int k = 0;
    for(auto &i : clc_idx){
        M.startVec(k);
        int l = 0;
        for(auto &j : clc_idx){
            if(k==l){
                float w_sum = 0;
                for(auto &j2 : clc_idx){
                    if(j2!=j){
                        w_sum += w(pcls[j],pcls[j2],dx*3.1);
                    }
                }
                M.insertBack(k,k) = 1.0/rho*2.0*(float)dim/(lambda_0*n_0)*w_sum + compressibility/(dt*dt);
            }
            else{
                M.insertBack(k,l) = -1.0/rho*2.0*(float)dim/(lambda_0*n_0)*w(pcls[i],pcls[j],dx*3.1);
            }
            l++;
        }
        k++;
    }
    M.finalize();
}

void Mps::calcb(Eigen::VectorXf &v, std::vector<int> &clc_idx){
    int k = 0;
    for(auto &i : clc_idx){
        v(k)=gamma*1.0/(dt*dt)*(n_d(pcls[i])-n_0)/n_0;
        k++;
    }
}

void Mps::removeNegativePressure(){
    for(auto &pcl : pcls){
        if(pcl.prr<0){
            pcl.prr=0;
        }
    }
}

void Mps::calcPressureGrad( std::vector<int> &prr_defined_idx){
    for(auto &i : prr_defined_idx){
        float minprr = pcls[i].prr;
        for(auto &j : prr_defined_idx){
            if(minprr > pcls[j].prr && w(pcls[i],pcls[j])>0){
                minprr = pcls[j].prr;
            }
        }
        pcls[i].acc = Eigen::Vector3f::Zero();
        for(auto &j : prr_defined_idx){
            if(pcls[i] != pcls[j] && pcls[i].pos!=pcls[j].pos){
                pcls[i].acc += -1.0*(float)dim/(rho*n_0)*(pcls[j].prr-minprr)
                            /((pcls[i].pos-pcls[j].pos).norm()*(pcls[i].pos-pcls[j].pos).norm())
                            *(pcls[j].pos-pcls[i].pos)*w(pcls[i],pcls[j]);
            }
        }
    }
}

void Mps::fixParticlePosition(){
    for(auto& pcl : pcls){
        if(pcl.typ == Particle::FLD){
            pcl.vel += pcl.acc*dt;
            pcl.pos += pcl.acc*dt*dt;
            pcl.acc = Eigen::Vector3f::Zero();
        }
    }
}

void Mps::calcPressure(){
    std::cout << "SOLVING" << std::endl;
    std::vector<int> clc_idx;
    std::vector<int> prr_defined_idx;
    setBoundaryCondition(clc_idx,prr_defined_idx);
    int n = clc_idx.size();
    Eigen::SparseMatrix<float, Eigen::RowMajor, int64_t> A(n,n);
    Eigen::VectorXf b(n);
    calcA(A,clc_idx);
    calcb(b,clc_idx);
    std::cout << "success calcA calcB" << std::endl;
    
    Eigen::BiCGSTAB<Eigen::SparseMatrix<float>> solver;
    solver.compute(A);
    std::cout << "success compute" << std::endl;
    if(solver.info()!=Eigen::Success) {
        std::cout<<"solver error" << std::endl;
        return;
    }
    auto x = solver.solve(b);
    if(solver.info()!=Eigen::Success) {
        std::cout<<"solving failed" << std::endl;
        return;
    }
    int k = 0;
    int l = 0;
    
    while(k<pcls.size()){
        pcls[k].prr = 0;
        if(l<clc_idx.size() && k==clc_idx[l]){
            pcls[k].prr = x[l];
            l++;
        }
        k++;
    }
    removeNegativePressure();
    calcPressureGrad(prr_defined_idx);
    fixParticlePosition();
}

void Mps::run(){
    int i=0;
    calcParameter();
    while(t<max_time){
        std::cout << "calc" << i << std::endl;
        calcGravity();
        calcViscosity();
        moveParticle();
        calcPressure();
        moveParticle();
        ex.exportPara(filename,i, pcls);
        i++;
        t+=dt;
    }
    std::cout << "end" << std::endl;
}