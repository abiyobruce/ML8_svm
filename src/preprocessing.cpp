#include <ML8_svm/preprocessing.hpp>
#include <ML8_svm/errors.hpp>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <map>
#include <numeric>
#include <random>
#include <set>

namespace ml8_svm {

namespace {

// Fisher-Yates with mt19937: same seed -> same order.
void permute(std::vector<std::size_t>& v, std::mt19937& rng) {
    for (std::size_t i = v.size(); i > 1; --i) std::swap(v[i - 1], v[rng() % i]);
}

Dataset subset(const Dataset& d, const std::vector<std::size_t>& idx) {
    Dataset s;
    s.feature_names = d.feature_names;
    for (std::size_t i : idx) { s.X.push_back(d.X[i]); s.y.push_back(d.y[i]); }
    return s;
}

void check_sizes(const Dataset& d) {
    if (d.X.size() != d.y.size())
        throw DimensionMismatch("X and y have different sample counts");
}

} // namespace

void encode_binary_labels(Dataset& d) {
    std::set<int> classes(d.y.begin(), d.y.end());
    if (classes.size() != 2) throw InvalidArgument("expected exactly two classes");
    const int low = *classes.begin();              // smaller label -> -1
    for (int& v : d.y) v = (v == low) ? -1 : 1;
}

void impute_missing(Dataset& d) {
    check_sizes(d);
    if (d.X.empty()) return;
    const std::size_t m = d.X[0].size();
    for (const auto& r : d.X)
        if (r.size() != m) throw DimensionMismatch("rows have different lengths");
    for (std::size_t j = 0; j < m; ++j) {
        double sum = 0.0; std::size_t n = 0;
        for (const auto& r : d.X) {
            if (std::isinf(r[j])) {
                throw InvalidArgument("feature values must not be infinite");
            }
            if (!std::isnan(r[j])) { sum += r[j]; ++n; }
        }
        if (n == 0) throw InvalidArgument("column has no valid values");
        const double mean = sum / static_cast<double>(n);
        for (auto& r : d.X) if (std::isnan(r[j])) r[j] = mean;
    }
}

void shuffle(Dataset& d, unsigned seed) {
    check_sizes(d);
    std::vector<std::size_t> idx(d.y.size());
    std::iota(idx.begin(), idx.end(), std::size_t{0});
    std::mt19937 rng(seed);
    permute(idx, rng);
    d = subset(d, idx);
}

void validate(const Dataset& d) {
    if (d.X.empty() || d.y.empty()) throw InvalidArgument("dataset is empty");
    check_sizes(d);
    const std::size_t m = d.X[0].size();
    if (m == 0) throw InvalidArgument("samples have no features");
    for (const auto& r : d.X) {
        if (r.size() != m) throw DimensionMismatch("inconsistent feature count");
        for (double value : r) {
            if (!std::isfinite(value)) {
                throw InvalidArgument("feature values must be finite; impute missing values first");
            }
        }
    }
    std::set<int> classes(d.y.begin(), d.y.end());
    if (classes.size() != 2) throw InvalidArgument("expected exactly two classes");
}

Split train_test_split(const Dataset& d, double test_ratio, unsigned seed) {
    if (!(test_ratio > 0.0 && test_ratio < 1.0))
        throw InvalidArgument("test_ratio must be in (0, 1)");
    validate(d);

    std::map<int, std::vector<std::size_t>> by_class;
    for (std::size_t i = 0; i < d.y.size(); ++i) by_class[d.y[i]].push_back(i);

    std::mt19937 rng(seed);
    std::vector<std::size_t> train, test;
    for (auto& kv : by_class) {
        auto& v = kv.second;
        if (v.size() < 2) throw InvalidArgument("each class needs at least 2 samples");
        permute(v, rng);
        std::size_t nt = static_cast<std::size_t>(std::lround(test_ratio * static_cast<double>(v.size())));
        nt = std::min(std::max<std::size_t>(nt, 1), v.size() - 1); // keep both sets non-empty
        test.insert(test.end(), v.begin(), v.begin() + static_cast<std::ptrdiff_t>(nt));
        train.insert(train.end(), v.begin() + static_cast<std::ptrdiff_t>(nt), v.end());
    }
    permute(train, rng);   // mix the classes
    permute(test, rng);
    return Split{subset(d, train), subset(d, test)};
}

} // namespace ml8_svm
