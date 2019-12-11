#include "Endurance/Distributions/Uniform.h"
#include <math.h>
#include <iostream>

using namespace NVM;

UniformDistribution::UniformDistribution( Config *conf )
{
    config = conf;


    if( conf->GetValue( "EnduranceDistMean" ) == -1 )
    {
        std::cout << "EnduranceDistMean parameter not found for normal \
            distribution!!\n";
        mean = 1000000;
    }
    else
    {
        mean = conf->GetValue( "EnduranceDistMean" );
    }
}

uint64_t UniformDistribution::GetEndurance( )
{
    return mean;
}
