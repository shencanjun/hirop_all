#ifndef C_BASE_PICKPLACE_H
#define C_BASE_PICKPLACE_H
#include "ipickPlace.h"
namespace hirop_pickPlace{

class CBasePickPlace:public IPickPlace{
public:

    CBasePickPlace();

    int getName(std::string &name) ;

    ENTITY_TYPE getEntityType() ;

private:
    std::string _name;
    ENTITY_TYPE _entityType;
};
}
//H_DECLARE_PLUGIN(hirop_pickPlace::IPickPlace)
#endif // C_BASE_PICKPLACE_H
