#include "c_base_generator.h"

using namespace hirop_pickPlace;

CBaseGenerator::CBaseGenerator()
{
}

int CBaseGenerator::getName(std::string &name)
{
    name = this ->_name;
    return 0;
}

ENTITY_TYPE CBaseGenerator::getEntityType()
{
    return this->_entityType;
}
