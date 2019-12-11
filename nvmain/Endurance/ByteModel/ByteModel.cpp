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

