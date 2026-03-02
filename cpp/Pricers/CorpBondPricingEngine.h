#ifndef CORPBONDPRICINGENGINE_H
#define CORPBONDPRICINGENGINE_H

#include "BasePricingEngine.h"

class CorpBondPricingEngine : public BasePricingEngine {
public:
    CorpBondPricingEngine()
    {
        setDelay(8000);
        addSupportedTradeType("CorpBond");
    }
};

#endif // CORPBONDPRICINGENGINE_H
