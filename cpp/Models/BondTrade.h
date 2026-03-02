#ifndef BONDTRADE_H
#define BONDTRADE_H

#include <stdexcept>

#include "BaseTrade.h"

class BondTrade : public BaseTrade {
public:
    // TODO: enum
    static constexpr const char* GovBondTradeType = "GovBond";
    static constexpr const char* CorpBondTradeType = "CorpBond";

    BondTrade(const std::string& tradeId,
        const std::string& tradeType = GovBondTradeType)
        : tradeType_(tradeType)
    {
        if (tradeId.empty()) {
            throw std::invalid_argument(
                "A valid non null, non empty trade ID must be provided");
        }
        tradeId_ = tradeId;
    }

    // // templated forwarding
    // template <typename S1, typename S2>
    // BondTrade(S1&& tradeId, S2&& tradeType)
    //     : tradeType_(std::forward<S2>(tradeType))
    // {
    //     if (!tradeId.empty()) {
    //         tradeId_(std::forward<S1>(tradeId));
    //     }
    // }

    std::string getTradeType() const override { return tradeType_; }

private:
    std::string tradeType_;
};

#endif // BONDTRADE_H
