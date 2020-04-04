#include "mmm.h"
#include "particle.h"
#include "object.h"
#include <Eigen/Core>
#include <functional>

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

MMM::MagneticBody::MagneticBody():
Bvector(),
MPS::Object(body)
{
}

MMM::MagneticBody::MagneticBody(const MMM::MagneticBody& rhs):
Bvector(rhs.Bvector),
MPS::Object(body)
{
}

void MMM::MagneticBody::setMagneticFluxDensity(std::function<Eigen::Vector3d(double,Eigen::Vector3d)> f){
    Bvector = f;
}

Eigen::Vector3d MMM::MagneticBody::getMagneticFluxDensity(double t){
    return Bvector(t,position);
}

void MMM::MakeParticle::make_ex(Environment &env){
}

MMM::MMMSolver::MMMSolver(Environment &&env):
Mps(std::move(env))
{

}

void MMM::MMMSolver::mainLoop(){
    calcGravity();
    calcViscosity();
    moveParticle();
    collision();
    calcPressure();
}