#include "StreamingTradeLoader.h"
#include "../Loaders/BondTradeLoader.h"
#include "../Loaders/FxTradeLoader.h"
#include "Models/IPricingEngine.h"
#include "NameResolver.h"
#include "PricingConfigLoader.h"
#include <iostream>
#include <stdexcept>

std::vector<std::unique_ptr<ITradeLoader>>
StreamingTradeLoader::getTradeLoaders()
{
    std::vector<std::unique_ptr<ITradeLoader>> loaders;

    loaders.push_back(std::make_unique<BondTradeLoader>());
    loaders.back()->setDataFile("TradeData/BondTrades.dat");

    loaders.push_back(std::make_unique<FxTradeLoader>());
    loaders.back()->setDataFile("TradeData/FxTrades.dat");

    return loaders;
}

void StreamingTradeLoader::loadPricers()
{
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

StreamingTradeLoader::~StreamingTradeLoader() { }

// NOTE: ScalarResults(.h) implements IScalarResultReceiver implmeents iterator
void StreamingTradeLoader::loadAndPrice(IScalarResultReceiver* resultReceiver)
{

    loadPricers();
    std::vector<std::unique_ptr<ITradeLoader>> loaders = getTradeLoaders();

    // TODO: maybe we could allow this method to receive a pricer
    // (Parallel vs Serial)
    for (const auto& loader : loaders) {

        loader->streamTrades([this, resultReceiver](const ITrade& trade) {
            const std::string& tradeType = trade.getTradeType();

            auto it = this->pricers_.find(tradeType);
            if (it == this->pricers_.end()) {
                std::cerr << "No pricer was found for tradeType: " << tradeType
                          << '\n';
                return;
            }

            IPricingEngine* pricer = it->second.get();
            pricer->price(&trade, resultReceiver);
        }

        );
    }
}
