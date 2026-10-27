# ML8_svm

ML8_svm is a reusable C++17 library for binary classification with a linear Support Vector Machine. The project implements the model and its training steps directly in C++, without a machine-learning dependency. 
It includes CSV loading, preprocessing, feature scaling, optimization, prediction, evaluation, tests, and runnable examples.

The classifier uses labels `-1` and `+1` and minimizes the regularized hinge-loss objective:

```text
J(w, b) = (lambda / 2) * ||w||^2
        + (1 / n) * sum(max(0, 1 - y_i * (w . x_i + b)))
```

The decision score is `w . x + b`. A score of zero is assigned to class `+1`. The width of the margin is `2 / ||w||`.

## Project Objectives

- Build a small, reusable SVM library with a clear public interface.
- Implement the linear binary classifier from the objective function through training and evaluation.
- Keep public headers in `include/ML8_svm/` and implementation files in `src/`.
- Check inputs and report errors through a common exception hierarchy.
- Demonstrate normal use and important edge cases with tests and examples.
- Document how to build, install, and use the library.

## Features

- Numeric CSV loading with configurable delimiter and label column.
- Binary label encoding, mean imputation, seeded shuffling, validation, and stratified train/test splitting.
- `StandardScaler` and `MinMaxScaler`, including inverse transforms and constant-feature handling.
- A shared `Scaler` interface for using either scaling method through runtime polymorphism.
- Hyperplane scores, signed distances, functional and geometric margins, and margin width.
- Mean hinge loss, its subgradient, L2 regularization, and the full training objective.
- Batch, stochastic, and mini-batch gradient updates, optional learning-rate decay, seeded shuffling, and tolerance-based stopping.
- Support-vector identification and a `LinearSVM` class for fitting, scoring, and prediction.
- Confusion matrix, accuracy, precision, recall, F1 score, and a text classification report.

## Project Structure

```text
ML8_svm/
|-- CMakeLists.txt
|-- cmake/ML8_svmConfig.cmake.in
|-- include/ML8_svm/       Public headers and umbrella header
|-- src/                   Library implementation
|-- tests/                 Dependency-free unit and pipeline tests
|-- examples/              Seven learning examples and a lambda sweep
|-- data/input/            Synthetic and Iris two-class CSV files
|-- data/output/           Generated prediction and experiment results
|-- presentation/          Final project presentation
`-- reports/               Weekly reports, final report, figures, AI declaration
```

Include the complete public API with:

```cpp
#include <ML8_svm/ML8_svm.hpp>
```

## Requirements

- A C++17 compiler (for example, GCC, Clang, or MSVC).
- CMake 3.16 or newer.
- No machine-learning, plotting, or test-framework packages are downloaded by the build.

## Build and Test

Run these commands from the repository root:

```sh
cmake -S . -B cmake-build-vs -G "Visual Studio 18 2026" -A x64 -DBUILD_TESTING=ON -DML8_SVM_BUILD_EXAMPLES=ON
cmake --build cmake-build-vs --config Debug --parallel 1
ctest --test-dir cmake-build-vs -C Debug --output-on-failure
```

The test suite contains one executable for each major module and an end-to-end pipeline test. To build only the library, configure with `-DBUILD_TESTING=OFF -DML8_SVM_BUILD_EXAMPLES=OFF`.

To install the library and CMake package files into a local directory:

```sh
cmake --install build --prefix install
```

An installed project can be linked from CMake with:

```cmake
find_package(ML8_svm CONFIG REQUIRED)
target_link_libraries(my_program PRIVATE ML8_svm::ML8_svm)
```

## Basic Use

The scalers must be fitted on training data only. The test set is transformed with the training statistics so information from the test set does not enter training.

```cpp
#include <iostream>
#include <ML8_svm/ML8_svm.hpp>

int main() {
    using namespace ml8_svm;

    Dataset data = load_csv("data/input/iris_versicolor_virginica.csv");
    encode_binary_labels(data);
    impute_missing(data);
    validate(data);

    Split split = train_test_split(data, 0.2, 42);
    StandardScaler scaler;
    Matrix X_train = scaler.fit_transform(split.train.X);
    Matrix X_test = scaler.transform(split.test.X);

    OptimizerConfig config;
    config.learning_rate = 0.1;
    config.epochs = 500;
    config.batch_size = 16;
    config.tol = 1e-6;
    config.decay = true;
    config.seed = 42;

    LinearSVM model(0.01, config);
    model.fit(X_train, split.train.y);

    const std::vector<int> predictions = model.predict(X_test);
    std::cout << classification_report(split.test.y, predictions);
}
```

## Examples

Build examples with the default CMake option, then run them from the repository root so the default data paths resolve.

- `example1_load_csv` reads a CSV and prints a data summary.
- `example2_scaling` demonstrates feature scaling.
- `example3_margin` prints scores, distances, and margins for hand-calculated points.
- `example4_train_predict` trains on a CSV file and predicts held-out samples.
- `example5_full_pipeline` runs the full pipeline, reports metrics, and writes `data/output/predictions.csv`.
- `example6_loss_curve` prints the optimizer's loss after each epoch.
- `example7_support_vectors` lists identified support vectors.
- `lambda_sweep` compares several regularization strengths and writes `data/output/lambda_sweep.csv`.

For example, on Linux or MinGW:

```sh
./build/example5_full_pipeline
./build/example7_support_vectors data/input/iris_versicolor_virginica.csv
```

For a multi-configuration Visual Studio build, run the executables from `build/Release/` instead.

## Data

`linear_separable.csv` is a generated 200-row, two-feature dataset with balanced classes. It is intended for quick tests and examples. `iris_versicolor_virginica.csv` contains 100 rows from Fisher's Iris dataset, limited to the versicolor and virginica classes and four numeric measurements. The input README describes each file and the CSV format accepted by the loader.

The full pipeline writes one row per held-out sample to `data/output/predictions.csv`. The lambda-sweep example writes its experiment results to `data/output/lambda_sweep.csv`.

The reports folder contains the compiled and per-member weekly reports, final report, AI-use declaration, design figures, and Week 3 class-layout JPGs. Week 4 reports are finalized from repository evidence available on 24 October 2026; they report module and project status without inventing unrecorded personal contributions or AI-use details. The final presentation is `presentation/ML8_svm_Final_Presentation.pptx`.

## Limitations

- The implementation supports binary classification with a linear decision boundary. It does not include kernels or multiclass classification.
- Input features must be numeric. The CSV loader does not support text fields or quoted fields containing the delimiter.
- Missing feature values are represented as NaN and must be imputed before scaling and model fitting.
- The optimizer uses gradient updates and may need different learning rates, epoch counts, batch sizes, and regularization values for other datasets.
- The package does not promise the same accuracy on every dataset; evaluate it with held-out samples.

## Group Contributions

The project objectives assign work by module:

| Member | Main area |
|---|---|
| Abiyo Bruce | Dataset loading and input data |
| Bulukwa Jeremiah | Data preprocessing |
| Kainamatsiko Faith | Feature scaling and build integration |
| Tendo Martha Nassanga | Hyperplane geometry and margins |
| Asiimwe Roland | Hinge loss |
| Katende Joseph Travor | Core types, linear algebra, and regularization |
| Ssekindi Mercellinous | Gradient-based optimization |
| Ndagire Majorine | Support vectors and submission documentation |
| Ankunda Liz | Decision function and binary classification |
| Sserunjogi Jesse Ssemakula | Evaluation metrics and end-to-end pipeline |

## Collaboration and AI Use

The work was divided into modules with shared public interfaces. Members developed and reviewed changes through Git branches and pull requests, then integrated the modules into a single CMake project. Seeded data splitting and optimizer settings make the examples and tests repeatable.

AI tools were used as supporting aids for planning, code drafts, debugging, test ideas, and documentation. Contributors remain responsible for checking and understanding the code they submit. The reports directory contains the weekly records and the final AI-use declaration.

Weekly summaries are named with their reporting week and compiler, and per-member reports are stored under `reports/week_01/` through `reports/week_04/` with the member name in each filename. Where an individual report or historical AI-use detail was unavailable, the project records that gap explicitly rather than inventing a contributor statement. See `reports/README.md` for the report index and `reports/ai-use-declaration.md` for the consolidated disclosure.

## License

This project is distributed under the MIT License. See [LICENSE](LICENSE).
