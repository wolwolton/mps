#include "particle.h"
#include "environment.h"
#include <Eigen/Core>
#include <functional>
#include "object.h"
#include "mk_particle.h"
#include "mps.h"

namespace MPS{
namespace MMM{
    class Particle : public MPS::Particle{
        public:
            Particle();
            Particle(const Particle& rhs);
            Eigen::Vector3d m_moment;
    };

    class MakeParticle : public MPS::MakeParticle{
        public:
            void make_ex(Environment &env);
    };

    class MagneticBody : public MPS::Object{
        public:
            MagneticBody();
            MagneticBody(const MagneticBody& rhs);
            void setMagneticFluxDensity(std::function<Eigen::Vector3d(double,Eigen::Vector3d)> f);
            Eigen::Vector3d getMagneticFluxDensity(double t);
        private:
            std::function<Eigen::Vector3d(double,Eigen::Vector3d)> Bvector;
    };

    class MMMSolver : public MPS::Mps{
        public:
            MMMSolver(MPS::Environment&& env);
        private:
            void mainLoop();
    };
}
}