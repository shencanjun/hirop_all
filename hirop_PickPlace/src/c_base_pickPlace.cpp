#include "c_base_pickPlace.h"

using namespace hirop_pickPlace;

CBasePickPlace::CBasePickPlace()
{
}

int CBasePickPlace::getName(std::string &name)
{
    name = this->_name;
    return 0;
}

ENTITY_TYPE CBasePickPlace::getEntityType(){
    return this->_entityType;
}
