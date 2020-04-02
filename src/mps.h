#pragma once
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <iostream>
#include <vector>
#include "environment.h"
#include "particle.h"
#include "mk_particle.h"
#include "export.h"

namespace MPS{
class Mps{
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
        Mps(Environment &&e);
        void run();
        void setDt(double t);
        void setMaxTime(double t);
        void setDx(double dx);
        void setDimension(int d);
        void setName(std::string name);
        void setCOR(double e_in);
    private:
        const static int INER_FLD = 0;
        const static int OUTR_FLD = 1;
        const static int GST_DMY  = -1;
        const Eigen::Vector3d g;
        const double nu = 1e-6;
        const double rho = 1.0e3;
        const double beta = 0.97;
        const double gamma = 0.2;
        const double compressibility = 0.45e-9;
        double dt;
        double t;
        double n_0;
        double n_0_lap;
        double lambda_0;
        double re;
        double colDist;
        double dx;
        double e;
        double max_time;
        double dim;
        Environment env;
        std::string filename;
        Export ex;
        double w(const Eigen::Vector3d &a, const Eigen::Vector3d &b);
        double w(const Eigen::Vector3d &a, const Eigen::Vector3d &b, double re_tmp);
        double w(const Particle &a, const Particle &b);
        double w(const std::unique_ptr<Particle> &a, const std::unique_ptr<Particle> &b);
        double w(const Particle &a, const Particle &b, double re_tmp);
        double w(const std::unique_ptr<Particle> &a, const std::unique_ptr<Particle> &b, double re_tmp);
        double n_d(const Particle &pcl);
        double n_d(const std::unique_ptr<Particle> &pcl);
        void calcGravity();
        void calcViscosity();
        void calcN_0(const std::unique_ptr<Particle> &pcl1);
        void calcLambda_0(const std::unique_ptr<Particle> &pcl1);
        void calcParameter();
        void moveParticle();
        void collision();
        void setBoundaryCondition();
        void calcA(Eigen::SparseMatrix<double, Eigen::RowMajor, int64_t> &M);
        void calcb(Eigen::VectorXd &v);
        void removeNegativePressure();
        void calcPressureGrad();
        void fixParticlePosition();
        void calcPressure();
};
}

