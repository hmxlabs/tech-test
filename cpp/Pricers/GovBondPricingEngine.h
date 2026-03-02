#ifndef GOVBONDPRICINGENGINE_H
#define GOVBONDPRICINGENGINE_H

#include "BasePricingEngine.h"

class GovBondPricingEngine : public BasePricingEngine {
public:
    GovBondPricingEngine()
    {
        setDelay(5000);
        addSupportedTradeType("GovBond");
    }
};

#endif // GOVBONDPRICINGENGINE_H
