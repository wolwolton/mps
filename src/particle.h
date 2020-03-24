#pragma once
#include <vector>
#include <Eigen/Core>

class Particle
{
    private:
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        Particle();
        Particle(const Particle& rhs);
        const static int GST = -1; 
        const static int FLD = 0; 
        const static int WLL = 1;
        const static int DMY = 2; 
        Eigen::Vector3d pos;
        Eigen::Vector3d acc;
        Eigen::Vector3d vel;
        double prr;
        int typ;
        int b_c;
};

inline bool operator==(const Particle& lhs, const Particle& rhs){return (&lhs==&rhs); }
inline bool operator!=(const Particle& lhs, const Particle& rhs){ return !(lhs == rhs); }
