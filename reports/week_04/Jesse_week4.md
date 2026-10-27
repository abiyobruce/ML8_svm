# Week 4 Final Module Report: Sserunjogi Jesse Ssemakula

**Assigned area:** Evaluation metrics and end-to-end pipeline  

## Final module status

Confusion-matrix counts and accuracy, precision, recall, F1, and classification reporting are implemented in `src/metrics.cpp`. The metric and pipeline tests, plus all examples, passed. The final outputs include `data/output/predictions.csv` and `data/output/lambda_sweep.csv`. The Iris run recorded 0.9231 test accuracy and 0.9300 five-fold accuracy; the synthetic run recorded 1.0000 for both.

The project-level integration check compiled and linked all 12 library sources, 13 test programs, and eight examples with Clang. All 13 test programs and all eight examples ran successfully. This verifies the module as part of the integrated repository; it does not claim that the named member personally performed that integration pass.

## Submission hand-off

The module files and test are included in the project. The overall project still needs a CMake/CTest run from a supported generator/toolchain because this machine lacks a working build generator. See the final report and README for the exact commands and verification limitation.
