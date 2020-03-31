#include "object.h"

Object::Object(ObjectType ot):objecttype(ot)
{

}

ObjectType Object::getObejctType(){
    return objecttype;
}
