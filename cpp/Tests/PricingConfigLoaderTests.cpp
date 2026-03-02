#include <memory>

#include "../Models/BondTrade.h"
#include "../Models/FxTrade.h"
#include "../RiskSystem/PricingConfigLoader.h"
#include "../RiskSystem/PricingEngineConfig.h"
#include "TestFramework.h"

static PricingEngineConfig* config = nullptr;

void setUpConfig()
{
    PricingConfigLoader loader;
    loader.setConfigFile("RiskSystem/PricingConfig/PricingEngines.xml");
    config = new PricingEngineConfig(loader.loadConfig());
}

TEST(TestConfigItemCount)
{
    setUpConfig();
    ASSERT_EQ(config->size(), 4);
}

TEST(TestFirstConfigMapping)
{
    setUpConfig();
    auto configItem = (*config)[0];

    ASSERT_EQ(configItem.getTradeType(), BondTrade::GovBondTradeType);
    ASSERT_EQ(configItem.getTypeName(),
        "HmxLabs.TechTest.Pricers.GovBondPricingEngine");
    ASSERT_EQ(configItem.getAssembly(), "HmxLabs.TechTest.Pricers");
}

TEST(TestLastConfigMapping)
{
    setUpConfig();
    auto configItem = (*config)[3];
    ASSERT_EQ(configItem.getTradeType(), FxTrade::FxForwardTradeType);
    ASSERT_EQ(
        configItem.getTypeName(), "HmxLabs.TechTest.Pricers.FxPricingEngine");
    ASSERT_EQ(configItem.getAssembly(), "HmxLabs.TechTest.Pricers");
}
