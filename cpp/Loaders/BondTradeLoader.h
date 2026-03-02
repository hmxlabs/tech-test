#ifndef BONDTRADELOADER_H
#define BONDTRADELOADER_H

#include <memory>
#include <string>
#include <vector>

#include "../Models/BondTrade.h"
#include "../Models/BondTradeList.h"
#include "ITradeLoader.h"

class BondTradeLoader : public ITradeLoader {
private:
    static constexpr char separator = ',';
    std::string dataFile_;

    std::optional<BondTrade*> createTradeFromLine(std::string line);
    void loadTradesFromFile(std::string filename, BondTradeList& tradeList);

public:
    std::vector<ITrade*> loadTrades() override;
    std::string getDataFile() const override;
    void setDataFile(const std::string& file) override;
    void streamTrades(std::function<void(const ITrade&)> onTrade) override;
};

#endif // BONDTRADELOADER_H
