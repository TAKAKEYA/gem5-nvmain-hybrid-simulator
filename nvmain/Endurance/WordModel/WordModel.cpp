#include "Endurance/WordModel/WordModel.h"
#include <iostream>

using namespace NVM;

WordModel::WordModel( )
{
    /*
     *  Clear the life map, which will hold all of the endurance
     *  values for each of our rows. Do this to ensure it didn't
     *  happen to be allocated somewhere that thinks it contains 
     *  values.
     */
    life.clear( );
}

WordModel::~WordModel( )
{
    /*
     *  Nothing to do here. We do not own the *config pointer, so
     *  don't delete that.
     */
}

void WordModel::SetConfig( Config *config, bool createChildren )
{
    Params *params = new Params( );
    params->SetParams( config );
    SetParams( params );

    SetGranularity( p->BusWidth * 8 );

    EnduranceModel::SetConfig( config, createChildren );
}

ncycles_t WordModel::Read( NVMainRequest *request )
{
    uint64_t row;
    uint64_t col;
    ncycles_t rv = 0;

    request->address.GetTranslatedAddress( &row, &col, NULL, NULL, NULL, NULL );

    uint64_t wordkey;
    uint64_t rowSize;
    uint64_t wordSize;
    uint64_t partitionCount;

    wordSize = p->BusWidth;
    wordSize *= p->tBURST * p->RATE;
    wordSize /= 8;

    rowSize = p->COLS * wordSize;

    /*
     *  Think of each row being partitioned into 64-bit divisions (or
     *  whatever the Bus Width is). Each row has rowSize / wordSize
     *  paritions. For the key we will use:
     *
     *  row * number of partitions + partition in this row
     */
    partitionCount = rowSize / wordSize;

    wordkey = row * partitionCount + col;

    if( IsDead( wordkey ) )
        rv = -(rv + 1);

    return rv;
}

ncycles_t WordModel::Write( NVMainRequest *request, NVMDataBlock& /*oldData*/ ) 
{
    NVMAddress address = request->address;

    /*
     *  The default life map is an stl map< uint64_t, uint64_t >. 
     *  You may map row and col to this map_key however you want.
     *  It is up to you to ensure there are no collisions here.
     */
    uint64_t row;
    uint64_t col;
    ncycles_t rv = 0;

    /*
     *  For our simple row model, we just set the key equal to the row.
     */
    address.GetTranslatedAddress( &row, &col, NULL, NULL, NULL, NULL );

    /*
     *  If using the default life map, we can call the DecrementLife
     *  function which will check if the map_key already exists. If so,
     *  the life value is decremented (write count incremented). Otherwise 
     *  the map_key is inserted with a write count of 1.
     */
    uint64_t wordkey;
    uint64_t rowSize;
    uint64_t wordSize;
    uint64_t partitionCount;

    wordSize = p->BusWidth;
    wordSize *= p->tBURST * p->RATE;
    wordSize /= 8;

    rowSize = p->COLS * wordSize;

    /*
     *  Think of each row being partitioned into 64-bit divisions (or
     *  whatever the Bus Width is). Each row has rowSize / wordSize
     *  paritions. For the key we will use:
     *
     *  row * number of partitions + partition in this row
     */
    partitionCount = rowSize / wordSize;

    wordkey = row * partitionCount + col;

    if( !DecrementLife( wordkey ) )
        rv = -1;

    return rv;
}

