#ifndef SERIALTRADELOADER_H
#define SERIALTRADELOADER_H

#include "../Loaders/ITradeLoader.h"
#include "../Models/ITrade.h"
#include <vector>

class SerialTradeLoader {
private:
    std::vector<std::unique_ptr<ITradeLoader>> getTradeLoaders();

public:
    std::vector<std::vector<ITrade*>> loadTrades();
};

#endif // SERIALTRADELOADER_H
