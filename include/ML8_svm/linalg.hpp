// linalg.hpp: vector arithmetic and input-shape checks.
// Owner: Travor (M6)
//
// Implements the operations the SVM maths needs: w.x + b, ||w||, w - eta*g.
//
// Every function that combines two vectors checks that their sizes match and
// throws DimensionMismatch if they do not, so no function reads out of bounds.
//
// scale(v, k) multiplies a vector by a number. It is unrelated to the feature
// scalers in scaler.hpp.
#pragma once

#include <string>
#include <vector>

#include <ML8_svm/errors.hpp>
#include <ML8_svm/types.hpp>

namespace ml8_svm {

// ---- Vector arithmetic -----------------------------------------------------

// Dot product: a[0]*b[0] + a[1]*b[1] + ...
// Throws DimensionMismatch if a and b have different sizes.
// Example: dot({1,2,3}, {4,5,6}) = 4 + 10 + 18 = 32. Two empty vectors give 0.
double dot(const Vector& a, const Vector& b);

// Euclidean length: sqrt(v.v). The norm of an empty vector is 0.
// Example: norm({3,4}) = 5.
double norm(const Vector& v);

// Element-wise sum: result[i] = a[i] + b[i].
// Throws DimensionMismatch if a and b have different sizes.
Vector add(const Vector& a, const Vector& b);

// Element-wise difference: result[i] = a[i] - b[i].
// Throws DimensionMismatch if a and b have different sizes.
Vector sub(const Vector& a, const Vector& b);

// Multiplies every element by k: result[i] = k * v[i].
Vector scale(const Vector& v, double k);

// ---- Shape checks ----------------------------------------------------------

// Throws DimensionMismatch if a and b have different sizes.
// 'where' names the calling function and is included in the error message,
// for example check_same_size(w, x, "Hyperplane::score").
void check_same_size(const Vector& a, const Vector& b, const std::string& where);

// Checks that a feature matrix X and its label vector y fit together:
//   - X has at least one row               (otherwise InvalidArgument)
//   - X.size() == y.size()                 (otherwise DimensionMismatch)
//   - every row of X has the same length   (otherwise DimensionMismatch)
// 'where' names the calling function and is included in the error message.
void check_X_y(const Matrix& X, const std::vector<int>& y, const std::string& where);

}  // namespace ml8_svm
