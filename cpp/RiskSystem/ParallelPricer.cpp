#include "ParallelPricer.h"
#include "Models/IPricingEngine.h"
#include "Models/IScalarResultReceiver.h"
#include "Models/ScalarResult.h"
#include "Models/ScalarResults.h"
#include "NameResolver.h"
#include <mutex>
#include <stdexcept>
#include <thread>
#include <vector>

ParallelPricer::~ParallelPricer() { }

void ParallelPricer::loadPricers()
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

#define MAX_WORKERS 8

void ParallelPricer::price(
    const std::vector<std::vector<ITrade*>>& tradeContainers,
    IScalarResultReceiver* resultReceiver)
{
    loadPricers();

    // turn it into a flat vector of trades
    std::vector<ITrade*> trades;
    for (const auto& container : tradeContainers) {
        trades.insert(trades.end(), container.begin(), container.end());
    }

    std::counting_semaphore<MAX_WORKERS> sem(MAX_WORKERS);
    std::vector<std::thread> handles;

    for (ITrade* trade : trades) {
        sem.acquire();

        handles.emplace_back([this, trade, resultReceiver, &sem]() {
            std::string tradeType = trade->getTradeType();
            auto it = pricers_.find(tradeType);
            if (it == pricers_.end()) {
                std::lock_guard<std::mutex> lock(resultMutex_);
                resultReceiver->addError(trade->getTradeId(),
                    "No Pricing Engines available for this trade type");
            } else {
                IPricingEngine* pricer = it->second.get();
                ScalarResults result = {};
                pricer->price(trade, &result);
                {
                    std::lock_guard<std::mutex> lock(resultMutex_);

                    for (const auto& res : result) {
                        auto r = res.getResult();
                        if (r) {
                            resultReceiver->addResult(
                                trade->getTradeId(), r.value());
                        }

                        auto e = res.getError();
                        if (e) {
                            resultReceiver->addError(
                                trade->getTradeId(), e.value());
                        }
                    }
                }
            }
            sem.release();
        });
    }

    // Join all threads
    for (auto& t : handles) {
        t.join();
    }
}
