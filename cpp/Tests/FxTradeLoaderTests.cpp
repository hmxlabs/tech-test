#include "../Loaders/FxTradeLoader.h"
#include "../Models/FxTrade.h"
#include "../Models/TradeList.h"
#include "TestFramework.h"
#include <chrono>
#include <cmath>
#include <ctime>

static TradeList* fxTradeList = nullptr;

void setUpFx()
{
    if (fxTradeList != nullptr) {
        delete fxTradeList;
    }

    FxTradeLoader loader;
    loader.setDataFile("Loaders/TradeData/FxTrades.dat");
    auto trades = loader.loadTrades();
    fxTradeList = new TradeList();
    for (auto trade : trades) {
        fxTradeList->add(trade);
    }
}

TEST(TestFxTradeLoadCount)
{
    setUpFx();
    ASSERT_EQ(fxTradeList->size(), 4);
}

TEST(TestFxTradeLoadAccuracyOfFirstTrade)
{
    setUpFx();
    FxTrade* trade = dynamic_cast<FxTrade*>((*fxTradeList)[0]);
    ASSERT_TRUE(trade != nullptr);

    ASSERT_EQ(trade->getTradeType(), FxTrade::FxSpotTradeType);

    std::tm tm = {};
    tm.tm_year = 2012 - 1900;
    tm.tm_mon = 10 - 1;
    tm.tm_mday = 8;
    auto expectedDate
        = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    auto actualDate = trade->getTradeDate();
    auto diff = std::chrono::duration_cast<std::chrono::hours>(
        actualDate - expectedDate)
                    .count();
    ASSERT_TRUE(std::abs(diff) < 24);

    ASSERT_EQ(trade->getInstrument(), "EURUSD");
    ASSERT_EQ(trade->getCounterparty(), "CSI,AG");
    ASSERT_NEAR(trade->getNotional(), 145000000.0, 0.01);
    ASSERT_NEAR(trade->getRate(), 0.97562, 0.00001);

    std::tm valueTm = {};
    valueTm.tm_year = 2012 - 1900;
    valueTm.tm_mon = 10 - 1;
    valueTm.tm_mday = 11;
    auto expectedValueDate
        = std::chrono::system_clock::from_time_t(std::mktime(&valueTm));
    auto actualValueDate = trade->getValueDate();
    auto valueDiff = std::chrono::duration_cast<std::chrono::hours>(
        actualValueDate - expectedValueDate)
                         .count();
    ASSERT_TRUE(std::abs(valueDiff) < 24);
}

TEST(TestFxTradeLoadAccuracyOfLastTrade)
{
    setUpFx();
    FxTrade* trade = dynamic_cast<FxTrade*>((*fxTradeList)[3]);
    ASSERT_TRUE(trade != nullptr);

    ASSERT_EQ(trade->getTradeType(), FxTrade::FxForwardTradeType);

    std::tm tm = {};
    tm.tm_year = 2012 - 1900;
    tm.tm_mon = 5 - 1;
    tm.tm_mday = 9;
    auto expectedDate
        = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    auto actualDate = trade->getTradeDate();
    auto diff = std::chrono::duration_cast<std::chrono::hours>(
        actualDate - expectedDate)
                    .count();
    ASSERT_TRUE(std::abs(diff) < 24);

    ASSERT_EQ(trade->getInstrument(), "USDJPY");
    ASSERT_EQ(trade->getCounterparty(), "GS");
    ASSERT_NEAR(trade->getNotional(), 1223445000.0, 0.01);
    ASSERT_NEAR(trade->getRate(), 78.983, 0.001);

    std::tm valueTm = {};
    valueTm.tm_year = 2012 - 1900;
    valueTm.tm_mon = 7 - 1;
    valueTm.tm_mday = 16;
    auto expectedValueDate
        = std::chrono::system_clock::from_time_t(std::mktime(&valueTm));
    auto actualValueDate = trade->getValueDate();
    auto valueDiff = std::chrono::duration_cast<std::chrono::hours>(
        actualValueDate - expectedValueDate)
                         .count();
    ASSERT_TRUE(std::abs(valueDiff) < 24);
}
