#include "SerialPricer.h"
#include "Models/IPricingEngine.h"
#include "NameResolver.h"

// NOTE: No need forthis as the unique_ptr will automatically cleanup
// SerialPricer::~SerialPricer() { }

// Name resolver implementation used to be here, now moved to separate file
//

void SerialPricer::loadPricers()
{
    // DISCUSSION (exercise 4): runtime type resolution is a tradeoff between
    // compile type safety (+ some runtime overhead) in favor of
    // flexibility/dynamic configuration. Additionally, refactoring becomes
    // slightly harder when working with strings instead of named identifiers,
    // the latter of which the compiler can assist with.
    //
    // I'm not sure what the exact use case of this system is - but if possible
    // I would vouch for a compile-time approach.

    PricingConfigLoader pricingConfigLoader;
    pricingConfigLoader.setConfigFile("./PricingConfig/PricingEngines.xml");
    PricingEngineConfig pricerConfig = pricingConfigLoader.loadConfig();

    // reset pricers
    pricers_.clear();

    for (const auto& configItem : pricerConfig) {

        std::string tradeType = configItem.getTradeType();
        std::string typeName = configItem.getTypeName();
        pricers_.emplace(tradeType, NameResolver::instance().create(typeName));
    }
}

void SerialPricer::price(
    const std::vector<std::vector<ITrade*>>& tradeContainers,
    IScalarResultReceiver* resultReceiver)
{
    loadPricers();

    for (const auto& tradeContainer : tradeContainers) {
        for (ITrade* trade : tradeContainer) {
            std::string tradeType = trade->getTradeType();
            auto entry = pricers_.find(trade->getTradeType());
            if (entry == pricers_.end()) {
                resultReceiver->addError(trade->getTradeId(),
                    "No Pricing Engines available for this trade type");
                continue;
            }

            IPricingEngine* pricer = entry->second.get();
            pricer->price(trade, resultReceiver);
        }
    }
}
