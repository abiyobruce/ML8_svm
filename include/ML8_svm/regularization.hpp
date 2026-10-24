// regularization.hpp: L2 regularization and the full SVM objective.
// Owner: Travor (M6)
//
// Minimising the hinge loss alone can produce a very large weight vector w
// that fits the training data too closely (overfitting). L2 regularization adds
// a penalty on the size of w, which favours a wider margin.
//
// The objective that is minimised is
//
//   J(w, b) = (lambda / 2) * ||w||^2  +  (1/n) * SUM max(0, 1 - y_i * (w.x_i + b))
//             \_____________________/     \_____________________________________/
//                   l2_penalty                           hinge_loss
//
// lambda >= 0 sets the strength of the penalty:
//   small lambda: weak penalty, narrower margin, higher risk of overfitting
//   large lambda: strong penalty, wider margin, higher risk of underfitting
//
// The bias b is not penalised; only w is.
//
// Uses Hyperplane (hyperplane.hpp) and hinge_loss (hinge_loss.hpp).
#pragma once

#include <vector>

#include <ML8_svm/hyperplane.hpp>
#include <ML8_svm/types.hpp>

namespace ml8_svm {

// L2 penalty: (lambda / 2) * ||w||^2.
// Throws InvalidArgument if lambda is negative or NaN.
// Example: w = {3,4}, lambda = 0.1 gives 0.05 * 25 = 1.25.
double l2_penalty(const Vector& w, double lambda);

// Gradient of the L2 penalty with respect to w: lambda * w.
// The optimizer adds it to the hinge-loss subgradient of w.
// Throws InvalidArgument if lambda is negative or NaN.
// Example: w = {3,4}, lambda = 0.1 gives {0.3, 0.4}.
Vector l2_gradient(const Vector& w, double lambda);

// Full objective: hinge_loss(h, X, y) + l2_penalty(h.w, lambda).
// Throws InvalidArgument if lambda is negative or NaN, or if X has no rows.
// Throws DimensionMismatch if X and y differ in length, if the rows of X have
// different lengths, or if h.w does not have one weight per feature.
double objective(const Hyperplane& h, const Matrix& X, const std::vector<int>& y,
                 double lambda);

}  // namespace ml8_svm
