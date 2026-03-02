#ifndef LOADERUTILS_H
#define LOADERUTILS_H
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>

inline std::string trim(const std::string& s)
{
    auto start = std::find_if_not(s.begin(), s.end(), ::isspace);
    auto end = std::find_if_not(s.rbegin(), s.rend(), ::isspace).base();
    if (start >= end) {
        return "";
    } else {
        return std::string(start, end);
    }
}

inline std::vector<std::string> split(
    const std::string& s, const std::string& delimiter)
{

    std::vector<std::string> tokens;
    size_t start = 0;
    size_t pos;

    while ((pos = s.find(delimiter, start)) != std::string::npos) {
        // WARN: perhaps there could be an occasion to not trim?
        tokens.push_back(trim(s.substr(start, pos - start)));
        start = pos + delimiter.length();
    }

    tokens.push_back(trim(s.substr(start)));
    return tokens;
}

#endif
