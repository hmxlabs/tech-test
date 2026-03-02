#ifndef TRADELIST_H
#define TRADELIST_H

#include <vector>

#include "ITrade.h"
#include "ITradeReceiver.h"

class TradeList : public ITradeReceiver {
public:
    TradeList() = default;

    void add(ITrade* trade) override { trades_.push_back(trade); }

    size_t size() const { return trades_.size(); }
    ITrade* operator[](size_t index) const { return trades_[index]; }

    using iterator = std::vector<ITrade*>::iterator;
    using const_iterator = std::vector<ITrade*>::const_iterator;

    iterator begin() { return trades_.begin(); }
    iterator end() { return trades_.end(); }
    const_iterator begin() const { return trades_.begin(); }
    const_iterator end() const { return trades_.end(); }

private:
    std::vector<ITrade*> trades_;
};

#endif // TRADELIST_H
