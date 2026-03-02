#ifndef SCALARRESULT_H
#define SCALARRESULT_H

#include <iostream>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <string>

class ScalarResult {
public:
    ScalarResult(const std::string& tradeId,
        const std::optional<double>& result,
        const std::optional<std::string>& error)
        : tradeId_(tradeId)
        , result_(result)
        , error_(error)
    {
        if (tradeId.empty()) {
            throw std::invalid_argument(
                "A non null, non empty trade id must be provided");
        }
    }

    std::string getTradeId() const { return tradeId_; }
    std::optional<double> getResult() const { return result_; }
    std::optional<std::string> getError() const { return error_; }

private:
    std::string tradeId_;
    std::optional<double> result_;
    std::optional<std::string> error_;
};

#endif // SCALARRESULT_H
