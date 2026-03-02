#include "SerialTradeLoader.h"
#include "../Loaders/BondTradeLoader.h"
#include "../Loaders/FxTradeLoader.h"

std::vector<std::unique_ptr<ITradeLoader>> SerialTradeLoader::getTradeLoaders()
{
    std::vector<std::unique_ptr<ITradeLoader>> loaders;

    loaders.push_back(std::make_unique<BondTradeLoader>());
    loaders.back()->setDataFile("TradeData/BondTrades.dat");

    loaders.push_back(std::make_unique<FxTradeLoader>());
    loaders.back()->setDataFile("TradeData/FxTrades.dat");

    return loaders;
}

std::vector<std::vector<ITrade*>> SerialTradeLoader::loadTrades()
{
    auto loaders = getTradeLoaders();
    std::vector<std::vector<ITrade*>> result;

    for (const auto& loader : loaders) {
        result.push_back(loader->loadTrades());
    }

    return result;
}
