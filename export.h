#pragma once
#include <iostream>
#include "particle.h"

class Export
{
public:
    int exportPara(const std::string name, const std::vector<Particle> &pcls);
    int exportPara(const std::string name, int i, const std::vector<Particle> &pcls);
};