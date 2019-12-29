#pragma once
#include <vector>
#include <Eigen/Core>

class Particle
{
    private:
        Eigen::Vector3f position;
        Eigen::Vector3f velocity;
        Eigen::Vector3f acceleration;
        float pressure;
        int particle_type;
    public:
        const static int GST = -1; 
        const static int FLD = 0; 
        const static int WLL = 1;
        const static int DMY = 2; 
        void updPos(Eigen::Vector3f p);
        void updVel(Eigen::Vector3f v);
        void updAcc(Eigen::Vector3f a);
        void updTyp(int t);
        void updPrr(float p);
        const Eigen::Vector3f pos() const;
        const Eigen::Vector3f vel() const;
        const Eigen::Vector3f acc() const;
        const int typ() const;
        const float prr() const;
};