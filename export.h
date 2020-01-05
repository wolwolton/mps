#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "particle.h"

class Export
{
public:
    int exportPara(const std::string name, std::vector<std::unique_ptr<Particle>>& pcls);
    int exportPara(const std::string name, int i, std::vector<std::unique_ptr<Particle>>& pcls);
};