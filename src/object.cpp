#include "object.h"
#include <Eigen/Core>

using namespace MPS;
Object::Object(ObjectType ot):
objecttype(ot),
position(Eigen::Vector3d::Zero())
{

}

ObjectType Object::getObejctType(){
    return objecttype;
}

