#include "ML8_svm/scaler.hpp"
#include "test_utils.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace ml8_svm;
using namespace std;
using Matrix = vector<vector<double>>;

template <typename Function>
void expect_exception(Function function, const string& message)
{
    try
    {
        function();
    }
    catch (const exception&)
    {
        return;
    }

    throw runtime_error(message);
}

void test_standard_scaler()
{
    Matrix X = {{1, 10}, {3, 20}, {5, 30}};
    StandardScaler scaler;

    Matrix result = scaler.fit_transform(X);

    expect_true(scaler.is_fitted(), "StandardScaler should be fitted");
    expect_near(scaler.get_mean()[0], 3.0, 0.0001, "First feature mean");
    expect_near(scaler.get_mean()[1], 20.0, 0.0001, "Second feature mean");
    expect_near(result[0][0], -1.2247, 0.001, "First scaled value");
    expect_near(result[1][0], 0.0, 0.0001, "Middle scaled value");
    expect_near(result[2][0], 1.2247, 0.001, "Last scaled value");

    Matrix original = scaler.inverse_transform(result);

    for (size_t i = 0; i < X.size(); i++)
    {
        for (size_t j = 0; j < X[i].size(); j++)
        {
            expect_near(original[i][j], X[i][j], 0.0001, "StandardScaler inverse transform");
        }
    }
}

void test_minmax_scaler()
{
    Matrix X = {{1, 10}, {3, 20}, {5, 30}};
    MinMaxScaler scaler;

    Matrix result = scaler.fit_transform(X);

    expect_true(scaler.is_fitted(), "MinMaxScaler should be fitted");
    expect_near(scaler.get_min_values()[0], 1.0, 0.0001, "First feature minimum");
    expect_near(scaler.get_max_values()[0], 5.0, 0.0001, "First feature maximum");
    expect_near(result[0][0], 0.0, 0.0001, "Minimum scaled value");
    expect_near(result[1][0], 0.5, 0.0001, "Middle scaled value");
    expect_near(result[2][0], 1.0, 0.0001, "Maximum scaled value");

    Matrix original = scaler.inverse_transform(result);

    for (size_t i = 0; i < X.size(); i++)
    {
        for (size_t j = 0; j < X[i].size(); j++)
        {
            expect_near(original[i][j], X[i][j], 0.0001, "MinMaxScaler inverse transform");
        }
    }
}

void test_custom_minmax_range()
{
    Matrix X = {{1}, {3}, {5}};
    MinMaxScaler scaler(-1.0, 1.0);

    Matrix result = scaler.fit_transform(X);

    expect_near(result[0][0], -1.0, 0.0001, "Custom minimum");
    expect_near(result[1][0], 0.0, 0.0001, "Custom middle value");
    expect_near(result[2][0], 1.0, 0.0001, "Custom maximum");
}

void test_constant_features()
{
    Matrix X = {{5, 10}, {5, 20}, {5, 30}};

    StandardScaler standard;
    Matrix standard_result = standard.fit_transform(X);

    expect_near(standard_result[0][0], 0.0, 0.0001, "StandardScaler constant feature");
    expect_near(standard_result[1][0], 0.0, 0.0001, "StandardScaler constant feature");

    MinMaxScaler minmax;
    Matrix minmax_result = minmax.fit_transform(X);

    expect_near(minmax_result[0][0], 0.0, 0.0001, "MinMaxScaler constant feature");
    expect_near(minmax_result[1][0], 0.0, 0.0001, "MinMaxScaler constant feature");

    Matrix original = minmax.inverse_transform(minmax_result);

    for (size_t i = 0; i < X.size(); i++)
    {
        expect_near(original[i][0], 5.0, 0.0001, "Restore constant feature");
    }
}

void test_errors()
{
    StandardScaler standard;
    MinMaxScaler minmax;
    Matrix X = {{1, 2}, {3, 4}};

    expect_exception([&]() { standard.transform(X); }, "StandardScaler should reject transform before fit");
    expect_exception([&]() { minmax.transform(X); }, "MinMaxScaler should reject transform before fit");

    expect_exception([&]() { standard.fit({}); }, "StandardScaler should reject empty data");
    expect_exception([&]() { minmax.fit({}); }, "MinMaxScaler should reject empty data");

    expect_exception([&]() { standard.fit({{1, 2}, {3}}); }, "StandardScaler should reject inconsistent rows");
    expect_exception([&]() { minmax.fit({{1, 2}, {3}}); }, "MinMaxScaler should reject inconsistent rows");

    expect_exception([&]() { MinMaxScaler invalid(5.0, 1.0); }, "MinMaxScaler should reject an invalid range");
}

int main()
{
    try
    {
        test_standard_scaler();
        test_minmax_scaler();
        test_custom_minmax_range();
        test_constant_features();
        test_errors();

        cout << "All scaler tests passed." << endl;
        return 0;
    }
    catch (const exception& error)
    {
        cerr << "Test failed: " << error.what() << endl;
        return 1;
    }
}
