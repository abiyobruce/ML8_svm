# Week 4 Final Project Status Report

**Compiled by:** Ndagire Majorine
**Evidence cutoff:** Integrated repository state and direct Clang verification available on 24 October 2026

## Project completion status

The project now includes the C++17 linear SVM library, public headers, build/package configuration, 13 test programs, eight examples, two datasets, prediction and lambda-sweep outputs, user documentation, final report, AI-use declaration, individual reports, class-layout figures, and final presentation.

All 12 implementation sources compiled and linked into the library with Clang. All 13 test programs and eight examples compiled, linked, and ran successfully. The pipeline was run on both bundled datasets.

## Module status

| Member | Area | Final repository evidence |
|---|---|---|
| Bruce (M1) | CSV loading and input data | Loader, input descriptions, CSV example, dataset tests |
| Jeremiah (M2) | Preprocessing | Encoding, imputation, validation, seeded shuffle and stratified split; preprocessing tests |
| Faith (M3) | Scaling and build integration | Abstract scaler API, standard/min-max implementations, polymorphic use, scaler tests |
| Martha (M4) | Hyperplane geometry | Scores, signed distances, margins, margin width and zero-weight handling |
| Roland (M5) | Hinge loss | Mean loss, subgradient, kink behavior, hand-checked and numerical-gradient tests |
| Travor (M6) | Core types and regularization | Linear algebra, regularized objective and gradient, lambda sweep and output |
| Mercellinous (M7) | Gradient optimization | Batch, stochastic and mini-batch updates; loss-curve example and report |
| Majorine (M8) | Support vectors and documentation | Support-vector API/example, README, final report, diagrams and presentation |
| Liz (M9) | Decision and binary classification | Decision score and `LinearSVM` fit/predict API with tests |
| Jesse (M10) | Evaluation and pipeline | Confusion matrix and metrics, full pipeline, generated predictions |

Each individual Week 4 file records the module's final repository status and project-level verification. Member-specific Week 4 activity and AI-use details were not recorded, so the reports do not invent personal contributions or AI disclosures. The project-wide declaration contains known historical disclosures and identifies remaining gaps.

## Measured results

- The synthetic dataset run recorded 1.0000 test accuracy and 1.0000 five-fold accuracy.
- The two-class Iris run recorded 0.9231 test accuracy and 0.9300 five-fold accuracy. The unscaled test run recorded 0.5385 accuracy.
- The 11-row regularization sweep is saved in `data/output/lambda_sweep.csv`; held-out pipeline predictions are in `data/output/predictions.csv`.
- The M7 toy loss-curve run decreased from `0.550675` to `0.097213` in 50 epochs and reached the configured epoch limit without reporting convergence.

## Build and comparison status

The CMake files were reviewed for target/source consistency, C++17 requirements, CTest registration, installation/export setup, and example target paths; no obvious missing target or source reference was found. A CMake-generated build and CTest run could not be performed on this host: NMake and Ninja were unavailable, and the available MinGW tools failed to start. Direct Clang compilation and runtime checks passed, but do not substitute for a clean CMake/CTest run on the submission machine.

The planned scikit-learn comparison was not completed because scikit-learn was unavailable in the local Python environment. No comparison result is claimed. These two checks remain visible in the final report and should be completed if the instructor requires them.

## Submission contents

The package includes the top-level `README.md`, `CMakeLists.txt`, `cmake/ML8_svmConfig.cmake.in`, source and public-header trees, tests, examples, input data, generated experiment outputs, weekly and final reports, AI-use declaration, figures, Week 3 class-layout JPGs, and `presentation/ML8_svm_Final_Presentation.pptx`.

## AI-use record

ChatGPT assisted with project review, beginner-level code and documentation improvements, direct integration verification, and preparation of submission materials. Historical AI use is summarized in `reports/ai-use-declaration.md`; missing member-specific details remain marked unrecorded rather than guessed.
