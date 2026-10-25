# AI Use Declaration

## Project: ML8_svm - M7 Gradient-Based Optimization

ChatGPT was used as an AI assistance tool during the development and documentation of the M7 gradient-based optimizer.

AI assistance was used to help explain optimizer configuration settings, troubleshoot build and testing issues, improve technical documentation, organize optimization results, and provide guidance on Git commands and version control.

The project was built locally using CMake, and the test suite was run to verify the changes. Both `scaler_test` and `optimizer_test` passed. The loss-curve example was also executed locally, and its output was used to document the observed loss reduction.

The project contributor remains responsible for reviewing the implementation, checking the accuracy of the reported results, understanding the submitted work, and ensuring that AI assistance complies with the group's academic and project requirements.

AI assistance was used as a support tool rather than as a substitute for local building, testing, and verification.



## Project: ML8_svm - M6 Regularization and Core Layer (Travor)

Claude (Anthropic) was used as an AI assistance tool while developing and documenting the M6 modules: `types.hpp`, `errors.hpp`, `linalg`, `regularization`, their tests and the lambda sweep.

AI assistance was used to:
- draft starter code and explanatory comments for the core types, error classes, linear-algebra helpers and the regularization functions;
- draft the unit tests in `test_linalg.cpp` and `test_regularization.cpp`, and adapt them to the shared `tests_utils.hpp` helper;
- draft the lambda-sweep program (`examples/lambda_sweep.cpp`) and run it on the merged code to produce `data/output/lambda_sweep.csv`;
- review the repository for build and test problems, such as tests that were not registered with CTest;
- draft the weekly report lines and the final-report sections for Regularization and Core Types and Error Handling.

The code was built with CMake and the test suite was run to verify it. The report numbers were checked against `lambda_sweep.csv`. I reviewed the AI-assisted text and code, rewrote the report sections in my own words, and can explain and defend my own modules. The README contribution lines were typed by hand.

AI assistance was used as a support tool rather than as a substitute for building, testing and understanding the work.
