#pragma once

#include "test_utils.hpp"

inline void test_assert(bool condition, const std::string& message)
{
    expect_true(condition, message);
}
