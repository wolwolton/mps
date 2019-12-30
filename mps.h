#pragma once
#include <Eigen/Core>
#include <iostream>
#include <vector>
#include "particle.h"
#include "mk_particle.h"
#include "export.h"

class Mps{
    public:
        Mps(std::vector<Particle> &p);
        void run();
        void setDt(float t);
        void setMaxTime(float t);
        void setDx(float dx);
        void setDimension(int d);
        void setName(std::string name);
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    private:
        const Eigen::Vector3f g;
        const float nu = 1e-6;
        float dt;
        float t;
        float n_0;
        float lambda_0;
        float re;
        float dx;
        float max_time;
        int dim;
        std::vector<Particle> pcls;
        std::string filename;
        Export ex;
        float w(const Eigen::Vector3f &a, const Eigen::Vector3f &b);
        void calcGravity();
        void calcViscosity();
        void calcN_0(const Particle& pcl1);
        void calcLambda_0(const Particle& pcl1);
        void calcParameter();
        void moveParticleTmp();
        void calcPressure();
};

