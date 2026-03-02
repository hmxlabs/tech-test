#ifndef ISCALARRESULTRECEIVER_H
#define ISCALARRESULTRECEIVER_H

#include <string>

class IScalarResultReceiver {
public:
    virtual ~IScalarResultReceiver() = default;
    virtual void addResult(const std::string& tradeId, double result) = 0;
    virtual void addError(const std::string& tradeId, const std::string& error)
        = 0;

    // NOTE: I would have liked to implement this, but this would involve
    // changing the IScalarResultReceiver drastically
    //
    // virutal void combineWith(IScalarResultReceiver other);
};

#endif // ISCALARRESULTRECEIVER_H
