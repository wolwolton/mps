#include "mmm.h"
#include <Eigen/Core>

MMM::Particle::Particle():
m_moment(Eigen::Vector3d::Zero()),
Particle()
{
}

MMM::Particle::Particle(const MMM::Particle& rhs):
m_moment(rhs.m_moment),
Particle(rhs)
{
}

void MMM::MakeParticle::make_ex(Environment &env){

}