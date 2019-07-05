#ifndef C_BASE_GENERATOR_H
#define C_BASE_GENERATOR_H
#include "igenerator.h"

namespace hirop_pickPlace {

class CBaseGenerator:public IGenerator{
public:
    CBaseGenerator();

    int getName(std::string &name);

    ENTITY_TYPE getEntityType();

private:
    std::string _name;
    ENTITY_TYPE _entityType;
};
}
//H_DECLARE_PLUGIN(hirop_pickPlace::IGenerator)
#endif // C_BASE_GENERATOR_H
