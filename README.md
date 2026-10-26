<<<<<<< HEAD
# ML8_svm

A Support Vector Machine (SVM) for binary classification, written in C++17 from scratch without external machine learning libraries. Developed by Group 16.

## Features

* Data handling: Dataset loading and CSV handling; preprocessing, including binary label encoding, missing-value handling, and train-test splitting; feature scaling with `StandardScaler` and `MinMaxScaler`.
* Model: Hyperplane representation, distance and margin computation, hinge loss and subgradient, regularization, gradient-based optimization, training history, loss curves, support-vector identification, and binary classification using the `LinearSVM` class.
* Evaluation: Model evaluation metrics and end-to-end pipeline testing.
* Library support: Core types, error handling, linear algebra helpers, CMake build configuration, CTest tests, installation rules, and exported targets.

## Modules

Public headers are located in `include/ML8_svm/`, and implementations are located in `src/`.

* Dataset (`dataset.hpp`, `dataset.cpp`): Loads datasets and CSV files and stores features and labels.
* Feature scaling (`scaler.hpp`, `scaler.cpp`): Provides `StandardScaler` and `MinMaxScaler`.
* Linear algebra (`linalg.cpp`): Provides basic mathematical operations used by the SVM.
* Hinge loss (`hinge_loss.hpp`, `hinge_loss.cpp`): Implements hinge loss and its subgradient.
* Regularization (`regularization.hpp`, `regularization.cpp`): Helps control model complexity during training.
* Optimization (`optimizer.hpp`, `optimizer.cpp`): Handles parameter optimization and training history.
* Linear SVM (`linear_svm.hpp` or `Linear_svm.hpp`, `Linear_svm.cpp`): Implements the linear SVM classifier. Confirm the exact header filename in your repository.
* Decision function (`Decision.hpp`, `Decision.cpp`): Calculates decision scores and binary predictions.
* Evaluation metrics (`metrics.hpp`, `metrics.cpp`): Provides classification performance metrics.
* Error handling (`errors.hpp`): Defines error-handling facilities for invalid arguments, dimension mismatches, file errors, and other errors.
* Core types (`types.hpp`): Contains shared type definitions.

## Requirements

* A C++17-compatible compiler, such as GCC, Clang, or MSVC.
* CMake 3.16 or newer.
* Git.

No external machine learning libraries are required.

## Project Structure

ML8_svm/
├── include/
│   └── ML8_svm/       Public header files
├── src/               Implementation files
├── tests/             Test programs and test configuration
├── data/
│   ├── input/         Input data
│   └── output/        Output data
├── reports/           Weekly and final project reports
├── CMakeLists.txt     Main CMake configuration
├── LICENSE            Project license
└── README.md          Project documentation


Confirm that the directories shown above exist in your repository before keeping them in this structure.

## Building

Run these commands from the project root:

bash
cmake -S . -B build
cmake --build build --config Release


## Running the Tests

Run the following command to execute the registered tests:

bash
ctest --test-dir build -C Release --output-on-failure


The project includes tests for the following modules, provided the corresponding test files exist and are registered in `tests/CMakeLists.txt`:

* Dataset: Dataset loading and handling.
* Hinge loss: Hinge loss calculations.
* Metrics: Classification evaluation functions.
* Optimizer: Optimization module.
* Scaler:Feature scaling.
* Decision function: Decision scores and predictions.
* Linear SVM: Classifier training and prediction.

`tests/test_utils.hpp` provides helper functions shared by tests, if present.

Tests that use relative input-data paths should be run from the project root or configured with the appropriate working directory.

To run only the scaler test, if it is registered under the name `test_scaler`, use:
bash
ctest --test-dir build -C Release -R test_scaler --output-on-failure


The name after `-R` must match the registered CTest test name.

## Installing

Run the following commands from the project root:
bash
cmake -S . -B build
cmake --build build --config Release
cmake --install build --config Release --prefix install


The installation directory should contain the compiled library and public headers if installation completes successfully. Check the command output to confirm which files were installed.

## Using the Library in Another CMake Project

Place the ML8_svm repository inside your other project's directory. Then add the following to the other project's `CMakeLists.txt`:

cmake
add_subdirectory(ML8_svm)
target_link_libraries(my_program PRIVATE ML8_svm::ML8_svm)


Replace `my_program` with the name of your executable target.

This method uses the ML8_svm source directory directly.

## CMake Options

`ML8_SVM_BUILD_TESTS` is enabled by default. To build the library without tests, use:

bash
cmake -S . -B build -DML8_SVM_BUILD_TESTS=OFF


For single-configuration generators, the project defaults to the Release build type if none is specified. For multi-configuration generators, such as Visual Studio, select the configuration when building.

## Troubleshooting

* File-name capitalization: File names are case-sensitive on Linux and macOS. Ensure that the names in `CMakeLists.txt` match the actual files.
* Source file not compiled: Add the source file to `add_library(ML8_svm ...)` in the root `CMakeLists.txt`.
* Test not running: Ensure that the test executable is defined in `tests/CMakeLists.txt` and registered using `add_test()`.
* CTest finds no tests: Check that tests are enabled, configure and build the project, and run CTest from the project root.
* Generated folders appearing in Git:add generated directories such as `build/` and `Testing/` to `.gitignore`.

## Contributors

* Bruce: Dataset loading, CSV handling, input dataset documentation, and data preprocessing, including binary label encoding, missing-value handling, and train-test splitting.
* Faith: Feature scaling, CMake build system, test configuration, integration, installation and export rules, and clean-environment build testing.
* Martha: Hyperplane representation, distances, and margin computation.
* Roland: Hinge loss and subgradient calculation.
* Travor: Regularization, core types, error handling, and linear algebra.
* Mercellinous: Gradient-based optimization, training history, and loss curves.
* Majorine: Support-vector identification, umbrella header, documentation, report organization, and submission package.
* Liz: Decision function, binary classification, and the `LinearSVM` class.
* Jesse: Evaluation metrics, end-to-end pipeline testing, and evaluation results.

Weekly and final project reports are stored in the `reports/` directory.

## License

This project is released under the terms of the license provided in the [LICENSE](LICENSE) file.
=======
# Machine_Learning_8_-Support-Vector-Machine-for-binary-classification-
Project work for the members of Group 16
A reusable C++ library that trains and evaluates a linear Support Vector Machine (SVM) for binary classification, written from scratch with no machine-learning dependencies. 
The project was built by a group of 10 students as a C++ group project, taking scikit-learn as inspiration for the overall workflow.

## Project Name and Description
**ML8_svm** (namespace `ml8_svm`) is a library, not a stand-alone program. It covers the full classification pipeline: load a CSV file, preprocess it, scale the features, fit a linear SVM by gradient descent on the regularised hinge loss, predict, and evaluate. Labels are encoded as -1 / +1 and the model minimises

J(w, b) = (lambda / 2) * ||w||^2 + (1 / n) * sum_i max(0, 1 - y_i (w . x_i + b))

A prediction is the sign of the decision function w . x + b, and the margin width is 2 / ||w||.

## Project Objectives
- Design and implement a clear, reusable C++ library with a public API in `include/` and implementation in `src/`.
- Implement a linear SVM from first principles, with every component in its own module.
- Handle invalid input with a consistent exception hierarchy.
- Test each module with unit tests and an end-to-end pipeline test, runnable from a clean environment through CTest.
- Collaborate with Git and GitHub using feature branches, pull requests and code review.
- Document the library, report progress weekly, and declare all AI use.

## Main Features
- CSV dataset loading with clear errors for missing files, ragged rows and non-numeric fields.
- Preprocessing: label encoding to {-1, +1}, missing-value imputation, seeded shuffling, stratified train/test split and dataset validation.
- Feature scaling with `StandardScaler` and `MinMaxScaler` (fit on training data only).
- Hyperplane geometry: score, distance to the plane, functional and geometric margins, margin width.
- Hinge loss and its subgradient, L2 regularisation and the full objective.
- Gradient-based optimisation: batch gradient descent, SGD, mini-batch, learning-rate decay, early stopping, reproducible with a seed.
- Support vector identification.
- The `LinearSVM` class with `fit`, `predict`, `decision_function`, `hyperplane()`, `history()` and `support_vector_indices()`.
- Evaluation metrics: confusion matrix, accuracy, precision, recall, F1 and a classification report.

## Project Structure

## Requirements and Dependencies

## Installation and Build Instructions

## How to Use the Library

## Examples

## How to Run the Tests

## Limitations

## Contributions by Group Members
Member M6 - KATENDE JOSEPH TRAVOR
My name is Katende Joseph Travor, and I was in charge of setting up the mentioned modules;
- types
- errors
- linalg
- regularization. 
I also did their tests, as well as the lambda sweep file

## How We Collaborated
>>>>>>> origin/main
