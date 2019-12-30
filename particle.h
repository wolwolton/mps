#pragma once
#include <vector>
#include <Eigen/Core>

class Particle
{
    private:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    public:
        Particle();
        const static int GST = -1; 
        const static int FLD = 0; 
        const static int WLL = 1;
        const static int DMY = 2; 
        Eigen::Vector3f pos;
        Eigen::Vector3f vel;
        Eigen::Vector3f acc;
        float prr;
        int typ;
};

inline bool operator==(const Particle& lhs, const Particle& rhs){return (&lhs==&rhs); }
inline bool operator!=(const Particle& lhs, const Particle& rhs){ return !(lhs == rhs); }
