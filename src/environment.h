#pragma once
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <iostream>
#include <vector>
#include <memory>
#include "object.h"
#include "particle.h"

class Environment{
    private:
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        Environment(std::vector<std::unique_ptr<Particle>> p);
        Environment();
        Environment(Environment &&rhs);
        std::vector<std::unique_ptr<Particle>> pcls;
};