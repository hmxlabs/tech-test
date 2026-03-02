#ifndef FXTRADELOADER_H
#define FXTRADELOADER_H

#include <memory>
#include <string>
#include <vector>

#include "../Models/FxTrade.h"
#include "../Models/FxTradeList.h"
#include "ITradeLoader.h"

class FxTradeLoader : public ITradeLoader {
private:
    static constexpr char separator[] = "¬";
    std::string dataFile_;

    std::optional<FxTrade*> createTradeFromLine(std::string line);
    void loadTradesFromFile(std::string filename, FxTradeList& tradeList);

public:
    // NOTE: These methods are only here to allow the solution to compile prior
    // to the test being completed.
    std::vector<ITrade*> loadTrades() override;
    void streamTrades(std::function<void(const ITrade&)> onTrade) override;
    std::string getDataFile() const override;
    void setDataFile(const std::string& file) override;
};

#endif // FXTRADELOADER_H
