#ifndef ITRADE_H
#define ITRADE_H

#include <chrono>
#include <memory>
#include <string>

class ITrade {
public:
    virtual ~ITrade() = default;

    virtual std::chrono::system_clock::time_point getTradeDate() const = 0;
    virtual void setTradeDate(const std::chrono::system_clock::time_point& date)
        = 0;

    virtual std::string getInstrument() const = 0;
    virtual void setInstrument(const std::string& instrument) = 0;

    virtual std::string getCounterparty() const = 0;
    virtual void setCounterparty(const std::string& counterparty) = 0;

    virtual double getNotional() const = 0;
    virtual void setNotional(double notional) = 0;

    virtual double getRate() const = 0;
    virtual void setRate(double rate) = 0;

    virtual std::string getTradeType() const = 0;
    virtual std::string getTradeId() const = 0;
};

#endif // ITRADE_H
