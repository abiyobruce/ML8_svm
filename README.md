# ML8_svm

A Support Vector Machine (SVM) for binary classification, written in C++17 from scratch with no external machine learning libraries.

This project was developed by Group 16.

## Features

### Data Handling

- Dataset loading and CSV handling.
- Data preprocessing, including binary label encoding, missing-value handling, and train-test splitting.
- Feature scaling using `StandardScaler` and `MinMaxScaler`.

### Model

- Hyperplane representation, distance, and margin computation.
- Hinge loss and subgradient calculation.
- Regularization.
- Gradient-based optimization with training history and loss curves.
- Support-vector identification.
- Decision function and binary classification through the `LinearSVM` class.

### Evaluation

- Model evaluation metrics.
- End-to-end pipeline testing.

### Library Support

- Core types, error handling, and linear algebra helpers.
- CMake build system with CTest tests, installation rules, and exported targets.

## Modules

The public header files are located in `include/ML8_svm/`, while the implementation files are located in `src/`.

### Dataset

The dataset module loads and handles datasets, including reading CSV files and storing feature and label information.

Files:
- `dataset.hpp`
- `dataset.cpp`

### Feature Scaling

The scaling module provides `StandardScaler` and `MinMaxScaler` for scaling dataset features.

Files:
- `scaler.hpp`
- `scaler.cpp`

### Linear Algebra

The linear algebra module provides basic mathematical operations used by the SVM implementation.

File:
- `linalg.cpp`

### Hinge Loss

The hinge loss module calculates the hinge loss used during SVM training and supports subgradient calculation.

Files:
- `hinge_loss.hpp`
- `hinge_loss.cpp`

### Regularization

The regularization module provides regularization calculations used to control model complexity during training.

Files:
- `regularization.hpp`
- `regularization.cpp`

### Optimization

The optimization module handles model parameter optimization and training history.

Files:
- `optimizer.hpp`
- `optimizer.cpp`

### Linear SVM

The Linear SVM module implements the linear support vector machine classifier.

Files:
- `Linear_svm.hpp`
- `Linear_svm.cpp`

### Decision Function

The decision module calculates decision scores and produces predictions for binary classification.

Files:
- `Decision.hpp`
- `Decision.cpp`

### Evaluation Metrics

The metrics module provides functions for evaluating classification performance.

Files:
- `metrics.hpp`
- `metrics.cpp`

### Error Handling

The error-handling module defines exceptions used to report invalid arguments, dimension mismatches, file errors, and other problems.

File:
- `errors.hpp`

### Core Types

The core types module contains shared type definitions used throughout the project.

File:
- `types.hpp`

## Requirements

To build the project, you need:

- A C++17-compatible compiler, such as GCC, Clang, or MSVC.
- CMake version 3.16 or newer.
- Git.

The project does not require external machine learning libraries.

## Project Structure

The project is organized as follows:

```text
ML8_svm/
├── include/ML8_svm/    Public header files
├── src/                Implementation files
├── tests/              Test programs and test configuration
├── data/
│   ├── input/          Input data
│   └── output/         Output data
├── reports/            Weekly and final project reports
├── CMakeLists.txt      Main CMake configuration
├── LICENSE             Project license
└── README.md           Project documentation
```

## Building the Project

Open a terminal in the project root directory and configure the project:

```bash
cmake -S . -B build
```

Build the project in Release mode:

```bash
cmake --build build --config Release
```

These commands configure and compile the project using the available C++ compiler.

## Running the Tests

The project uses CTest to register and run its tests.

After building the project, run:

```bash
ctest --test-dir build -C Release --output-on-failure
```

The test programs cover the following areas:

### Dataset Tests

Source file: `tests/test_dataset.cpp`

These tests check dataset loading and handling.

### Hinge Loss Tests

Source file: `tests/test_hinge_loss.cpp`

These tests check hinge loss calculations.

### Evaluation Metrics Tests

Source file: `tests/test_metrics.cpp`

These tests check the classification evaluation functions.

### Optimization Tests

Source file: `tests/test_optimizer.cpp`

These tests check the optimization module.

### Feature Scaling Tests

Source file: `tests/test_scaler.cpp`

These tests check feature scaling functionality.

### Decision Function Tests

The decision function tests check decision scores and binary classification predictions.

### Linear SVM Tests

The Linear SVM tests check the classifier's training and prediction functionality.

The shared header `tests/test_utils.hpp` provides helper functions used by the test programs.

Tests that use relative paths to access input data should be run from the project root directory.

### Running a Single Test

To run only the feature scaling test, use:

```bash
ctest --test-dir build -C Release -R test_scaler --output-on-failure
```

The test must be registered in `tests/CMakeLists.txt` for CTest to find it.

## Installing the Library

Build the project and install it into a local `install` directory:

```bash
cmake -S . -B build
cmake --build build --config Release
cmake --install build --config Release --prefix install
```

The installation directory contains the compiled library and the public headers.

## Using the Library in Another CMake Project

The library can be included as a subdirectory in another CMake project.

For example, if the ML8_svm repository is located inside the other project's directory, add the following to the other project's `CMakeLists.txt`:

```cmake
add_subdirectory(ML8_svm)

target_link_libraries(my_program PRIVATE ML8_svm::ML8_svm)
```

Replace `my_program` with the name of your executable target.

## CMake Options

The project provides an option for controlling whether tests are built.

### Building Without Tests

The `ML8_SVM_BUILD_TESTS` option is enabled by default.

To configure the project without building tests, use:

```bash
cmake -S . -B build -DML8_SVM_BUILD_TESTS=OFF
```

When a single-configuration generator is used and no build type is specified, the project defaults to Release mode. With a multi-configuration generator, such as Visual Studio, select the desired configuration when building.

## Troubleshooting

### File Names and Capitalization

File names may be case-sensitive on Linux and macOS. Make sure source file names match the names listed in `CMakeLists.txt`.

### A New Source File Is Not Compiled

Add the source file to the `add_library(ML8_svm ...)` section of the root `CMakeLists.txt`.

### A New Test Is Not Run

Make sure the test executable is defined and registered in `tests/CMakeLists.txt` using `add_test()`.

### CTest Reports That No Tests Were Found

Build the project first and check that testing is enabled and that the tests are registered correctly.

For a multi-configuration build, use the appropriate configuration when running CTest.

### Generated Folders Appear in Git

Folders such as `build/` and `Testing/` are generated during building and testing. They should be listed in `.gitignore` so that generated files are not accidentally committed.

## Contributors

### Bruce

Bruce contributed to dataset loading and CSV handling. His work includes reading datasets, handling input data, and documenting the input datasets and project data structure.

Bruce also contributed to data preprocessing, including binary label encoding, missing-value handling, and train-test splitting.

### Faith

Faith contributed to feature scaling using `StandardScaler` and `MinMaxScaler`.

Her responsibilities also include the CMake build system, test configuration, project integration, installation and export rules, and clean-environment build testing.

### Martha

Martha contributed to hyperplane representation, distance calculations, and margin computation for the support vector machine.

### Roland

Roland contributed to the hinge loss module and subgradient calculation used during SVM training.

### Travor

Travor contributed to regularization, shared core types, error handling, and linear algebra operations used by the other modules.

### Mercellinous

Mercellinous contributed to gradient-based optimization, training history, and loss curves used to examine model training.

### Majorine

Majorine contributed to support-vector identification, the umbrella header, project documentation, report organization, and preparation of the submission package.

### Liz

Liz contributed to the decision function, binary classification, and the `LinearSVM` class used for model training and prediction.

### Jesse

Jesse contributed to model evaluation metrics, end-to-end pipeline testing, and the collection and reporting of evaluation results.

Weekly reports and the final report are available in the `reports/` directory.

## License

This project is released under the license provided in the [LICENSE](LICENSE) file.