#include "BasePricingEngine.h"

#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <thread>

BasePricingEngine::BasePricingEngine()
    : delay_(5000)
{
}

void BasePricingEngine::price(
    const ITrade* trade, IScalarResultReceiver* resultReceiver)
{
    if (resultReceiver == nullptr) {
        throw std::invalid_argument("resultReceiver_");
    }

    if (trade == nullptr) {
        throw std::invalid_argument("trade_");
    }

    priceTrade(trade, resultReceiver);
}

bool BasePricingEngine::isTradeTypeSupported(const std::string& tradeType) const
{
    return supportedTypes_.find(tradeType) != supportedTypes_.end();
}

void BasePricingEngine::addSupportedTradeType(const std::string& tradeType)
{
    supportedTypes_[tradeType] = 0;
}

int BasePricingEngine::getDelay() const { return delay_; }

void BasePricingEngine::setDelay(int delay) { delay_ = delay; }

void BasePricingEngine::priceTrade(
    const ITrade* trade, IScalarResultReceiver* resultReceiver)
{
    if (!isTradeTypeSupported(trade->getTradeType())) {
        if (trade->getTradeId().empty()) {
            throw std::invalid_argument("Trade does not have a valid ID");
        }

        resultReceiver->addError(
            trade->getTradeId(), "Trade type not supported");
        return;
    }

    std::cout << "Started pricing trade: " << trade->getTradeId() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_));
    // std::this_thread::sleep_for(std::chrono::milliseconds(20));
    double result = calculateResult();

    std::string tradeId = trade->getTradeId();
    auto& tradesToError = getTradesToError();
    auto& tradesToWarn = getTradesToWarn();

    if (tradesToError.find(tradeId) != tradesToError.end()) {
        resultReceiver->addError(tradeId, tradesToError[tradeId]);
    } else {
        resultReceiver->addResult(tradeId, result);
        if (tradesToWarn.find(tradeId) != tradesToWarn.end()) {
            resultReceiver->addError(tradeId, tradesToWarn[tradeId]);
        }
    }

    std::cout << "Completed pricing trade: " << trade->getTradeId()
              << std::endl;
}

double BasePricingEngine::calculateResult()
{
    return random_.nextDouble() * 100.0;
}

BasePricingEngine::Random::Random()
    : gen_(rd_())
    , dist_(0, std::numeric_limits<unsigned int>::max())
{
}

double BasePricingEngine::Random::nextDouble()
{
    return static_cast<double>(dist_(gen_))
        / static_cast<double>(std::numeric_limits<unsigned int>::max());
}

std::map<std::string, std::string>& BasePricingEngine::getTradesToError()
{
    static std::map<std::string, std::string> tradesToError;
    static bool initialized = false;
    if (!initialized) {
        tradesToError["GOV006"] = "Undefined error in pricing";
        initialized = true;
    }
    return tradesToError;
}

std::map<std::string, std::string>& BasePricingEngine::getTradesToWarn()
{
    static std::map<std::string, std::string> tradesToWarn;
    static bool initialized = false;
    if (!initialized) {
        tradesToWarn["FWD001"] = "Unable to calibrate model to value date";
        initialized = true;
    }
    return tradesToWarn;
}
