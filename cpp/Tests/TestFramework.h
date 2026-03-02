#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#define ASSERT_THAT(actual, matcher)                                           \
    do {                                                                       \
        if (!(matcher)(actual)) {                                              \
            std::cerr << "ASSERTION FAILED at " << __FILE__ << ":" << __LINE__ \
                      << std::endl;                                            \
            std::cerr << "  Expected: " << #matcher << std::endl;              \
            std::cerr << "  Actual: " << actual << std::endl;                  \
            throw std::runtime_error("Test assertion failed");                 \
        }                                                                      \
    } while (0)

#define ASSERT_EQ(actual, expected)                                            \
    do {                                                                       \
        if ((actual) != (expected)) {                                          \
            std::cerr << "ASSERTION FAILED at " << __FILE__ << ":" << __LINE__ \
                      << std::endl;                                            \
            std::cerr << "  Expected: " << (expected) << std::endl;            \
            std::cerr << "  Actual: " << (actual) << std::endl;                \
            throw std::runtime_error("Test assertion failed");                 \
        }                                                                      \
    } while (0)

#define ASSERT_NEAR(actual, expected, epsilon)                                 \
    do {                                                                       \
        if (std::abs((actual) - (expected)) > (epsilon)) {                     \
            std::cerr << "ASSERTION FAILED at " << __FILE__ << ":" << __LINE__ \
                      << std::endl;                                            \
            std::cerr << "  Expected: " << (expected) << " (within "           \
                      << (epsilon) << ")" << std::endl;                        \
            std::cerr << "  Actual: " << (actual) << std::endl;                \
            throw std::runtime_error("Test assertion failed");                 \
        }                                                                      \
    } while (0)

#define ASSERT_TRUE(condition)                                                 \
    do {                                                                       \
        if (!(condition)) {                                                    \
            std::cerr << "ASSERTION FAILED at " << __FILE__ << ":" << __LINE__ \
                      << std::endl;                                            \
            std::cerr << "  Expected: true" << std::endl;                      \
            std::cerr << "  Actual: false" << std::endl;                       \
            throw std::runtime_error("Test assertion failed");                 \
        }                                                                      \
    } while (0)

#define ASSERT_FALSE(condition)                                                \
    do {                                                                       \
        if (condition) {                                                       \
            std::cerr << "ASSERTION FAILED at " << __FILE__ << ":" << __LINE__ \
                      << std::endl;                                            \
            std::cerr << "  Expected: false" << std::endl;                     \
            std::cerr << "  Actual: true" << std::endl;                        \
            throw std::runtime_error("Test assertion failed");                 \
        }                                                                      \
    } while (0)

template <typename T> class IsEqualTo {
private:
    T expected_;

public:
    IsEqualTo(T expected)
        : expected_(expected)
    {
    }
    bool operator()(T actual) const { return actual == expected_; }
};

template <typename T> IsEqualTo<T> IsEqual(T expected)
{
    return IsEqualTo<T>(expected);
}

class TestRunner {
public:
    static void runAll()
    {
        std::vector<std::string> failedTests;
        int totalTests = 0;
        int passedTests = 0;

        for (auto& test : getTests()) {
            totalTests++;
            try {
                test.second();
                passedTests++;
                std::cout << "PASS: " << test.first << std::endl;
            } catch (const std::exception& e) {
                failedTests.push_back(test.first);
                std::cerr << "FAIL: " << test.first << " - " << e.what()
                          << std::endl;
            }
        }

        std::cout << "\n=== Test Summary ===" << std::endl;
        std::cout << "Total: " << totalTests << std::endl;
        std::cout << "Passed: " << passedTests << std::endl;
        std::cout << "Failed: " << failedTests.size() << std::endl;

        if (!failedTests.empty()) {
            std::cerr << "\nFailed tests:" << std::endl;
            for (const auto& test : failedTests) {
                std::cerr << "  - " << test << std::endl;
            }
            exit(1);
        }
    }

    static void registerTest(
        const std::string& name, std::function<void()> test)
    {
        getTests().push_back({ name, test });
    }

private:
    static std::vector<std::pair<std::string, std::function<void()>>>&
    getTests()
    {
        static std::vector<std::pair<std::string, std::function<void()>>> tests;
        return tests;
    }
};

#define TEST(name)                                                             \
    void test_##name();                                                        \
    namespace {                                                                \
        struct Register_##name {                                               \
            Register_##name()                                                  \
            {                                                                  \
                TestRunner::registerTest(#name, test_##name);                  \
            }                                                                  \
        } register_##name;                                                     \
    }                                                                          \
    void test_##name()

#endif // TESTFRAMEWORK_H
