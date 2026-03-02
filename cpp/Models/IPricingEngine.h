#ifndef IPRICINGENGINE_H
#define IPRICINGENGINE_H

#include "IScalarResultReceiver.h"
#include "ITrade.h"

class IPricingEngine {
public:
    virtual ~IPricingEngine() = default;
    virtual void price(
        const ITrade* trade, IScalarResultReceiver* resultReceiver)
        = 0;
};

#endif // IPRICINGENGINE_H
