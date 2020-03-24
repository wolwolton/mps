#pragma once
#include <Eigen/Core>
#include <vector>
#include <memory>
#include "particle.h"

class MakeParticle
{
    private:
    public:
        void make_bar(std::vector<std::unique_ptr<Particle>> &pcls);
        void make_bar(std::vector<std::unique_ptr<Particle>> &pcls, const double pcl_dist);
        void make_bar_ex(std::vector<std::unique_ptr<Particle>> &pcls, const double pcl_dist);
};