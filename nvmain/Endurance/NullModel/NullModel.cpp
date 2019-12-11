#include "Endurance/NullModel/NullModel.h"

using namespace NVM;

NullModel::NullModel( )
{
}

NullModel::~NullModel( )
{
}

ncycles_t NullModel::Read( NVMainRequest* /*request*/ )
{
    return 0;
}

ncycles_t NullModel::Write( NVMainRequest* /*request*/, NVMDataBlock& /*oldData*/ ) 
{
    return 0;
}
