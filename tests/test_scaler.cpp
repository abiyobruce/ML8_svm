#include <ML8_svm/scaler.hpp>
#include <ML8_svm/errors.hpp>
#include "test_utils.hpp"
#include <cmath>

using namespace ml8_svm;

int main() {
    const Matrix data = {{1.0, 10.0, 4.0}, {3.0, 20.0, 4.0},
                         {5.0, 30.0, 4.0}, {7.0, 40.0, 4.0}};

    StandardScaler standard;
    expect_throw<NotFitted>([&]() { standard.transform(data); },
                            "standard scaler needs fit before transform");

    const Matrix standardized = standard.fit_transform(data);
    test_assert(standard.is_fitted(), "standard scaler records fitted state");
    test_assert(std::abs(standard.get_mean()[0] - 4.0) < 1e-12,
                "standard scaler calculates the feature mean");
    test_assert(std::abs(standardized[0][0] + standardized[3][0]) < 1e-12,
                "standardized values are centered around zero");
    test_assert(standardized[0][2] == 0.0 && standardized[3][2] == 0.0,
                "constant feature is scaled without division by zero");

    const Matrix restored = standard.inverse_transform(standardized);
    test_assert(std::abs(restored[2][1] - data[2][1]) < 1e-12,
                "standard scaler inverse_transform restores the input");

    // The same operations can be called through the common Scaler interface.
    // fit_transform() then calls the selected scaler's virtual fit() and transform().
    Scaler& standard_interface = standard;
    const Matrix scaled_through_interface = standard_interface.fit_transform(data);
    test_assert(standard_interface.is_fitted() &&
                    std::abs(scaled_through_interface[0][0] - standardized[0][0]) < 1e-12,
                "standard scaler works through the polymorphic Scaler interface");

    MinMaxScaler minmax(-1.0, 1.0);
    const Matrix minmax_data = minmax.fit_transform(data);
    test_assert(std::abs(minmax_data[0][0] + 1.0) < 1e-12 &&
                    std::abs(minmax_data[3][0] - 1.0) < 1e-12,
                "min-max scaler maps values into the requested range");
    test_assert(minmax_data[0][2] == -1.0 && minmax_data[3][2] == -1.0,
                "constant feature maps to the lower end of the range");

    const Matrix minmax_restored = minmax.inverse_transform(minmax_data);
    test_assert(std::abs(minmax_restored[1][1] - data[1][1]) < 1e-12,
                "min-max scaler inverse_transform restores the input");
    Scaler& minmax_interface = minmax;
    const Matrix minmax_through_interface = minmax_interface.transform(data);
    test_assert(std::abs(minmax_through_interface[0][0] - minmax_data[0][0]) < 1e-12,
                "min-max scaler overrides transform through the Scaler interface");
    expect_throw<InvalidArgument>([]() { MinMaxScaler invalid(1.0, 1.0); },
                                  "min-max scaler rejects an empty output range");

    return 0;
}
