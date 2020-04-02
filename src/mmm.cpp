#include "mmm.h"
#include "particle.h"
#include <Eigen/Core>

using namespace MPS;

MMM::Particle::Particle():
m_moment(Eigen::Vector3d::Zero()),
MPS::Particle()
{
}

MMM::Particle::Particle(const MMM::Particle& rhs):
m_moment(rhs.m_moment),
MPS::Particle(rhs)
{
}

void MMM::MakeParticle::make_ex(Environment &env){

}