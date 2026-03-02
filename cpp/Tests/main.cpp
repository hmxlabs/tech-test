#include "BondTradeLoaderTests.cpp"
#include "FxTradeLoaderTests.cpp"
#include "PricingConfigLoaderTests.cpp"
#include "PricingEngineTests.cpp"
#include "ScalarResultsTests.cpp"
#include "TestFramework.h"

int main()
{
    TestRunner::runAll();

    // PricingConfigLoader loader;
    // loader.setConfigFile("RiskSystem/PricingConfig/PricingEngines.xml");
    // loader.loadConfig();
    // FxTradeLoader loader;
    // loader.setDataFile("Loaders/TradeData/FxTrades.dat");
    // auto trades = loader.loadTrades();
    // return 0;
}
