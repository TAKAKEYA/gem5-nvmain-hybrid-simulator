
#ifndef __ENDURANCEDISTRIBUTIONFACTORY_H__
#define __ENDURANCEDISTRIBUTIONFACTORY_H__

#include "src/EnduranceDistribution.h"
#include "src/Config.h"

namespace NVM {

class EnduranceDistributionFactory
{
  public:
    EnduranceDistributionFactory( ) { }
    ~EnduranceDistributionFactory( ) { }

    static EnduranceDistribution *CreateEnduranceDistribution( 
            std::string distName, Config *conf );
};

};


#endif
