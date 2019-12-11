#ifndef __UNIFORMDISTRIBUTION_H__
#define __UNIFORMDISTRIBUTION_H__

#include "src/EnduranceDistribution.h"

namespace NVM {

class UniformDistribution : public EnduranceDistribution
{
  public:
    UniformDistribution( Config *conf );
    ~UniformDistribution( ) { }

    uint64_t GetEndurance( );

  private:
    Config *config;

    uint64_t mean;
};

};

#endif
