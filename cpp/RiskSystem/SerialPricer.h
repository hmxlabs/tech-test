#ifndef SERIALPRICER_H
#define SERIALPRICER_H

#include "../Models/IPricingEngine.h"
#include "../Models/IScalarResultReceiver.h"
#include "../Models/ITrade.h"
#include "PricingConfigLoader.h"
#include <map>
#include <string>
#include <vector>

class SerialPricer {
private:
    std::map<std::string, std::unique_ptr<IPricingEngine>> pricers_;
    void loadPricers();

public:
    ~SerialPricer() = default;
    void price(const std::vector<std::vector<ITrade*>>& tradeContainers,
        IScalarResultReceiver* resultReceiver);
};

#endif // SERIALPRICER_H
