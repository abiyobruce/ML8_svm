#pragma once

#include <ML8_svm/dataset.hpp>
#include <ML8_svm/errors.hpp>

namespace ml8_svm {

/// Map the smaller of two integer classes to -1 and the larger to +1.
/// Throws InvalidArgument unless exactly two classes are present.
void encode_binary_labels(Dataset& data);

/// Replace NaN feature values with their column mean.
/// Throws DimensionMismatch for ragged data and InvalidArgument if a column
/// has no observed values or contains infinity.
void impute_missing(Dataset& data);

/// Shuffle rows and labels together using a repeatable seed.
void shuffle(Dataset& data, unsigned seed);

/// Check that samples, labels, feature counts and two classes are consistent.
/// Feature values must be finite; call impute_missing() before validation when needed.
void validate(const Dataset& data);

struct Split {
    Dataset train;
    Dataset test;
};

/// Create a seeded, stratified split. Each class needs at least two samples,
/// and test_ratio must be strictly between zero and one.
Split train_test_split(const Dataset& data, double test_ratio, unsigned seed);

} // namespace ml8_svm
