#pragma once
#include <Eigen/Core>
#include <iostream>
#include "particle.h"
#include "mk_particle.h"
#include "export.h"

class Mps{
    public:
        void setupPcl();
        void run();
    private:
        void calcGravity();
        void calcViscosity();
        void calcPressure();
};

