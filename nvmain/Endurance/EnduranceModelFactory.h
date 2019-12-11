
#ifndef __ENDURANCEMODELFACTORY_H__
#define __ENDURANCEMODELFACTORY_H__

#include "Endurance/RowModel/RowModel.h"

namespace NVM {

class EnduranceModelFactory
{
  public:
    EnduranceModelFactory( ) {}
    ~EnduranceModelFactory( ) {}

    static EnduranceModel *CreateEnduranceModel( std::string modelName );
};


};

#endif
