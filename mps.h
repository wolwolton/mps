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
        void setName(std::string name);
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    private:
        Export ex;
        const Eigen::Vector3f g;
        float dt;
        float t;
        float max_time;
        std::vector<Particle> pcls;
        std::string filename;
        void calcGravity();
        void calcViscosity();
        void calcPressure();
};

