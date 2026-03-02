#include "BondTradeLoader.h"
#include "LoaderUtils.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

std::optional<BondTrade*> BondTradeLoader::createTradeFromLine(std::string line)
{
    std::vector<std::string> items;
    std::istringstream record_stream(line);
    std::string item;

    while (std::getline(record_stream, item, separator)) {
        // string fields get trimmed before pushed
        items.push_back(trim(item));
    }

    if (items.size() < 7) {
        // throw std::runtime_error("Invalid line format");
        std::cerr << "Invalid line format" << '\n';
        return std::nullopt;
    }

    // TODO: maybe the while loop can be changed to explicitly name each
    // parameter by index

    try {

        // Type,TradeDate,Instrument,Counterparty,Notional,Rate,TradeId
        std::string type = items[0];
        std::string trade_date = items[1];
        std::string instrument = items[2];
        std::string counterparty = items[3];
        std::string notional = items[4];
        std::string rate = items[5];
        std::string trade_id = items[6];

        // missing argument
        BondTrade* trade = new BondTrade(trade_id, type);

        std::tm tm = {};
        std::istringstream dateStream(trade_date);
        dateStream >> std::get_time(&tm, "%Y-%m-%d");
        auto timePoint
            = std::chrono::system_clock::from_time_t(std::mktime(&tm));

        trade->setTradeDate(timePoint);

        trade->setInstrument(instrument);
        trade->setCounterparty(counterparty);
        trade->setNotional(std::stod(notional));
        trade->setRate(std::stod(rate));

        return trade;

    } catch (...) {
        return std::nullopt;
    }
}

void BondTradeLoader::loadTradesFromFile(
    std::string filename, BondTradeList& tradeList)
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
        if (lineCount == 0) {
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

std::vector<ITrade*> BondTradeLoader::loadTrades()
{
    BondTradeList tradeList;
    loadTradesFromFile(dataFile_, tradeList);

    std::vector<ITrade*> result;
    for (size_t i = 0; i < tradeList.size(); ++i) {
        result.push_back(tradeList[i]);
    }
    return result;
}

std::string BondTradeLoader::getDataFile() const { return dataFile_; }

void BondTradeLoader::setDataFile(const std::string& file) { dataFile_ = file; }

void BondTradeLoader::streamTrades(std::function<void(const ITrade&)> onTrade)
{

    // NOTE: copy of loadTradesFromFile implementation
    // TODO: datafile validation could be coupled
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
        if (lineCount == 0) {
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
