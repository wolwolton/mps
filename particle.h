#pragma once
#include <vector>
#include <Eigen/Core>

class Particle
{
    private:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        Eigen::Vector3f position;
        Eigen::Vector3f velocity;
        Eigen::Vector3f acceleration;
        float pressure;
        int particle_type;
    public:
        Particle();
        const static int GST = -1; 
        const static int FLD = 0; 
        const static int WLL = 1;
        const static int DMY = 2; 
        void updPos(const Eigen::Vector3f &p);
        void updVel(const Eigen::Vector3f &v);
        void updAcc(const Eigen::Vector3f &a);
        void updTyp(const int t);
        void updPrr(const float p);
        const Eigen::Vector3f pos() const;
        const Eigen::Vector3f vel() const;
        const Eigen::Vector3f acc() const;
        const int typ() const;
        const float prr() const;
};

inline bool operator==(const Particle& lhs, const Particle& rhs){return (&lhs==&rhs); }
inline bool operator!=(const Particle& lhs, const Particle& rhs){ return !(lhs == rhs); }
