// Unit tests for regularization.hpp: normal cases, edge cases and invalid input.
#include <cmath>
#include <limits>
#include <string>
#include <vector>

#include <ML8_svm/errors.hpp>
#include <ML8_svm/regularization.hpp>

#include "tests_utils.hpp"

using namespace std;
using namespace ml8_svm;

namespace {

// True if a and b differ by at most tol.
bool approx(double a, double b, double tol = 1e-12) { return fabs(a - b) <= tol; }

// Passes only if fn() throws Exception (or a class derived from it).
// The expect_throw helper in tests_utils.hpp also passes when nothing is
// thrown and ignores the exception type, so it is not used here.
template <typename Exception, typename Function>
void expect_throws(Function fn, const string& message) {
    bool thrown = false;
    try {
        fn();
    } catch (const Exception&) {
        thrown = true;
    } catch (...) {
    }
    test_assert(thrown, message);
}

}  // namespace

int main() {
    const double nan = numeric_limits<double>::quiet_NaN();

    // ---- l2_penalty = (lambda / 2) * ||w||^2 ----
    test_assert(approx(l2_penalty({3, 4}, 0.1), 1.25), "l2_penalty: w=(3,4), lambda=0.1 gives 1.25");
    test_assert(approx(l2_penalty({-3, -4}, 0.1), 1.25), "l2_penalty: sign of w does not matter");
    test_assert(approx(l2_penalty({1, -2, 2}, 2.0), 9.0), "l2_penalty: w=(1,-2,2), lambda=2 gives 9");
    test_assert(approx(l2_penalty({1, 1}, 1000.0), 1000.0, 1e-9), "l2_penalty: large lambda");
    test_assert(approx(l2_penalty({3, 4}, 0.0), 0.0), "l2_penalty: lambda = 0 gives 0");
    test_assert(approx(l2_penalty({0, 0}, 5.0), 0.0), "l2_penalty: w = 0 gives 0");
    test_assert(approx(l2_penalty({}, 0.5), 0.0), "l2_penalty: empty w gives 0");
    expect_throws<InvalidArgument>([&] { l2_penalty({3, 4}, -0.1); }, "l2_penalty: negative lambda throws InvalidArgument");
    expect_throws<InvalidArgument>([&] { l2_penalty({3, 4}, nan); }, "l2_penalty: NaN lambda throws InvalidArgument");

    // ---- l2_gradient = lambda * w ----
    Vector w = {3, 4};
    Vector g = l2_gradient(w, 0.1);
    test_assert(approx(g[0], 0.3) && approx(g[1], 0.4), "l2_gradient: w=(3,4), lambda=0.1 gives (0.3, 0.4)");
    test_assert(w == Vector({3, 4}), "l2_gradient: input vector is not modified");
    test_assert(l2_gradient({3, 4}, 0.0) == Vector({0, 0}), "l2_gradient: lambda = 0 gives zeros");
    test_assert(l2_gradient({}, 0.5).empty(), "l2_gradient: empty w gives an empty vector");
    expect_throws<InvalidArgument>([&] { l2_gradient({3, 4}, -1.0); }, "l2_gradient: negative lambda throws InvalidArgument");
    expect_throws<InvalidArgument>([&] { l2_gradient({3, 4}, nan); }, "l2_gradient: NaN lambda throws InvalidArgument");

    // The gradient must match a numerical derivative of the penalty.
    const double eps = 1e-6;
    bool gradient_matches = true;
    for (size_t i = 0; i < w.size(); ++i) {
        Vector up = w, down = w;
        up[i] += eps;
        down[i] -= eps;
        double numeric = (l2_penalty(up, 0.1) - l2_penalty(down, 0.1)) / (2 * eps);
        if (!approx(numeric, g[i], 1e-6)) gradient_matches = false;
    }
    test_assert(gradient_matches, "l2_gradient: matches the numerical derivative of l2_penalty");

    // ---- objective = hinge loss + l2 penalty ----
    // w = (1, 0), b = 0. Sample scores are 0.5 and 2, so the hinge terms are
    // 0.5 and 0 (mean 0.25). With lambda = 0.2 the penalty is 0.1.
    Hyperplane h;
    h.w = {1, 0};
    h.b = 0.0;
    Matrix X = {{0.5, 0}, {2, 0}};
    vector<int> y = {1, 1};
    test_assert(approx(objective(h, X, y, 0.2), 0.35), "objective: hinge 0.25 + penalty 0.1 = 0.35");
    test_assert(approx(objective(h, X, y, 0.0), 0.25), "objective: lambda = 0 gives the hinge loss only");

    // One misclassified sample: score = -1, so the hinge term is 2. Penalty is 0.1.
    test_assert(approx(objective(h, {{-1, 0}}, {1}, 0.2), 2.1), "objective: misclassified sample gives 2 + 0.1");

    // The bias is not penalised. Both hyperplanes have the same w and zero hinge
    // loss on this data, so their objectives must be equal (0.5 * 0.4 * 1 = 0.2).
    Matrix Xs = {{3, 0}, {-3, 0}};
    vector<int> ys = {1, -1};
    Hyperplane h_b0, h_b1;
    h_b0.w = {1, 0};
    h_b0.b = 0.0;
    h_b1.w = {1, 0};
    h_b1.b = 0.5;
    test_assert(approx(objective(h_b0, Xs, ys, 0.4), 0.2), "objective: b = 0 gives 0.2");
    test_assert(approx(objective(h_b1, Xs, ys, 0.4), 0.2), "objective: changing b does not change the penalty");

    // ---- objective rejects invalid input ----
    expect_throws<InvalidArgument>([&] { objective(h, X, y, -0.2); }, "objective: negative lambda throws InvalidArgument");
    expect_throws<InvalidArgument>([&] { objective(h, X, y, nan); }, "objective: NaN lambda throws InvalidArgument");
    expect_throws<InvalidArgument>([&] { objective(h, {}, {}, 0.2); }, "objective: no samples throws InvalidArgument");
    expect_throws<DimensionMismatch>([&] { objective(h, X, {1}, 0.2); }, "objective: too few labels throws DimensionMismatch");
    expect_throws<DimensionMismatch>([&] { objective(h, X, {1, 1, 1}, 0.2); }, "objective: too many labels throws DimensionMismatch");
    expect_throws<DimensionMismatch>([&] { objective(h, {{1, 0}, {1}}, {1, 1}, 0.2); },
                                     "objective: ragged rows throw DimensionMismatch");

    Hyperplane h3;  // 3 weights, but the samples have 2 features
    h3.w = {1, 0, 0};
    h3.b = 0.0;
    expect_throws<DimensionMismatch>([&] { objective(h3, X, y, 0.2); },
                                     "objective: more weights than features throws DimensionMismatch");

    Hyperplane h_empty;  // no weights at all
    expect_throws<DimensionMismatch>([&] { objective(h_empty, X, y, 0.2); },
                                     "objective: empty weights throw DimensionMismatch");

    cout << "All regularization tests passed." << endl;
    return 0;
}
