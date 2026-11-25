#ifndef ITRADELOADER_H
#define ITRADELOADER_H

#include "../Models/ITrade.h"
#include "../Models/TradeList.h"
#include <vector>
#include <string>

class ITradeLoader {  
protected:
    virtual ITrade* createTradeFromLine(const std::string& line) = 0;
    virtual void loadTradesFromFile(std::string& filename, TradeList& tradeList) = 0;

public:
    virtual ~ITradeLoader() = default;
    virtual std::vector<ITrade*> loadTrades() = 0;
    virtual std::string getDataFile() const = 0;
    virtual void setDataFile(const std::string& file) = 0;
};

#endif // ITRADELOADER_H
