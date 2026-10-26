// Unit tests for linalg.hpp: normal cases, empty vectors and mismatched sizes.
#include <cmath>
#include <string>

#include <ML8_svm/linalg.hpp>

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
    // ---- dot ----
    test_assert(approx(dot({1, 2, 3}, {4, 5, 6}), 32.0), "dot: (1,2,3).(4,5,6) = 32");
    test_assert(approx(dot({1, -2}, {-3, 4}), -11.0), "dot: negative entries");
    test_assert(approx(dot({}, {}), 0.0), "dot: two empty vectors give 0");
    expect_throws<DimensionMismatch>([] { dot({1, 2}, {1}); }, "dot: different sizes throw DimensionMismatch");
    expect_throws<DimensionMismatch>([] { dot({}, {1}); }, "dot: empty and non-empty throw DimensionMismatch");

    // ---- norm ----
    test_assert(approx(norm({3, 4}), 5.0), "norm: (3,4) = 5");
    test_assert(approx(norm({-3, -4}), 5.0), "norm: sign does not matter");
    test_assert(approx(norm({5}), 5.0), "norm: single element");
    test_assert(approx(norm({0, 0, 0}), 0.0), "norm: zero vector");
    test_assert(approx(norm({}), 0.0), "norm: empty vector");

    // ---- add and sub ----
    test_assert(add({1, 2}, {3, 4}) == Vector({4, 6}), "add: element-wise sum");
    test_assert(add({}, {}).empty(), "add: two empty vectors give an empty vector");
    test_assert(sub({5, 7}, {2, 3}) == Vector({3, 4}), "sub: element-wise difference");
    test_assert(sub({2, 3}, {2, 3}) == Vector({0, 0}), "sub: equal vectors give zeros");
    test_assert(sub({}, {}).empty(), "sub: two empty vectors give an empty vector");
    expect_throws<DimensionMismatch>([] { add({1}, {1, 2}); }, "add: different sizes throw DimensionMismatch");
    expect_throws<DimensionMismatch>([] { add({}, {1}); }, "add: empty and non-empty throw DimensionMismatch");
    expect_throws<DimensionMismatch>([] { sub({1, 2}, {1}); }, "sub: different sizes throw DimensionMismatch");
    expect_throws<DimensionMismatch>([] { sub({1}, {}); }, "sub: non-empty and empty throw DimensionMismatch");

    // ---- scale ----
    test_assert(scale({1, -2, 3}, 2.0) == Vector({2, -4, 6}), "scale: multiply by 2");
    test_assert(scale({1, -2}, -1.0) == Vector({-1, 2}), "scale: multiply by -1");
    test_assert(scale({1, 2}, 0.0) == Vector({0, 0}), "scale: multiply by 0");
    test_assert(scale({}, 5.0).empty(), "scale: empty vector stays empty");

    // ---- check_same_size ----
    check_same_size({1, 2}, {3, 4}, "test");
    check_same_size({}, {}, "test");
    test_assert(true, "check_same_size: equal sizes do not throw");
    expect_throws<DimensionMismatch>([] { check_same_size({1, 2}, {3}, "test"); },
                                     "check_same_size: different sizes throw DimensionMismatch");

    // ---- check_X_y ----
    check_X_y({{1, 2}, {3, 4}}, {1, -1}, "test");
    test_assert(true, "check_X_y: consistent X and y do not throw");
    expect_throws<InvalidArgument>([] { check_X_y({}, {}, "test"); }, "check_X_y: no samples throws InvalidArgument");
    expect_throws<InvalidArgument>([] { check_X_y({}, {1}, "test"); }, "check_X_y: empty X with labels throws InvalidArgument");
    expect_throws<DimensionMismatch>([] { check_X_y({{1, 2}}, {}, "test"); }, "check_X_y: empty y throws DimensionMismatch");
    expect_throws<DimensionMismatch>([] { check_X_y({{1, 2}, {3, 4}}, {1}, "test"); },
                                     "check_X_y: fewer labels than rows throws DimensionMismatch");
    expect_throws<DimensionMismatch>([] { check_X_y({{1, 2}, {3}}, {1, -1}, "test"); },
                                     "check_X_y: ragged second row throws DimensionMismatch");
    expect_throws<DimensionMismatch>([] { check_X_y({{1, 2}, {3, 4}, {5}}, {1, -1, 1}, "test"); },
                                     "check_X_y: ragged last row throws DimensionMismatch");

    // ---- every error can be caught as the base class SvmError ----
    expect_throws<SvmError>([] { dot({1}, {1, 2}); }, "DimensionMismatch is an SvmError");
    expect_throws<SvmError>([] { check_X_y({}, {}, "test"); }, "InvalidArgument is an SvmError");

    // ---- the error message names the function that failed ----
    string message;
    try {
        dot({1, 2}, {1});
    } catch (const SvmError& e) {
        message = e.what();
    }
    test_assert(message.find("dot") != string::npos, "dot: error message contains the function name");

    cout << "All linalg tests passed." << endl;
    return 0;
}
