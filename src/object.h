#pragma once
#include <string>
#include <Eigen/Core>

namespace MPS{

enum ObjectType {body, config};

class Object{
    public:
        Object(ObjectType ot);
        ObjectType getObejctType();
        Eigen::Vector3d position;
    private:
        ObjectType objecttype;
    protected:
};
}
