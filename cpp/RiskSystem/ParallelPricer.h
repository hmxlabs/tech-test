#ifndef PARALLELPRICER_H
#define PARALLELPRICER_H

#include <future>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "../Models/IPricingEngine.h"
#include "../Models/IScalarResultReceiver.h"
#include "../Models/ITrade.h"
#include "PricingConfigLoader.h"

class ParallelPricer {
private:
    std::map<std::string, std::unique_ptr<IPricingEngine>> pricers_;
    std::mutex resultMutex_;

    void loadPricers();

public:
    ~ParallelPricer();

    void price(const std::vector<std::vector<ITrade*>>& tradeContainers,
        IScalarResultReceiver* resultReceiver);
};

#endif // PARALLELPRICER_H
