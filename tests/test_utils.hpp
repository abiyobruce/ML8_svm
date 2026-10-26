#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

inline void test_assert(bool condition, const std::string& message)
{
    if (!condition)
    {
        std::cerr << "TEST FAILED: " << message << std::endl;
        throw std::runtime_error(message);
    }

    std::cout << "TEST PASSED: " << message << std::endl;
}

template <typename Function>
inline void expect_throw(Function function, const std::string& message)
{
    bool caught_exception = false;
    try
    {
        function();
    }
    catch (...)
    {
        caught_exception = true;
    }

    test_assert(caught_exception, message);
}

template <typename Exception, typename Function>
inline void expect_throw(Function function, const std::string& message)
{
    bool caught_expected_exception = false;
    try
    {
        function();
    }
    catch (const Exception&)
    {
        caught_expected_exception = true;
    }
    catch (...)
    {
        // A different exception does not satisfy this check.
    }

    test_assert(caught_expected_exception, message);
}

#define ASSERT_TRUE(condition) \
    test_assert(static_cast<bool>(condition), "ASSERT_TRUE: " #condition)

#define ASSERT_NEAR(actual, expected, tolerance)                              \
    test_assert(std::fabs(static_cast<double>(actual) -                       \
                          static_cast<double>(expected)) <= (tolerance),       \
                "ASSERT_NEAR: " #actual " ~= " #expected)

#define EXPECT_THROWS(expression, exception_type)                              \
    do {                                                                       \
        bool caught_expected_exception = false;                                \
        try {                                                                  \
            (void)(expression);                                                \
        } catch (const exception_type&) {                                      \
            caught_expected_exception = true;                                 \
        } catch (...) {                                                        \
        }                                                                      \
        test_assert(caught_expected_exception,                                 \
                    "EXPECT_THROWS: " #expression " throws " #exception_type); \
    } while (false)

