#pragma once
#include <vector>
#include <Eigen/Core>

class Particle
{
    private:
    public:
        const static int GST = -1; 
        const static int FLD = 0; 
        const static int WLL = 1;
        const static int DMY = 2;
        Eigen::Vector3f pos;
        Eigen::Vector3f vel;
        Eigen::Vector3f acc;
        float prr;
        int typ; 
        void updAcc();
        void updVel();
        void updPos();
};
