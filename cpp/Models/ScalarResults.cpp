#include "ScalarResults.h"

#include <optional>
#include <stdexcept>

ScalarResults::~ScalarResults() = default;

std::optional<ScalarResult> ScalarResults::operator[](
    const std::string& tradeId) const
{
    if (!containsTrade(tradeId)) {
        return std::nullopt;
    }

    std::optional<double> priceResult = std::nullopt;
    std::optional<std::string> error = std::nullopt;

    auto resultIt = results_.find(tradeId);
    if (resultIt != results_.end()) {
        priceResult = resultIt->second;
    }

    auto errorIt = errors_.find(tradeId);
    if (errorIt != errors_.end()) {
        error = errorIt->second;
    }

    return ScalarResult(tradeId, priceResult, error);
}

bool ScalarResults::containsTrade(const std::string& tradeId) const
{
    return results_.find(tradeId) != results_.end()
        || errors_.find(tradeId) != errors_.end();
}

void ScalarResults::addResult(const std::string& tradeId, double result)
{
    results_[tradeId] = result;
}

void ScalarResults::addError(
    const std::string& tradeId, const std::string& error)
{
    errors_[tradeId] = error;
}

ScalarResult ScalarResults::Iterator::operator*() const
{

    // result iterator has ended
    if (it1_ == end1_) {
        return ScalarResult(it2_->first, std::nullopt, it2_->second);
    }

    // error iterator has ended
    if (it2_ == end2_) {
        return ScalarResult(it1_->first, it1_->second, std::nullopt);
    }

    // both ongoing
    if (it1_->first == it2_->first) {
        return ScalarResult(it1_->first, it1_->second, it2_->second);
    } else if (it1_->first < it2_->first) {
        return ScalarResult(it1_->first, it1_->second, std::nullopt);
    } else if (it1_->first > it2_->first) {
        return ScalarResult(it2_->first, std::nullopt, it2_->second);
    }

    throw std::logic_error(
        "ScalarResult Iterator reached an invalid state, the iterator indexed "
        "a key which did not have either a result nor an error");
}

ScalarResults::Iterator& ScalarResults::Iterator::operator++()
{
    // advance the iterator depending on the state of the inner iterators
    if (it1_ == end1_) {
        it2_++;
    } else if (it2_ == end2_) {
        it1_++;
    } else if (it1_->first < it2_->first) {
        it1_++;
    } else if (it2_->first < it1_->first) {
        it2_++;
    } else {
        // it1_->first == it2_->first
        it1_++;
        it2_++;
    }

    return *this;
}

bool ScalarResults::Iterator::operator!=(const Iterator& other) const
{
    return it1_ != other.it1_ || it2_ != other.it2_;
}

ScalarResults::Iterator ScalarResults::begin() const
{
    return Iterator(
        results_.cbegin(), results_.cend(), errors_.cbegin(), errors_.cend());
}

ScalarResults::Iterator ScalarResults::end() const
{
    return Iterator(
        results_.cend(), results_.cend(), errors_.cend(), errors_.cend());
}
