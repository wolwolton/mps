#pragma once
#include <Eigen/Core>
#include <vector>
#include <memory>
#include "particle.h"
#include "environment.h"

class MakeParticle
{
    private:
    public:
        void make_bar(Environment &env);
        void make_bar(Environment &env, const double pcl_dist);
        void make_bar_ex(Environment &env, const double pcl_dist);
};