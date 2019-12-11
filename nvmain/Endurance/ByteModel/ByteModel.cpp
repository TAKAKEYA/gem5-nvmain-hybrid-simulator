#include "Endurance/ByteModel/ByteModel.h"
#include <iostream>

using namespace NVM;

ByteModel::ByteModel( )
{
    /*
     *  Clear the life map, which will hold all of the endurance
     *  values for each of our rows. Do this to ensure it didn't
     *  happen to be allocated somewhere that thinks it contains 
     *  values.
     */
    life.clear( );

    SetGranularity( 8 );
}

ByteModel::~ByteModel( )
{
  /*
   *  Nothing to do here. We do not own the *config pointer, so
   *  don't delete that.
   */
}

void ByteModel::SetConfig( Config *config, bool createChildren )
{
    Params *params = new Params( );
    params->SetParams( config );
    SetParams( params );

    EnduranceModel::SetConfig( config, createChildren );
}

ncycles_t ByteModel::Read( NVMainRequest *request ) 
{
    uint64_t row;
    uint64_t col;
    ncycles_t rv = 0;

    request->address.GetTranslatedAddress( &row, &col, NULL, NULL, NULL, NULL );
    
    uint64_t wordkey;
    uint64_t rowSize;
    uint64_t wordSize;
    uint64_t partitionCount;

    /* 
     * wordSize is the size of a word written to memory, usually a cacheline. 
     * This size is in bytes 
     */
    wordSize = p->BusWidth;
    wordSize *= p->tBURST * p->RATE;
    wordSize /= 8;

    /* Size of a row in bytes */
    rowSize = p->COLS * wordSize;

    /* Check each byte to see if it was modified */
    for( int i = (int)wordSize - 1; i >= 0; --i )
    {
        /*
         *  Think of each row being partitioned into 8-bit divisions. Each 
         *  row has rowSize / 8 paritions. For the key we will use:
         *
         *  row * number of partitions + partition in this row
         */
        partitionCount = ( rowSize / 8 );

        wordkey = row * partitionCount + col * wordSize + i;
      
        if( IsDead( wordkey ) )
        {
            rv = -(rv + 1);  
            return rv;
        }
    }

    return rv;
}
ncycles_t ByteModel::Write( NVMainRequest *request, NVMDataBlock& oldData ) 
{
    NVMDataBlock& newData = request->data;
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

    /* 
     * wordSize is the size of a word written to memory, usually a cacheline. 
     * This size is in bytes 
     */
    wordSize = p->BusWidth;
    wordSize *= p->tBURST * p->RATE;
    wordSize /= 8;

    /* Size of a row in bytes */
    rowSize = p->COLS * wordSize;

    /* Check each byte to see if it was modified */
    for( int i = (int)wordSize - 1; i >= 0; --i )
    {
        uint8_t oldByte, newByte;

        oldByte = oldData.GetByte( i );
        newByte = newData.GetByte( i );

        if( oldByte == newByte ) 
            continue;

        /*
         *  Think of each row being partitioned into 8-bit divisions. Each 
         *  row has rowSize / 8 paritions. For the key we will use:
         *
         *  row * number of partitions + partition in this row
         */
        partitionCount = ( rowSize / 8 );

        wordkey = row * partitionCount + col * wordSize + i;
      
        if( !DecrementLife( wordkey ) )
            rv = -1;  
    }

    return rv;
}


