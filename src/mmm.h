#include "particle.h"
#include "environment.h"
#include <Eigen/Core>
#include "object.h"
#include "mk_particle.h"

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
        private:

    };
}
}