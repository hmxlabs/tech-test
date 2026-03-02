#ifndef PRICINGENGINECONFIGITEM_H
#define PRICINGENGINECONFIGITEM_H

#include <string>

class PricingEngineConfigItem {
public:
    std::string getTradeType() const { return tradeType_; }
    void setTradeType(const std::string& type) { tradeType_ = type; }

    std::string getAssembly() const { return assembly_; }
    void setAssembly(const std::string& assembly) { assembly_ = assembly; }

    std::string getTypeName() const { return typeName_; }
    void setTypeName(const std::string& typeName) { typeName_ = typeName; }

private:
    std::string tradeType_;
    std::string assembly_;
    std::string typeName_;
};

#endif // PRICINGENGINECONFIGITEM_H
