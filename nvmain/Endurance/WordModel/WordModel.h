#ifndef __WORDMODEL_H__
#define __WORDMODEL_H__

#include "src/EnduranceModel.h"

namespace NVM {

class WordModel : public EnduranceModel
{
  public:
    

    void SetConfig( Config *conf, bool createChildren = true );

    ncycles_t Read( NVMainRequest *request );
    ncycles_t Write( NVMainRequest *request, NVMDataBlock& oldData );
};

};

#endif
