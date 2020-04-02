#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "particle.h"
#include "environment.h"

namespace MPS{
class Export
{
public:
    int exportPara(const std::string name, const std::vector<std::unique_ptr<Particle>>& pcls);
    int exportPara(const std::string name, int i, const std::vector<std::unique_ptr<Particle>>& pcls);
    int exportPara(const std::string name, Environment& env);
    int exportPara(const std::string name, int i, Environment& env);
};
}