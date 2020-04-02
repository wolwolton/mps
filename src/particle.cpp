#include "particle.h"
#include <Eigen/Core>
#include "object.h"

using namespace MPS;
Particle::Particle()
:pos(Eigen::Vector3d::Zero()),
 vel(Eigen::Vector3d::Zero()),
 acc(Eigen::Vector3d::Zero()),
 prr(0),
 typ(GST),
 b_c(0)
{

}

Particle::Particle(const Particle& rhs)
:pos(rhs.pos),
 vel(rhs.pos),
 acc(rhs.acc),
 prr(rhs.prr),
 typ(rhs.typ),
 b_c(rhs.b_c)
{
}
