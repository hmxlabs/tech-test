#include <chrono>
#include <cmath>
#include <ctime>

#include "../Loaders/BondTradeLoader.h"
#include "../Models/BondTrade.h"
#include "../Models/TradeList.h"
#include "TestFramework.h"

static TradeList* tradeList = nullptr;

void setUp()
{
    if (tradeList != nullptr) {
        delete tradeList;
    }

    BondTradeLoader loader;
    loader.setDataFile("Loaders/TradeData/BondTrades.dat");
    auto trades = loader.loadTrades();
    tradeList = new TradeList();
    for (auto trade : trades) {
        tradeList->add(trade);
    }
}

TEST(TestTradeLoadCount)
{
    setUp();
    ASSERT_EQ(tradeList->size(), 10);
}

TEST(TestTradeLoadAccuracyOfFirstTrade)
{
    setUp();
    BondTrade* trade = dynamic_cast<BondTrade*>((*tradeList)[0]);
    ASSERT_TRUE(trade != nullptr);

    ASSERT_EQ(trade->getTradeType(), BondTrade::GovBondTradeType);

    std::tm tm = {};
    tm.tm_year = 2012 - 1900;
    tm.tm_mon = 4 - 1;
    tm.tm_mday = 17;
    auto expectedDate
        = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    auto actualDate = trade->getTradeDate();
    auto diff = std::chrono::duration_cast<std::chrono::hours>(
        actualDate - expectedDate)
                    .count();
    ASSERT_TRUE(std::abs(diff) < 24);

    ASSERT_EQ(trade->getInstrument(), "DE0001117794");
    ASSERT_EQ(trade->getCounterparty(), "CSI¬AG");
    ASSERT_NEAR(trade->getNotional(), 674500000.0, 0.01);
    ASSERT_NEAR(trade->getRate(), 105.985, 0.001);
    ASSERT_EQ(trade->getTradeId(), "GOV001");
}

TEST(TestTradeLoadAccuracyOfLastTrade)
{
    setUp();
    BondTrade* trade = dynamic_cast<BondTrade*>((*tradeList)[8]);
    ASSERT_TRUE(trade != nullptr);

    ASSERT_EQ(trade->getTradeType(), BondTrade::CorpBondTradeType);

    std::tm tm = {};
    tm.tm_year = 2012 - 1900;
    tm.tm_mon = 8 - 1;
    tm.tm_mday = 30;
    auto expectedDate
        = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    auto actualDate = trade->getTradeDate();
    auto diff = std::chrono::duration_cast<std::chrono::hours>(
        actualDate - expectedDate)
                    .count();
    ASSERT_TRUE(std::abs(diff) < 24);

    ASSERT_EQ(trade->getInstrument(), "XS0340495216");
    ASSERT_EQ(trade->getCounterparty(), "BLKROCK");
    ASSERT_NEAR(trade->getNotional(), 67000000.0, 0.01);
    ASSERT_NEAR(trade->getRate(), 120.240, 0.001);
    ASSERT_EQ(trade->getTradeId(), "CORP003");
}
