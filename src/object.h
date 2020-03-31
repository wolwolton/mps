#pragma once
#include <string>
#include <Eigen/Core>

enum ObjectType {body, config};

class Object{
    public:
        Object(ObjectType ot);
        ObjectType getObejctType();
    private:
        ObjectType objecttype;
    protected:
        Eigen::Vector3d position;
};
