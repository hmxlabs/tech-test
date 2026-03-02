#ifndef PRICINGENGINECONFIG_H
#define PRICINGENGINECONFIG_H

#include <vector>

#include "PricingEngineConfigItem.h"

class PricingEngineConfig : public std::vector<PricingEngineConfigItem> {
public:
    PricingEngineConfig() = default;
};

#endif // PRICINGENGINECONFIG_H
