#ifndef __BITMODEL_H__
#define __BITMODEL_H__

#include "src/EnduranceModel.h"

namespace NVM {

class BitModel : public EnduranceModel
{
  public:
    BitModel( );
    ~BitModel( );

    void SetConfig( Config *config, bool createChildren = true );

    ncycles_t Read( NVMainRequest *request );
    ncycles_t Write( NVMainRequest *request, NVMDataBlock& oldData );
};

};

#endif
