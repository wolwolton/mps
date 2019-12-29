#include "particle.h"
#include <Eigen/Core>

void Particle::updPos(Eigen::Vector3f p){
    position = p;
}
void Particle::updVel(Eigen::Vector3f v){
    velocity = v;
}
void Particle::updAcc(Eigen::Vector3f a){
    acceleration = a;
}
void Particle::updTyp(int t){
    particle_type = t;
}
void Particle::updPrr(float p){
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

