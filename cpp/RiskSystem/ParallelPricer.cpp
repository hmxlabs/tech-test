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

void ParallelPricer::price(
    const std::vector<std::vector<ITrade*>>& tradeContainers,
    IScalarResultReceiver* resultReceiver)
{

    loadPricers();

    std::vector<std::thread> handles;

    for (const auto& tradeContainer : tradeContainers) {
        std::cout << "starting a thread" << '\n';

        handles.emplace_back([this, &tradeContainer, resultReceiver]() {
            // std::vector<std::pair<std::string, double>> localThreadResults;
            // WARN: I chose ScalarResults to be the concrete container type for
            // this, but it may potentially lose information if another data
            // structure gets introduced and allows duplicate tradeIDs (for
            // whatever reason),
            //
            // IScalarResultReciever could have been chosen here, but it would
            // involve drastically changing the abstract class definition
            ScalarResults localResults;

            for (ITrade* trade : tradeContainer) {
                std::string tradeType = trade->getTradeType();
                auto entry = pricers_.find(trade->getTradeType());
                if (entry == pricers_.end()) {
                    resultReceiver->addError(trade->getTradeId(),
                        "No Pricing Engines available for this trade type");
                    continue;
                }

                IPricingEngine* pricer = entry->second.get();
                pricer->price(trade, &localResults);
            }
            // acquire/lock mutex one time per thread
            {
                std::lock_guard<std::mutex> lock(resultMutex_);
                for (const auto& result : localResults) {
                    std::string tradeId = result.getTradeId();
                    std::optional<double> tradeResult = result.getResult();
                    std::optional<std::string> tradeError = result.getError();

                    if (tradeResult) {
                        resultReceiver->addResult(tradeId, tradeResult.value());
                    }
                    if (tradeError) {
                        resultReceiver->addError(tradeId, tradeError.value());
                    }
                    // std::string result = result.();
                    // std::string error = result.getTradeId();
                    // resultReceiver.
                }
                // multiple localResults combined to one
            }
        });
    }
    for (auto& handle : handles) {
        handle.join();
    };
}
