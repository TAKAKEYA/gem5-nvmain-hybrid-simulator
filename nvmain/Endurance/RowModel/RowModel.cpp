#include "Endurance/RowModel/RowModel.h"

using namespace NVM;

RowModel::RowModel( )
{
    /*
     *  Clear the life map, which will hold all of the endurance
     *  values for each of our rows. Do this to ensure it didn't
     *  happen to be allocated somewhere that thinks it contains 
     *  values.
     */
    life.clear( );
}

RowModel::~RowModel( )
{
    /*
     *  Nothing to do here. We do not own the *config pointer, so
     *  don't delete that.
     */
}

void RowModel::SetConfig( Config *conf, bool createChildren )
{
    Params *params = new Params( );
    params->SetParams( conf );
    SetParams( params );

    SetGranularity( p->COLS * 8 );

    EnduranceModel::SetConfig( conf, createChildren );
}

ncycles_t RowModel::Read( NVMainRequest *request )
{
    uint64_t row;
    ncycles_t rv = 0;

    /*
     *  For our simple row model, we just set the key equal to the row.
     */
    request->address.GetTranslatedAddress( &row, NULL, NULL, NULL, NULL, NULL );

    if( IsDead( row ) )
    {
        rv = -(rv + 1);
    }

    return rv;
}

ncycles_t RowModel::Write( NVMainRequest *request, NVMDataBlock& /*oldData*/ ) 
{
    NVMAddress address = request->address;

    /*
     *  The default life map is an stl map< uint64_t, uint64_t >. 
     *  You may map row and col to this map_key however you want.
     *  It is up to you to ensure there are no collisions here.
     */
    uint64_t row;
    ncycles_t rv = 0;

    /*
     *  For our simple row model, we just set the key equal to the row.
     */
    address.GetTranslatedAddress( &row, NULL, NULL, NULL, NULL, NULL );
    
    /*
     *  If using the default life map, we can call the DecrementLife
     *  function which will check if the map_key already exists. If so,
     *  the life value is decremented (write count incremented). Otherwise 
     *  the map_key is inserted with a write count of 1.
     */
    if( !DecrementLife( row ) )
        rv = -1;

    return rv;
}
