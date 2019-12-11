#include "Endurance/EnduranceDistributionFactory.h"
#include <iostream>

/*
 *  #include your custom endurance distribution above, for example:
 *
 *  #include "Endurance/Distributions/MyDist.h"
 */
#include "Endurance/Distributions/Normal.h"
#include "Endurance/Distributions/Uniform.h"

using namespace NVM;

EnduranceDistribution *EnduranceDistributionFactory::CreateEnduranceDistribution( 
        std::string distName, Config *conf )
{
    EnduranceDistribution *enduranceDist = NULL;

    if( distName == "" )
        std::cout << "NVMain: EnduranceDist is not set in configuration file!\n";
    
    if( distName == "Normal" ) 
        enduranceDist = new NormalDistribution( conf );
    /*
     *  Add your custom endurance distribution here, for example:
     *
     *  else if( distName == "MyDist" ) enduranceDist = new MyDist( );
     */
    if( distName == "Uniform" ) 
        enduranceDist = new UniformDistribution( conf );


    if( enduranceDist == NULL )
        std::cout << "NVMain: Endurance distribution '" << distName 
            << "' not found in factory!\n";

    return enduranceDist;
}
