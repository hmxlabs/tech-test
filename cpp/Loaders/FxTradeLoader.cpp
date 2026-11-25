#include "FxTradeLoader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#include <chrono>

FxTrade* FxTradeLoader::createTradeFromLine(const std::string& line) {
    std::vector<std::string> items;
    std::stringstream ss(line);
    std::string item;

    // std::getline accepts only char for separator, ¬ is 2 bytes
    size_t start = 0;
    size_t end = line.find(separator);
    while (end != std::string::npos) {
        items.push_back(line.substr(start, end - start));
        start = end + separator.length();
        end = line.find(separator, start);
    }
    items.push_back(line.substr(start));
    
    if (items.size() < 9) {
        throw std::runtime_error("Invalid line format");
    }

    const std::string& tradeId = items[8];
    std::string tradeType;

    if (tradeId.find("SPOT") == 0) {
        tradeType = FxTrade::FxSpotTradeType;
    } else if (tradeId.find("FWD") == 0) {
        tradeType = FxTrade::FxForwardTradeType;
    } else {
        throw std::runtime_error("Unknown bond type for TradeID: " + tradeId);
    }

    std::unique_ptr<FxTrade> trade(new FxTrade(tradeId, tradeType));

    std::tm tm = {};
    std::istringstream dateStream(items[1]);
    dateStream >> std::get_time(&tm, "%Y-%m-%d");
    auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    trade->setTradeDate(timePoint);

    trade->setInstrument(items[2] + items[3]);
    trade->setNotional(std::stod(items[4]));
    trade->setRate(std::stod(items[5]));

    std::tm valueTm = {};
    std::istringstream valueDateStream(items[6]);
    valueDateStream >> std::get_time(&valueTm, "%Y-%m-%d");
    auto valueTimePoint = std::chrono::system_clock::from_time_t(std::mktime(&valueTm));
    trade->setValueDate(valueTimePoint);

    trade->setCounterparty(items[7]);

    return trade.release();
}

void FxTradeLoader::loadTradesFromFile(std::string& filename, TradeList& tradeList) {
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
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (lineCount < 2 || line.find("END") == 0) {
            lineCount++;
            continue;
        } 
        tradeList.add(createTradeFromLine(line));
        lineCount++;
    }
}

std::vector<ITrade*> FxTradeLoader::loadTrades() {
    FxTradeList tradeList;
    loadTradesFromFile(dataFile_, tradeList);

    std::vector<ITrade*> result;
    for (size_t i = 0; i < tradeList.size(); ++i) {
        result.push_back(tradeList[i]);
    }
    return result;
}

std::string FxTradeLoader::getDataFile() const {
    return dataFile_;
}

void FxTradeLoader::setDataFile(const std::string& file) {
    dataFile_ = file;
}

