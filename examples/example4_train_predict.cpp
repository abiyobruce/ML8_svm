// Train a small linear SVM and make predictions on held-out samples.
#include <ML8_svm/ML8_svm.hpp>

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    using namespace ml8_svm;

    const std::string path = argc > 1 ? argv[1] : "data/input/linear_separable.csv";

    try {
        Dataset data = load_csv(path);
        encode_binary_labels(data);
        impute_missing(data);
        validate(data);

        const Split split = train_test_split(data, 0.2, 42);

        StandardScaler scaler;
        const Matrix train_features = scaler.fit_transform(split.train.X);
        const Matrix test_features = scaler.transform(split.test.X);

        OptimizerConfig config;
        config.learning_rate = 0.1;
        config.epochs = 500;
        config.batch_size = 16;
        config.tol = 1e-6;
        config.decay = true;
        config.seed = 42;

        LinearSVM model(0.01, config);
        model.fit(train_features, split.train.y);

        const std::vector<int> predictions = model.predict(test_features);
        std::cout << "Trained on " << split.train.X.size() << " samples from "
                  << path << ".\n";
        std::cout << "Test accuracy: " << accuracy(split.test.y, predictions) << '\n';

        if (!test_features.empty()) {
            std::cout << "First test prediction: " << model.predict(test_features.front())
                      << " (actual " << split.test.y.front() << ")\n";
        }
    } catch (const SvmError& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
