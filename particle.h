#include <vector>
#include <Eigen/Core>

class Particle
{
    private:
        std::vector<Eigen::Vector3f> pos;
        std::vector<Eigen::Vector3f> vel;
        std::vector<Eigen::Vector3f> acc;
        std::vector<int> typ; 
        const int GST = -1; 
        const int FLD = 0; 
        const int WLL = 1;
        const int DMY = 2;
    public:
        void setupPcl_bar();
        void updAcc();
        void updVel();
        void updPos();
};
