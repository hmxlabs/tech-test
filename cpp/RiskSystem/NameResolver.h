#include "Pricers/CorpBondPricingEngine.h"
#include "Pricers/FxPricingEngine.h"
#include "Pricers/GovBondPricingEngine.h"
#include <functional>
#include <memory>
#include <stdexcept>

// singleton class name resolver
class NameResolver {
public:
    static NameResolver& instance()
    {
        static NameResolver resolver;
        return resolver;
    }

    // Lookup by string
    /// Can error if type name is not registered
    std::unique_ptr<IPricingEngine> create(const std::string& typeName)
    {
        auto it = resolver_.find(typeName);
        if (it != resolver_.end()) {
            // successful return map kv key
            return it->second();
        }

        // potentially std::bad_function_call may be a suitable error here?
        throw std::runtime_error(
            "NameResolver could not find engine with name: " + typeName);
    }

private:
    NameResolver()
    {
#define RESOLVE_NAME(Type)                                                     \
    resolver_.emplace("HmxLabs.TechTest.Pricers." #Type,                       \
        []() { return std::make_unique<Type>(); })

        // DISCUSSION: This solution would imply that every Engine type needs to
        // be registered here. Perhaps it could belong in a separate config?
        // expands to register names of engine
        RESOLVE_NAME(GovBondPricingEngine);
        RESOLVE_NAME(CorpBondPricingEngine);
        RESOLVE_NAME(FxPricingEngine);
    }

    // I considered returning shared_ptrs of instances so that each engine is
    // only ever instantiated once.
    // std::map<std::string, std::shared_ptr<IPricingEngine>> resolver_;

    std::map<std::string, std::function<std::unique_ptr<IPricingEngine>()>>
        resolver_;
};
