#include <Eigen/Core>
#include <Eigen/Sparse>
#include <Eigen/IterativeLinearSolvers>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include "particle.h"
#include "mps.h"

Mps::Mps(Environment &&e)
:env(std::move(e)),
 nu(1e-6),
 dt(0),
 max_time(0),
 dx(0),
 dim(0),
 e(0),
 colDist(0),
 t(0),
 g(0.0d,0.0d,-9.8d),
 n_0(0),
 lambda_0(0),
 re(0),
 ex(),
 filename()
{}

double Mps::w(const Eigen::Vector3d &a, const Eigen::Vector3d &b, double re_tmp){
    double r = (a-b).norm();
    if(re_tmp>r){
        return re_tmp/r -1.0;
    }else{
        return 0;
    }
}

double Mps::w(const Particle &a, const Particle &b, double re_tmp){
    return w(a.pos,b.pos,re_tmp);
}

double Mps::w(const std::unique_ptr<Particle> &a, const std::unique_ptr<Particle> &b, double re_tmp){
    return w(a->pos,b->pos,re_tmp);
}

double Mps::w(const Eigen::Vector3d &a, const Eigen::Vector3d &b){
    return w(a, b, re);
}

double Mps::w(const Particle &a, const Particle &b){
    return w(a.pos,b.pos, re);
}

double Mps::w(const std::unique_ptr<Particle> &a, const std::unique_ptr<Particle> &b){
    return w(a->pos,b->pos, re);
}

double Mps::n_d(const Particle &pcl){
    double n = 0;
    if(pcl.typ!=Particle::GST){
        for(auto&& pcl1 : env.pcls){
            if(*pcl1 != pcl && pcl1->typ!=Particle::GST){
                n += w(*pcl1,pcl);
            }
        }
    }
    return n;
}

double Mps::n_d(const std::unique_ptr<Particle> &pcl){
    return n_d(*pcl);
}

void Mps::setDt(double t){
    dt = t;
}

void Mps::setMaxTime(double t){
    max_time = t;
}

void Mps::setDx(double x){
    dx = x;
}

void Mps::setDimension(int d){
    dim = (double)d;
}

void Mps::setName(std::string name){
    filename=name;
}

void Mps::setCOR(double e_in){
    e = e_in;
}

void Mps::calcGravity(){
    for(auto&& pcl : env.pcls){
        if(Particle::FLD == pcl->typ){
            pcl->acc=g;
        }else{
            pcl->acc=Eigen::Vector3d::Zero();
        }
    }
}

void Mps::calcN_0(const std::unique_ptr<Particle>& pcl1){
    double n = 0;
    double n_lap = 0;
    for(auto&& pcl2 : env.pcls){
        if(pcl1!=pcl2){
            n += w(pcl1,pcl2,dx*2.1);
            n_lap += w(pcl1,pcl2,dx*3.1);
        }
    }
    n_0 = n;
    n_0_lap=n_lap;
    
}

void Mps::calcLambda_0(const std::unique_ptr<Particle>& pcl1){
    double l = 0;
    for(auto&& pcl2: env.pcls){
        if(pcl1!=pcl2){
            l += (pcl1->pos-pcl2->pos).norm()*(pcl1->pos-pcl2->pos).norm()*w(pcl1,pcl2,dx*3.1);
        }
    }
    lambda_0 = l/n_0_lap;
}

void Mps::calcParameter(){
    Eigen::Vector3d sum(Eigen::Vector3d::Zero());
    int i = 0;
    for(auto&& pcl : env.pcls){
        if(pcl->typ==Particle::FLD){
            sum += pcl->pos;
            i++;
        }
    }
    Eigen::Vector3d center = sum/i;
    double min = 100000;
    int min_idx = 0;
    for(int k=0; k<env.pcls.size(); k++){
        if(min>(env.pcls[k]->pos-center).norm()){
            min_idx=k;
            min = (env.pcls[k]->pos-center).norm();
        }
    }
    re = dx*2.1;
    colDist = dx*0.5;
    calcN_0(env.pcls[min_idx]);
    calcLambda_0(env.pcls[min_idx]);
    std::cout<<"SAMPLE PARTICLE NUM:"<<min_idx<<std::endl;
    std::cout<<"N_0:"<<n_0<<std::endl;
    std::cout<<"N_0_lap:"<<n_0_lap<<std::endl;
    std::cout<<"lambda:"<<lambda_0<<std::endl;
}

void Mps::calcViscosity(){
    for(auto&& pcl1 : env.pcls){
        if(pcl1->typ==Particle::FLD){
            Eigen::Vector3d a(Eigen::Vector3d::Zero());
            for(auto&& pcl2 : env.pcls){
                if(pcl2->typ!=Particle::GST && pcl2!=pcl1){
                    a+=(pcl2->vel-pcl1->vel)*w(pcl1,pcl2,dx*3.1);
                } 
            }
            pcl1->acc+=nu*2.0*dim/(n_0_lap*lambda_0)*a;
        }
    }
}

void Mps::moveParticle(){
    for(auto&& pcl : env.pcls){
        if(pcl->typ == Particle::FLD){
            pcl->vel += pcl->acc*dt;
            pcl->pos += pcl->vel*dt;
            pcl->acc = Eigen::Vector3d::Zero();
        }else{
            pcl->acc = Eigen::Vector3d::Zero();
        }
    }
}

void Mps::collision(){
    for(auto&& pcl1 : env.pcls){
        if(pcl1->typ!=Particle::FLD){
            continue;
        }
        Eigen::Vector3d vel_delta(Eigen::Vector3d::Zero());
        for(auto&& pcl2 : env.pcls){
            double dist = (pcl2->pos - pcl1->pos).norm();
            if(pcl1!=pcl2 && pcl2->typ!=Particle::GST && dist < colDist){
                Eigen::Vector3d direction = (pcl2->pos - pcl1->pos)/dist;
                double forceDT = (pcl1->vel.x() - pcl2->vel.x())*direction.x()
                                +(pcl1->vel.y() - pcl2->vel.y())*direction.y()
                                +(pcl1->vel.z() - pcl2->vel.z())*direction.z();
                if(forceDT>0){
                    vel_delta -= (1.0+e)*(rho*rho/(rho+rho))*forceDT/rho*direction;
                }
            }
        }
        pcl1->vel += vel_delta;
        pcl1->pos += vel_delta*dt;
    }
}

void Mps::setBoundaryCondition(){
    for(auto&& pcl : env.pcls){
        switch(pcl->typ){
            case Particle::DMY:
                pcl->b_c = GST_DMY;
                break;
            case Particle::GST:
                pcl->b_c = GST_DMY;
                break;
            case Particle::FLD:
                if(n_d(pcl)<(n_0*beta)){
                    pcl->b_c = OUTR_FLD;
                }else{
                    pcl->b_c = INER_FLD;
                }
                break;
            case Particle::WLL:
                if(n_d(pcl)<(n_0*beta)){
                    pcl->b_c = OUTR_FLD;
                }else{
                    pcl->b_c = INER_FLD;
                }
                break;
            default:
                pcl->b_c = INER_FLD;
                break;
        }
    }
}

void Mps::calcA(Eigen::SparseMatrix<double, Eigen::RowMajor, int64_t> &M){
    int k = -1;
    for(auto&& pcl1 : env.pcls){
        k++;
        M.startVec(k);
        if(pcl1->b_c!=INER_FLD)continue;
        int l = -1;
        for(auto&& pcl2 : env.pcls){
            l++;
            if(pcl2->b_c==GST_DMY)continue;//pass loop
            if(k==l){
                double sum = 0;
                for(auto&& pcl3 : env.pcls){
                    if(pcl2!=pcl3 && pcl3->b_c!=GST_DMY){
                        sum += w(pcl1,pcl3,dx*3.1) * (2.0*dim/(lambda_0*n_0)) / rho;
                    }
                }
                M.insertBack(k,k) = sum + compressibility/(dt*dt);
            }
            else{
                M.insertBack(k,l) = -1.0/rho*(2.0*dim/(lambda_0*n_0))*w(pcl1,pcl2,dx*3.1);
            }
        }
    }
    M.finalize();
}

void Mps::calcb(Eigen::VectorXd &v){
    int k = 0;
    for(auto&& pcl : env.pcls){
        if(pcl->b_c==INER_FLD){
            v(k)=gamma*(1.0/(dt*dt))*((n_d(pcl)-n_0)/n_0);
        }
        else{
            v(k)=0;
        }
        k++;
    }
}

void Mps::removeNegativePressure(){
    for(auto&& pcl : env.pcls){
        if(pcl->prr<0){
            pcl->prr=0;
        }
    }
}

void Mps::calcPressureGrad(){
    for(auto&& pcl : env.pcls){
        if(pcl->b_c!=Particle::FLD)continue;
        double minprr = 1.0e10;
        for(auto&& pcl2 : env.pcls){
            if(pcl2->b_c!=GST_DMY && pcl!=pcl2 && minprr > pcl2->prr && w(pcl,pcl2)>0){
                minprr = pcl2->prr;
            }
        }
        pcl->acc = Eigen::Vector3d::Zero();
        for(auto&& pcl2 : env.pcls){
            if(pcl!=pcl2 && pcl->pos!=pcl2->pos && pcl2->b_c!=GST_DMY){
                double dist = (pcl2->pos-pcl->pos).norm();
                pcl->acc += -1.0*(pcl2->pos - pcl->pos)
                                    *(dim/(rho*n_0))*(pcl2->prr-minprr)*w(pcl,pcl2)
                                /(dist*dist);
            }
        }
    }
}

void Mps::fixParticlePosition(){
    for(auto&& pcl : env.pcls){
        if(pcl->typ == Particle::FLD){
            pcl->vel += pcl->acc*dt;
            pcl->pos += pcl->acc*dt*dt;
            pcl->acc = Eigen::Vector3d::Zero();
        }else{
            pcl->acc = Eigen::Vector3d::Zero();
        }
    }
}

void Mps::calcPressure(){
    std::cout << "SOLVING" << std::endl;
    setBoundaryCondition();
    int n = env.pcls.size();
    Eigen::SparseMatrix<double, Eigen::RowMajor, int64_t> A(n,n);
    Eigen::VectorXd b(n);
    calcA(A);
    calcb(b);
    std::cout << "success calcA calcB" << std::endl;
    
    Eigen::BiCGSTAB<Eigen::SparseMatrix<double>> solver;
    solver.compute(A);
    if(solver.info()!=Eigen::Success) {
        std::cout<<"solver error" << std::endl;
        return;
    }
    Eigen::VectorXd x(n);
    x = solver.solve(b);
    if(solver.info()!=Eigen::Success) {
        std::cout<<"solving failed" << std::endl;
        return;
    }
    for(int k = 0; k<env.pcls.size(); k++){
        env.pcls[k]->prr = x[k];
    }
    removeNegativePressure();
    calcPressureGrad();
    fixParticlePosition();
    std::cout << "success compute" << std::endl;
}

void Mps::run(){
    int i=0;
    int k=0;
    calcParameter();
    ex.exportPara(filename,k, env.pcls);
    k++;
    while(t<max_time){
        calcGravity();
        calcViscosity();
        moveParticle();
        collision();
        calcPressure();
        if(i%20==0){
            ex.exportPara(filename,k, env.pcls);
            k++;
        }
        i++;
        t+=dt;
    }
    std::cout << "end" << std::endl;
}