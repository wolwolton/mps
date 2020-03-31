#include <vector>
#include <memory>
#include "environment.h"
#include "particle.h"
#include "object.h"

Environment::Environment(std::vector<std::unique_ptr<Particle>> p):
pcls(std::move(p))
{

}

Environment::Environment()
{

}


Environment::Environment(Environment&& rhs):
pcls(std::move(rhs.pcls))
{

}
