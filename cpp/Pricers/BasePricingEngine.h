#ifndef BASEPRICINGENGINE_H
#define BASEPRICINGENGINE_H

#include <map>
#include <random>
#include <string>

#include "../Models/IPricingEngine.h"
#include "../Models/IScalarResultReceiver.h"
#include "../Models/ITrade.h"

class BasePricingEngine : public IPricingEngine {
protected:
    BasePricingEngine();
    virtual ~BasePricingEngine() = default;

    void price(
        const ITrade* trade, IScalarResultReceiver* resultReceiver) override;

public:
    bool isTradeTypeSupported(const std::string& tradeType) const;

protected:
    void addSupportedTradeType(const std::string& tradeType);
    int getDelay() const;
    void setDelay(int delay);
    virtual void priceTrade(
        const ITrade* trade, IScalarResultReceiver* resultReceiver);
    virtual double calculateResult();

private:
    std::map<std::string, unsigned int> supportedTypes_;
    int delay_;

    class Random {
    public:
        Random();
        double nextDouble();

    private:
        std::random_device rd_;
        std::mt19937 gen_;
        std::uniform_int_distribution<unsigned int> dist_;
    };

    Random random_;

    static std::map<std::string, std::string>& getTradesToError();
    static std::map<std::string, std::string>& getTradesToWarn();
};

#endif // BASEPRICINGENGINE_H
