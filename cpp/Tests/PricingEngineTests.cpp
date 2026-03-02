#include "../Models/BondTrade.h"
#include "../Models/FxTrade.h"
#include "../Pricers/CorpBondPricingEngine.h"
#include "../Pricers/FxPricingEngine.h"
#include "../Pricers/GovBondPricingEngine.h"
#include "TestFramework.h"

TEST(TestPricerTypeConfig)
{
    GovBondPricingEngine govBondPricer;
    ASSERT_TRUE(
        govBondPricer.isTradeTypeSupported(BondTrade::GovBondTradeType));

    CorpBondPricingEngine corpBondPricer;
    ASSERT_TRUE(
        corpBondPricer.isTradeTypeSupported(BondTrade::CorpBondTradeType));

    FxPricingEngine fxPricer;
    ASSERT_TRUE(fxPricer.isTradeTypeSupported(FxTrade::FxSpotTradeType));
    ASSERT_TRUE(fxPricer.isTradeTypeSupported(FxTrade::FxForwardTradeType));
}
