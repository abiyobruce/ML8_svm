// types.hpp: the two basic types used throughout the library.
// Owner: Travor (M6)
//
// Header-only: it contains only type aliases, so there is no .cpp file.
#pragma once

#include <vector>

namespace ml8_svm {

// A list of real numbers: one sample's features, a weight vector, a gradient.
// Example: the point (1.5, -2.0) is Vector{1.5, -2.0}.
using Vector = std::vector<double>;

// A table of numbers stored row by row.
//   X[i]    is sample i
//   X[i][j] is feature j of sample i
// X.size() is the number of samples and X[0].size() is the number of features.
// Labels are not stored in a Matrix. They are kept in a separate
// std::vector<int> that holds -1 or +1 for each sample.
using Matrix = std::vector<Vector>;

}  // namespace ml8_svm
