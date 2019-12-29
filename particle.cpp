#include "particle.h"
#include <Eigen/Core>

Particle::Particle():position(0,0,0), velocity(0,0,0), acceleration(0,0,0), pressure(0), particle_type(GST)
{

}

void Particle::updPos(const Eigen::Vector3f &p){
    position = p;
}
void Particle::updVel(const Eigen::Vector3f &v){
    velocity = v;
}
void Particle::updAcc(const Eigen::Vector3f &a){
    acceleration = a;
}
void Particle::updTyp(const int t){
    particle_type = t;
}
void Particle::updPrr(const float p){
    pressure = p;
}
const Eigen::Vector3f Particle::pos() const{
    return position;
}
const Eigen::Vector3f Particle::vel() const{
    return velocity;
}
const Eigen::Vector3f Particle::acc() const{
    return acceleration;
}
const int Particle::typ() const{
    return particle_type;
}
const float Particle::prr() const{
    return pressure;
}


