#include <algorithm>
#include <vector>

#include "../Models/ScalarResults.h"
#include "TestFramework.h"

static const std::string DummyTradeIdOne = "TradeOne";
static const double DummyResultOne = 100.00;
static const std::string DummyErrorOne = "ErrorMessageOne";

static const std::string DummyTradeIdTwo = "TradeTwo";
static const double DummyResultTwo = 50.525;
static const std::string DummyErrorTwo = "ErrorMessageTwo;";

static const std::string DummyTradeIdThree = "TradeThree";
static const double DummyResultThree = 12.5;

static const std::string DummyTradeIdFour = "TradeFour";
static const std::string DummyErrorFour = "ErrorMessageFour";

TEST(TestResultInsertion)
{
    ScalarResults results;
    results.addResult(DummyTradeIdOne, DummyResultOne);

    auto result = results[DummyTradeIdOne];
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value().getTradeId(), DummyTradeIdOne);
    ASSERT_NEAR(result.value().getResult().value(), DummyResultOne, 0.001);
}

TEST(TestErrorInsertion)
{
    ScalarResults results;
    results.addError(DummyTradeIdOne, DummyErrorOne);

    auto result = results[DummyTradeIdOne];
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value().getTradeId(), DummyTradeIdOne);
    ASSERT_EQ(result.value().getError().value(), DummyErrorOne);
}

TEST(TestCombinedErrorAndResultInsertion)
{
    ScalarResults results;
    results.addResult(DummyTradeIdOne, DummyResultOne);
    results.addError(DummyTradeIdOne, DummyErrorOne);

    auto result = results[DummyTradeIdOne];
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value().getError().value(), DummyErrorOne);
    ASSERT_NEAR(result.value().getResult().value(), DummyResultOne, 0.001);
}

TEST(TestContainsPositive)
{
    ScalarResults results;
    results.addError(DummyTradeIdOne, DummyErrorOne);
    ASSERT_TRUE(results.containsTrade(DummyTradeIdOne));

    ScalarResults results2;
    results2.addResult(DummyTradeIdOne, DummyResultOne);
    ASSERT_TRUE(results2.containsTrade(DummyTradeIdOne));
}

TEST(TestContainsNegative)
{
    ScalarResults results;
    results.addError(DummyTradeIdOne, DummyErrorOne);
    ASSERT_FALSE(results.containsTrade(DummyTradeIdTwo));

    ScalarResults results2;
    results2.addResult(DummyTradeIdOne, DummyResultTwo);
    ASSERT_FALSE(results2.containsTrade(DummyTradeIdTwo));
}

TEST(TestEnumeration)
{
    ScalarResults results;
    results.addResult(DummyTradeIdOne, DummyResultOne);
    results.addError(DummyTradeIdOne, DummyErrorOne);
    results.addResult(DummyTradeIdTwo, DummyResultTwo);
    results.addError(DummyTradeIdTwo, DummyErrorTwo);
    results.addResult(DummyTradeIdThree, DummyResultThree);
    results.addError(DummyTradeIdFour, DummyErrorFour);

    std::vector<ScalarResult> resultsList;
    for (const auto& result : results) {
        resultsList.push_back(result);
    }
    ASSERT_EQ(resultsList.size(), 4);

    auto dummyResult = *std::find_if(
        resultsList.begin(), resultsList.end(), [](const ScalarResult& r) {
            return r.getTradeId() == DummyTradeIdOne;
        });
    ASSERT_EQ(dummyResult.getTradeId(), DummyTradeIdOne);
    ASSERT_NEAR(dummyResult.getResult().value(), DummyResultOne, 0.001);
    ASSERT_EQ(dummyResult.getError().value(), DummyErrorOne);

    dummyResult = *std::find_if(
        resultsList.begin(), resultsList.end(), [](const ScalarResult& r) {
            return r.getTradeId() == DummyTradeIdTwo;
        });
    ASSERT_EQ(dummyResult.getTradeId(), DummyTradeIdTwo);
    ASSERT_NEAR(dummyResult.getResult().value(), DummyResultTwo, 0.001);
    ASSERT_EQ(dummyResult.getError().value(), DummyErrorTwo);

    dummyResult = *std::find_if(
        resultsList.begin(), resultsList.end(), [](const ScalarResult& r) {
            return r.getTradeId() == DummyTradeIdThree;
        });
    ASSERT_EQ(dummyResult.getTradeId(), DummyTradeIdThree);
    ASSERT_NEAR(dummyResult.getResult().value(), DummyResultThree, 0.001);
    ASSERT_FALSE(dummyResult.getError().has_value());

    dummyResult = *std::find_if(
        resultsList.begin(), resultsList.end(), [](const ScalarResult& r) {
            return r.getTradeId() == DummyTradeIdFour;
        });
    ASSERT_EQ(dummyResult.getTradeId(), DummyTradeIdFour);
    ASSERT_FALSE(dummyResult.getResult().has_value());
    ASSERT_EQ(dummyResult.getError().value(), DummyErrorFour);
}
