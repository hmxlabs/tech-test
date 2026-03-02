#ifndef FXTRADE_H
#define FXTRADE_H

#include "BaseTrade.h"
#include <chrono>

static_assert(__cplusplus >= 202302L);

class FxTrade : public BaseTrade {
public:
    static constexpr const char* FxSpotTradeType = "FxSpot";
    static constexpr const char* FxForwardTradeType = "FxFwd";

    //  NOTE: changed the constructor to not have default parameters
    // FxTrade(const std::string& tradeId, const std::string& tradeType)
    //     : tradeType_(tradeType)
    // {
    //     if (!tradeId.empty()) {
    //         tradeId_ = tradeId;
    //     }
    // }

    // templated forwarding (similar to rust-like trait bounds)
    // allows selecting l/r values
    template <typename S1, typename S2>
        requires std::constructible_from<std::string, S1&&>
                     && std::constructible_from<std::string, S2&&>
    FxTrade(S1&& tradeId, S2&& tradeType)
        : BaseTrade(std::forward<S1>(tradeId))
        , tradeType_(std::forward<S2>(tradeType))

    {
        // if (!tradeId.empty()) {
        //     tradeId_(std::forward<S1>(tradeId));
        // }
    }

    std::string getTradeType() const override { return tradeType_; }

    std::chrono::system_clock::time_point getValueDate() const
    {
        return valueDate_;
    }
    void setValueDate(const std::chrono::system_clock::time_point& date)
    {
        valueDate_ = date;
    }

private:
    std::string tradeType_;
    std::chrono::system_clock::time_point valueDate_;
};

#endif // FXTRADE_H
