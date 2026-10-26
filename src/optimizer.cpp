#include <ML8_svm/optimizer.hpp>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include <ML8_svm/errors.hpp>
#include <ML8_svm/hinge_loss.hpp>
#include <ML8_svm/regularization.hpp>

namespace ml8_svm {
namespace {

void check_configuration(double lambda, const OptimizerConfig& config) {
    if (!std::isfinite(lambda) || lambda < 0.0) {
        throw InvalidArgument("optimize: lambda must be finite and non-negative");
    }
    if (!std::isfinite(config.learning_rate) || config.learning_rate <= 0.0) {
        throw InvalidArgument("optimize: learning_rate must be finite and positive");
    }
    if (config.epochs == 0 || config.batch_size == 0) {
        throw InvalidArgument("optimize: epochs and batch_size must be positive");
    }
    if (!std::isfinite(config.tol) || config.tol < 0.0) {
        throw InvalidArgument("optimize: tol must be finite and non-negative");
    }
}

void check_training_data(const Hyperplane& hyperplane,
                         const Matrix& X,
                         const std::vector<int>& y) {
    if (X.empty()) {
        throw InvalidArgument("optimize: training data must not be empty");
    }
    if (X.size() != y.size()) {
        throw DimensionMismatch("optimize: sample count and label count differ");
    }
    if (X.front().empty()) {
        throw InvalidArgument("optimize: samples must contain at least one feature");
    }
    if (hyperplane.w.size() != X.front().size()) {
        throw DimensionMismatch("optimize: weight count does not match feature count");
    }

    const std::size_t feature_count = X.front().size();
    for (std::size_t row = 0; row < X.size(); ++row) {
        if (X[row].size() != feature_count) {
            throw DimensionMismatch("optimize: rows have different feature counts");
        }
        if (y[row] != -1 && y[row] != 1) {
            throw InvalidArgument("optimize: labels must be -1 or +1");
        }
        for (double value : X[row]) {
            if (!std::isfinite(value)) {
                throw InvalidArgument("optimize: feature values must be finite");
            }
        }
    }
}

}  // namespace

TrainingHistory optimize(Hyperplane& hyperplane,
                         const Matrix& X,
                         const std::vector<int>& y,
                         double lambda,
                         const OptimizerConfig& config) {
    check_configuration(lambda, config);
    check_training_data(hyperplane, X, y);

    const std::size_t sample_count = X.size();
    const std::size_t feature_count = X.front().size();

    TrainingHistory history;
    history.loss.reserve(config.epochs);

    std::vector<std::size_t> sample_order(sample_count);
    std::iota(sample_order.begin(), sample_order.end(), 0);
    std::mt19937 random_generator(config.seed);

    double previous_loss = objective(hyperplane, X, y, lambda);

    for (std::size_t epoch = 0; epoch < config.epochs; ++epoch) {
        std::shuffle(sample_order.begin(), sample_order.end(), random_generator);

        double learning_rate = config.learning_rate;
        if (config.decay) {
            learning_rate /= (1.0 + static_cast<double>(epoch));
        }

        // A batch size of 1 is SGD. A batch at least as large as the dataset
        // performs one full-batch update per epoch.
        for (std::size_t start = 0; start < sample_count; start += config.batch_size) {
            const std::size_t end = std::min(start + config.batch_size, sample_count);
            Matrix batch_X;
            std::vector<int> batch_y;
            batch_X.reserve(end - start);
            batch_y.reserve(end - start);

            for (std::size_t position = start; position < end; ++position) {
                const std::size_t sample = sample_order[position];
                batch_X.push_back(X[sample]);
                batch_y.push_back(y[sample]);
            }

            Vector weight_gradient;
            double bias_gradient = 0.0;
            hinge_subgradient(hyperplane, batch_X, batch_y,
                              weight_gradient, bias_gradient);

            const Vector penalty_gradient = l2_gradient(hyperplane.w, lambda);
            for (std::size_t feature = 0; feature < feature_count; ++feature) {
                weight_gradient[feature] += penalty_gradient[feature];
                hyperplane.w[feature] -= learning_rate * weight_gradient[feature];
            }
            // The bias is not part of the L2 penalty.
            hyperplane.b -= learning_rate * bias_gradient;
        }

        const double current_loss = objective(hyperplane, X, y, lambda);
        history.loss.push_back(current_loss);
        history.epochs_run = epoch + 1;

        if (std::abs(previous_loss - current_loss) <= config.tol) {
            history.converged = true;
            break;
        }
        previous_loss = current_loss;
    }

    return history;
}

}  // namespace ml8_svm