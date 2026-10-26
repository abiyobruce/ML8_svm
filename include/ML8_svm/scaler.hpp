#pragma once

#include <ML8_svm/errors.hpp>
#include <ML8_svm/types.hpp>

namespace ml8_svm {

/// Common interface for feature scalers.
///
/// A Scaler can be used through a base-class reference when the choice of
/// scaling method is made at run time. Derived classes provide the actual
/// calculations. The shared fitted_ flag is protected so those classes can
/// update it after a successful fit without exposing it to library users.
class Scaler {
public:
    virtual ~Scaler() = default;

    virtual void fit(const Matrix& X) = 0;
    virtual Matrix transform(const Matrix& X) const = 0;
    virtual Matrix inverse_transform(const Matrix& X) const = 0;
    virtual bool is_fitted() const = 0;

    /// Fit the selected scaler and transform the same matrix.
    Matrix fit_transform(const Matrix& X) {
        fit(X);
        return transform(X);
    }

protected:
    bool fitted_ = false;
};

/// Standardize features using the mean and population standard deviation.
/// Fit this object on training data, then use transform() on training and test data.
/// Constant features are centered and divided by 1, so their transformed values are 0.
/// transform() and inverse_transform() throw NotFitted before fit().
class StandardScaler : public Scaler {
public:
    void fit(const Matrix& X) override;
    Matrix transform(const Matrix& X) const override;
    Matrix inverse_transform(const Matrix& X) const override;

    const Vector& get_mean() const;
    const Vector& get_standard_deviation() const;
    bool is_fitted() const override;

private:
    Vector mean_;
    Vector standard_deviation_;
};

/// Map each feature into a selected numeric range (default [0, 1]).
/// Constant features map to the lower end of the range.
/// The range must have finite endpoints with new_min < new_max.
class MinMaxScaler : public Scaler {
public:
    MinMaxScaler();
    MinMaxScaler(double new_min, double new_max);

    void fit(const Matrix& X) override;
    Matrix transform(const Matrix& X) const override;
    Matrix inverse_transform(const Matrix& X) const override;

    const Vector& get_min_values() const;
    const Vector& get_max_values() const;
    bool is_fitted() const override;

private:
    Vector min_values_;
    Vector max_values_;
    double new_min_ = 0.0;
    double new_max_ = 1.0;
};

}  // namespace ml8_svm
