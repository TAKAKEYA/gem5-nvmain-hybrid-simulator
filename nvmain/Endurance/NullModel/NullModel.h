#ifndef __NULLMODEL_H__
#define __NULLMODEL_H__

#include "src/EnduranceModel.h"

namespace NVM {

class NullModel : public EnduranceModel
{
  public:
    NullModel( );
    ~NullModel( );

    ncycles_t Read( NVMainRequest *request );
    ncycles_t Write( NVMainRequest *request, NVMDataBlock& oldData );
};

};

#endif
