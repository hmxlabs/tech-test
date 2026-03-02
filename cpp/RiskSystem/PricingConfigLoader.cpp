#include "PricingConfigLoader.h"
#include "RiskSystem/PricingEngineConfig.h"
#include "RiskSystem/PricingEngineConfigItem.h"
#include "pugixml.cpp"
#include "third-party/pugixml.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

PricingEngineConfig PricingConfigLoader::parseXml(const std::string& content)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(content.c_str());
    if (!result) {
        std::cerr << "Invalid XML: " << result.description() << '\n';
        throw std::runtime_error(result.description());
    }

    pugi::xml_node root = doc.document_element();

    PricingEngineConfig config;

    for (auto child : root.children()) {
        const char* tradeType = child.attribute("tradeType").as_string();
        const char* assembly = child.attribute("assembly").as_string();
        const char* typeName = child.attribute("pricingEngine").as_string();

        PricingEngineConfigItem item;
        item.setTradeType(tradeType);
        item.setAssembly(assembly);
        item.setTypeName(typeName);
        config.push_back(item);
    }

    return config;
}

std::string PricingConfigLoader::getConfigFile() const { return configFile_; }

void PricingConfigLoader::setConfigFile(const std::string& file)
{
    configFile_ = file;
}

PricingEngineConfig PricingConfigLoader::loadConfig()
{

    std::ifstream file(configFile_);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    std::string file_str = std::string((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    PricingEngineConfig config = parseXml(file_str);
    // PricingEngineConfig* config = new PricingEngineConfig();

    return config;
}
