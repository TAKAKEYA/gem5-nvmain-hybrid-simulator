#ifndef __NORMALDISTRIBUTION_H__
#define __NORMALDISTRIBUTION_H__

#include "src/EnduranceDistribution.h"

namespace NVM {

class NormalDistribution : public EnduranceDistribution
{
  public:
    NormalDistribution( );
    NormalDistribution( Config *conf );
    ~NormalDistribution( ) { }

    uint64_t GetEndurance( );

    void SetMean( uint64_t m ) { mean = m; }
    void SetVariance( uint64_t var ) { variance = var; }

    uint64_t GetMean( ) { return mean; }
    uint64_t GetVariance( ) { return variance; }

  private:
    Config *config;

    uint64_t mean;
    uint64_t variance;
    double nextEndurance;
};

};

#endif
