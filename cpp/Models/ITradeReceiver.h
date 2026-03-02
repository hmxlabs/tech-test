#ifndef ITRADERECEIVER_H
#define ITRADERECEIVER_H

#include "ITrade.h"

class ITradeReceiver {
public:
    virtual ~ITradeReceiver() = default;
    virtual void add(ITrade* trade) = 0;
};

#endif // ITRADERECEIVER_H
