
#include "Endurance/EnduranceModelFactory.h"
#include <iostream>

/*
 *  #include your custom endurance model here, for example:
 *
 *  #include "MyModel/MyModel.h"
 */
#include "Endurance/WordModel/WordModel.h"
#include "Endurance/ByteModel/ByteModel.h"
#include "Endurance/BitModel/BitModel.h"
#include "Endurance/NullModel/NullModel.h"

using namespace NVM;

EnduranceModel *EnduranceModelFactory::CreateEnduranceModel( 
        std::string modelName )
{
    EnduranceModel *enduranceModel = NULL;

    if( modelName == "" )
        std::cout << "NVMain: EnduranceModel is not set in configuration file!\n";

    if( modelName == "RowModel" ) 
        enduranceModel = new RowModel( );

    /*
     *  Add your custom endurance model here, for example:
     *
     *  else if( modelName == "MyModel" ) enduranceModel = new MyModel( );
     */
    else if( modelName == "WordModel" ) enduranceModel = new WordModel( );
    else if( modelName == "ByteModel" ) enduranceModel = new ByteModel( );
    else if( modelName == "BitModel"  ) enduranceModel = new BitModel( );
    else if( modelName == "NullModel" ) enduranceModel = new NullModel( );


    if( enduranceModel == NULL )
        std::cout << "NVMain: Endurance model " << modelName 
            << " not found in factory. Endurance will not be modelled.\n";

    return enduranceModel;
}
