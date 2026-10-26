#ifndef ML8_TEST_UTILS_HPP
#define ML8_TEST_UTILS_HPP

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

inline void expect_true(bool condition, const std::string& message)
{
    if (!condition)
    {
        std::cerr << "FAILED: " << message << std::endl;
        throw std::runtime_error(message);
    }
}

inline void expect_near(double actual, double expected, double tolerance, const std::string& message)
{
    if (std::abs(actual - expected) > tolerance)
    {
        std::cerr << "FAILED: " << message << std::endl;
        throw std::runtime_error(message);
    }
}

template <typename Function>
inline void expect_throw(Function function, const std::string& message)
{
    bool thrown = false;

    try
    {
        function();
    }
    catch (...)
    {
        thrown = true;
    }

    expect_true(thrown, message);
}

#endif