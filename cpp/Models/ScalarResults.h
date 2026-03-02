#ifndef SCALARRESULTS_H
#define SCALARRESULTS_H

#include <iterator>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include "IScalarResultReceiver.h"
#include "ScalarResult.h"

class ScalarResults : public IScalarResultReceiver {
public:
    virtual ~ScalarResults();
    std::optional<ScalarResult> operator[](const std::string& tradeId) const;

    bool containsTrade(const std::string& tradeId) const;

    virtual void addResult(const std::string& tradeId, double result) override;

    virtual void addError(
        const std::string& tradeId, const std::string& error) override;

    // virtual void combineWith(ScalarResults other);

    class Iterator {
    public:
        using ResultIter = std::map<std::string, double>::const_iterator;
        using ErrorIter = std::map<std::string, std::string>::const_iterator;

        // combined
        using value_type = ScalarResult;
        using difference_type = std::ptrdiff_t;
        using pointer = ScalarResult*;
        using reference = ScalarResult&;
        using iterator_category = std::forward_iterator_tag;

        Iterator() = default;

        Iterator(ResultIter it1, ResultIter end1, ErrorIter it2, ErrorIter end2)
            : it1_(it1)
            , end1_(end1)
            , it2_(it2)
            , end2_(end2)
        {
        }

        // Iterator must be constructable from ScalarResults parent
        Iterator& operator++();
        ScalarResult operator*() const;
        bool operator!=(const Iterator& other) const;

    private:
        ResultIter it1_, end1_;
        ErrorIter it2_, end2_;
    };

    Iterator begin() const;
    Iterator end() const;

private:
    std::map<std::string, double> results_;
    std::map<std::string, std::string> errors_;
};

#endif // SCALARRESULTS_H
