#include "FxTradeLoader.h"
#include "LoaderUtils.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::optional<FxTrade*> FxTradeLoader::createTradeFromLine(std::string line)
{
    std::istringstream record_stream(line);
    std::string item;

    // using a custom split function
    std::vector<std::string> items = split(line, separator);

    if (items.size() < 7) {
        // throw std::runtime_error("Invalid line format");
        std::cerr << "Invalid line format" << '\n';
        return std::nullopt;
    }

    try {

        std::string type = items[0];
        std::string trade_date = items[1];
        std::string ccy1 = items[2];
        std::string ccy2 = items[3];
        std::string amount = items[4];
        std::string rate = items[5];
        std::string value_date = items[6];
        std::string counterparty = items[7];
        std::string trade_id = items[8];

        // missing argument
        FxTrade* trade = new FxTrade(trade_id, type);

        std::tm tm = {};
        std::istringstream dateStream(trade_date);
        dateStream >> std::get_time(&tm, "%Y-%m-%d");
        auto timePoint
            = std::chrono::system_clock::from_time_t(std::mktime(&tm));

        trade->setTradeDate(timePoint);

        trade->setInstrument(ccy1 + ccy2);
        trade->setCounterparty(counterparty);
        trade->setNotional(std::stod(amount));
        trade->setRate(std::stod(rate));

        std::tm vdBuf = {};
        std::istringstream valueDateStream(value_date);
        valueDateStream >> std::get_time(&vdBuf, "%Y-%m-%d");

        auto valueDate
            = std::chrono::system_clock::from_time_t(std::mktime(&vdBuf));

        trade->setValueDate(valueDate);

        return trade;
    } catch (...) {
        return std::nullopt;
    }
    // Type¬TradeDate¬Ccy1¬Ccy2¬Amount¬Rate¬ValueDate¬Counterparty¬TradeId
    // explicit names
}

void FxTradeLoader::loadTradesFromFile(
    std::string filename, FxTradeList& tradeList)
{
    if (filename.empty()) {
        throw std::invalid_argument("Filename cannot be null");
    }

    std::ifstream stream(filename);
    if (!stream.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    int lineCount = 0;
    std::string line;
    while (std::getline(stream, line)) {
        if (lineCount < 2) {
            lineCount++;
            continue;
        }

        auto trade = createTradeFromLine(line);
        if (!trade) {
            break;
        }
        tradeList.add(trade.value());
        lineCount++;
    }
}

std::vector<ITrade*> FxTradeLoader::loadTrades()
{
    FxTradeList tradeList;
    loadTradesFromFile(dataFile_, tradeList);

    std::vector<ITrade*> result;
    for (size_t i = 0; i < tradeList.size(); ++i) {
        result.push_back(tradeList[i]);
    }
    return result;
}

std::string FxTradeLoader::getDataFile() const { return dataFile_; }

void FxTradeLoader::setDataFile(const std::string& file) { dataFile_ = file; }

void FxTradeLoader::streamTrades(std::function<void(const ITrade&)> onTrade)
{

    if (dataFile_.empty()) {
        throw std::invalid_argument("Filename cannot be null");
    }

    std::ifstream stream(dataFile_);
    if (!stream.is_open()) {
        throw std::runtime_error("Cannot open file: " + dataFile_);
    }

    int lineCount = 0;
    std::string line;
    while (std::getline(stream, line)) {
        if (lineCount < 2) {
            lineCount++;
            continue;
        }

        auto trade = createTradeFromLine(line);
        if (!trade) {
            break;
        }
        onTrade(*trade.value());
        lineCount++;
    }
}
