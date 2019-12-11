
#ifndef __BYTEMODEL_H__
#define __BYTEMODEL_H__

#include "src/EnduranceModel.h"

namespace NVM {

class ByteModel : public EnduranceModel
{
  public:
    ByteModel( );
    ~ByteModel( );

    void SetConfig( Config *config, bool createChildren = true );

    ncycles_t Read( NVMainRequest *request );
    ncycles_t Write( NVMainRequest *request, NVMDataBlock& oldData );

};

};

#endif
