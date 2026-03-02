#include "ScreenResultPrinter.h"
#include "Loaders/LoaderUtils.h"
#include <iostream>

void ScreenResultPrinter::printResults(ScalarResults& results)
{
    for (const auto& result : results) {
        std::string tradeId = result.getTradeId();

        std::optional<double> ok = result.getResult();
        auto ok_str = ok.has_value() ? std::format(" : {}", ok.value()) : "";

        std::optional<std::string> error = result.getError();
        auto error_str
            = error.has_value() ? std::format(" : {}", error.value()) : "";

        std::cout << tradeId << ok_str << error_str << '\n';
    }
}
