
#ifndef __ROWMODEL_H__
#define __ROWMODEL_H__

#include "src/EnduranceModel.h"

namespace NVM {

class RowModel : public EnduranceModel
{
  public:
    RowModel( );
    ~RowModel( );

    void SetConfig( Config *conf, bool createChildren = true );

    ncycles_t Read( NVMainRequest *request );
    ncycles_t Write( NVMainRequest *request, NVMDataBlock& oldData );
};

};

#endif
