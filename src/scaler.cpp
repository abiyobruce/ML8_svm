#include <ML8_svm/scaler.hpp>
#include <cmath>
#include <cstddef>
#include <string>
#include <ML8_svm/errors.hpp>

namespace ml8_svm {
namespace {

// Check that a matrix has at least one sample and one feature per sample.
void check_matrix(const Matrix& X, const char* function_name) {
    if (X.empty()) {
        throw InvalidArgument(std::string(function_name) + ": data must not be empty");
    }
    if (X.front().empty()) {
        throw InvalidArgument(std::string(function_name) + ": data must contain features");
    }

    const std::size_t feature_count = X.front().size();
    for (std::size_t row = 0; row < X.size(); ++row) {
        if (X[row].size() != feature_count) {
            throw DimensionMismatch(std::string(function_name) +
                                   ": all rows must have the same number of features");
        }
        for (double value : X[row]) {
            if (!std::isfinite(value)) {
                throw InvalidArgument(std::string(function_name) +
                                      ": values must be finite; impute missing values first");
            }
        }
    }
}

// Transform and inverse_transform must receive the same feature count used by fit().
void check_feature_count(const Matrix& X, std::size_t expected_features,
                         const char* function_name) {
    check_matrix(X, function_name);
    for (const Vector& row : X) {
        if (row.size() != expected_features) {
            throw DimensionMismatch(std::string(function_name) +
                                   ": feature count does not match the fitted data");
        }
    }
}

}  // namespace

void StandardScaler::fit(const Matrix& X) {
    check_matrix(X, "StandardScaler::fit");

    const std::size_t row_count = X.size();
    const std::size_t feature_count = X.front().size();
    Vector new_mean(feature_count, 0.0);
    Vector new_standard_deviation(feature_count, 0.0);

    for (const Vector& row : X) {
        for (std::size_t feature = 0; feature < feature_count; ++feature) {
            new_mean[feature] += row[feature];
        }
    }
    for (double& value : new_mean) {
        value /= static_cast<double>(row_count);
    }

    for (const Vector& row : X) {
        for (std::size_t feature = 0; feature < feature_count; ++feature) {
            const double difference = row[feature] - new_mean[feature];
            new_standard_deviation[feature] += difference * difference;
        }
    }
    for (double& value : new_standard_deviation) {
        value = std::sqrt(value / static_cast<double>(row_count));
        // A constant feature becomes zero after centering. Dividing by one
        // keeps that result finite and lets inverse_transform restore it.
        if (value == 0.0) {
            value = 1.0;
        }
    }

    mean_ = new_mean;
    standard_deviation_ = new_standard_deviation;
    fitted_ = true;
}

Matrix StandardScaler::transform(const Matrix& X) const {
    if (!fitted_) {
        throw NotFitted("StandardScaler::transform: call fit() first");
    }
    check_feature_count(X, mean_.size(), "StandardScaler::transform");

    Matrix result = X;
    for (Vector& row : result) {
        for (std::size_t feature = 0; feature < row.size(); ++feature) {
            row[feature] = (row[feature] - mean_[feature]) /
                           standard_deviation_[feature];
        }
    }
    return result;
}

Matrix StandardScaler::inverse_transform(const Matrix& X) const {
    if (!fitted_) {
        throw NotFitted("StandardScaler::inverse_transform: call fit() first");
    }
    check_feature_count(X, mean_.size(), "StandardScaler::inverse_transform");

    Matrix result = X;
    for (Vector& row : result) {
        for (std::size_t feature = 0; feature < row.size(); ++feature) {
            row[feature] = row[feature] * standard_deviation_[feature] + mean_[feature];
        }
    }
    return result;
}

const Vector& StandardScaler::get_mean() const {
    if (!fitted_) {
        throw NotFitted("StandardScaler::get_mean: call fit() first");
    }
    return mean_;
}

const Vector& StandardScaler::get_standard_deviation() const {
    if (!fitted_) {
        throw NotFitted("StandardScaler::get_standard_deviation: call fit() first");
    }
    return standard_deviation_;
}

bool StandardScaler::is_fitted() const {
    return fitted_;
}

MinMaxScaler::MinMaxScaler() = default;

MinMaxScaler::MinMaxScaler(double new_min, double new_max)
    : new_min_(new_min), new_max_(new_max) {
    if (!std::isfinite(new_min_) || !std::isfinite(new_max_) || new_min_ >= new_max_) {
        throw InvalidArgument("MinMaxScaler: range endpoints must be finite and new_min < new_max");
    }
}

void MinMaxScaler::fit(const Matrix& X) {
    check_matrix(X, "MinMaxScaler::fit");

    const std::size_t feature_count = X.front().size();
    Vector new_min_values = X.front();
    Vector new_max_values = X.front();

    for (const Vector& row : X) {
        for (std::size_t feature = 0; feature < feature_count; ++feature) {
            if (row[feature] < new_min_values[feature]) {
                new_min_values[feature] = row[feature];
            }
            if (row[feature] > new_max_values[feature]) {
                new_max_values[feature] = row[feature];
            }
        }
    }

    min_values_ = new_min_values;
    max_values_ = new_max_values;
    fitted_ = true;
}

Matrix MinMaxScaler::transform(const Matrix& X) const {
    if (!fitted_) {
        throw NotFitted("MinMaxScaler::transform: call fit() first");
    }
    check_feature_count(X, min_values_.size(), "MinMaxScaler::transform");

    Matrix result = X;
    const double new_range = new_max_ - new_min_;
    for (Vector& row : result) {
        for (std::size_t feature = 0; feature < row.size(); ++feature) {
            const double old_range = max_values_[feature] - min_values_[feature];
            if (old_range == 0.0) {
                row[feature] = new_min_;
            } else {
                const double fraction = (row[feature] - min_values_[feature]) / old_range;
                row[feature] = new_min_ + fraction * new_range;
            }
        }
    }
    return result;
}

Matrix MinMaxScaler::inverse_transform(const Matrix& X) const {
    if (!fitted_) {
        throw NotFitted("MinMaxScaler::inverse_transform: call fit() first");
    }
    check_feature_count(X, min_values_.size(), "MinMaxScaler::inverse_transform");

    Matrix result = X;
    const double new_range = new_max_ - new_min_;
    for (Vector& row : result) {
        for (std::size_t feature = 0; feature < row.size(); ++feature) {
            const double old_range = max_values_[feature] - min_values_[feature];
            if (old_range == 0.0) {
                row[feature] = min_values_[feature];
            } else {
                const double fraction = (row[feature] - new_min_) / new_range;
                row[feature] = min_values_[feature] + fraction * old_range;
            }
        }
    }
    return result;
}

const Vector& MinMaxScaler::get_min_values() const {
    if (!fitted_) {
        throw NotFitted("MinMaxScaler::get_min_values: call fit() first");
    }
    return min_values_;
}

const Vector& MinMaxScaler::get_max_values() const {
    if (!fitted_) {
        throw NotFitted("MinMaxScaler::get_max_values: call fit() first");
    }
    return max_values_;
}

bool MinMaxScaler::is_fitted() const {
    return fitted_;
}

}  // namespace ml8_svm
