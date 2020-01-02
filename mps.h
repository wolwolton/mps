#pragma once
#include <Eigen/Core>
#include <Eigen/Sparse>
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
        const float rho = 1.0e3;
        const float beta = 0.97;
        const float gamma = 0.2;
        const float compressibility = 0.45e-9;
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
        float w(const Eigen::Vector3f &a, const Eigen::Vector3f &b, float re_tmp);
        float w(const Particle &a, const Particle &b);
        float w(const Particle &a, const Particle &b, float re_tmp);
        float n_d(Particle& pcl);
        void calcGravity();
        void calcViscosity();
        void calcN_0(const Particle& pcl1);
        void calcLambda_0(const Particle& pcl1);
        void calcParameter();
        void moveParticle();
        void setBoundaryCondition(std::vector<int> &clc_idx, std::vector<int> &prr_defined_idx);
        void calcA(Eigen::SparseMatrix<float, Eigen::RowMajor, int64_t> &M,  std::vector<int> &clc_idx);
        void calcb(Eigen::VectorXf &v,  std::vector<int> &clc_idx);
        void removeNegativePressure();
        void calcPressureGrad(std::vector<int> &idx);
        void fixParticlePosition();
        void calcPressure();
};

