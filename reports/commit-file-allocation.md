# Commit File Allocation Checklist

This checklist maps the project files to the ten module assignments in the project allocation. Paths are relative to the repository root. It is an ownership guide for organizing commits, not proof of who authored every historical change. Each member should commit their own changes and only claim work they actually completed. Shared build, integration, and submission files are listed separately.

## Bruce (M1) — CSV dataset loading and input data

**Directories:** `include/ML8_svm/`, `src/`, `tests/`, `examples/`, `data/input/`, `reports/week_01/` through `reports/week_04/`.

- `include/ML8_svm/dataset.hpp`
- `src/dataset.cpp`
- `tests/test_dataset.cpp`
- `examples/example1_load_csv.cpp`
- `data/input/README.md`
- `data/input/linear_separable.csv`
- `data/input/iris_versicolor_virginica.csv`
- Reports: `reports/week_01/Bruce_week1.md`, `reports/week_02/Bruce_week2.md`, `reports/week_03/Bruce_week3.md`, `reports/week_04/Bruce_week4.md`

## Jeremiah (M2) — preprocessing

**Directories:** `include/ML8_svm/`, `src/`, `tests/`, `reports/week_01/` through `reports/week_04/`.

- `include/ML8_svm/preprocessing.hpp`
- `src/preprocessing.cpp`
- `tests/test_preprocessing.cpp`
- Reports: `reports/week_01/Jeremiah_week1.md`, `reports/week_02/Jeremiah_week2.md`, `reports/week_03/Jeremiah_week3.md`, `reports/week_04/Jeremiah_week4.md`

## Faith (M3) — feature scaling and build integration

**Directories:** `include/ML8_svm/`, `src/`, `tests/`, `examples/`, `cmake/`, `reports/week_01/` through `reports/week_04/`.

- `include/ML8_svm/scaler.hpp`
- `src/scaler.cpp`
- `tests/test_scaler.cpp`
- `examples/example2_scaling.cpp`
- Shared build files coordinated in this module: `CMakeLists.txt`, `tests/CMakeLists.txt`, `cmake/ML8_svmConfig.cmake.in`
- Reports: `reports/week_01/Faith_week1.md`, `reports/week_02/Faith_week2.md`, `reports/week_03/Faith_week3.md`, `reports/week_04/Faith_week4.md`

## Martha (M4) — hyperplane geometry and margins

**Directories:** `include/ML8_svm/`, `src/`, `tests/`, `examples/`, `reports/figures/`, `reports/week_01/` through `reports/week_04/`.

- `include/ML8_svm/hyperplane.hpp`
- `src/hyperplane.cpp`
- `tests/test_hyperplane.cpp`
- `examples/example3_margin.cpp`
- `reports/figures/margin_geometry.svg`
- Reports: `reports/week_01/Martha_week1.md`, `reports/week_02/Martha_week2.md`, `reports/week_03/Martha_week3.md`, `reports/week_04/Martha_week4.md`

## Roland (M5) — hinge loss

**Directories:** `include/ML8_svm/`, `src/`, `tests/`, `reports/week_01/` through `reports/week_04/`.

- `include/ML8_svm/hinge_loss.hpp`
- `src/hinge_loss.cpp`
- `tests/test_hinge_loss.cpp`
- Reports: `reports/week_01/roland_week1.md`, `reports/week_02/Roland_week2.md`, `reports/week_03/Roland_week3_status.md`, `reports/week_04/Roland_week4.md`

## Travor (M6; also written Trevor) — core types, linear algebra, regularization

**Directories:** `include/ML8_svm/`, `src/`, `tests/`, `examples/`, `data/output/`, `reports/week_01/` through `reports/week_04/`.

- `include/ML8_svm/types.hpp`
- `include/ML8_svm/errors.hpp`
- `include/ML8_svm/linalg.hpp`
- `src/linalg.cpp`
- `include/ML8_svm/regularization.hpp`
- `src/regularization.cpp`
- `tests/test_linalg.cpp`
- `tests/test_regularization.cpp`
- `examples/lambda_sweep.cpp`
- `data/output/lambda_sweep.csv`
- Reports: `reports/week_01/travor_week1.md`, `reports/week_02/Travor_week2_report.md`, `reports/week_03/travor_week3_report.md`, `reports/week_04/Travor_week4.md`

## Mercellinous (M7) — gradient-based optimization

**Directories:** `include/ML8_svm/`, `src/`, `tests/`, `examples/`, `reports/figures/`, `reports/week_01/` through `reports/week_04/`.

- `include/ML8_svm/optimizer.hpp`
- `src/optimizer.cpp`
- `tests/test_optimizer.cpp`
- `examples/example6_loss_curve.cpp`
- `reports/figures/M7_optimizer_loss_curve.html`
- Reports: `reports/week_01/mercellinous_week1.md`, `reports/week_02/Mercellinous_week2_status.md`, `reports/week_03/Mercellinous_week3.md`, `reports/week_04/Mercellinous_week4.md`

## Majorine (M8) — support vectors and documentation

**Directories:** `include/ML8_svm/`, `src/`, `tests/`, `examples/`, `reports/`, `presentation/`.

- `include/ML8_svm/support_vectors.hpp`
- `src/support_vectors.cpp`
- `include/ML8_svm/ML8_svm.hpp` (public umbrella header)
- `tests/test_support_vectors.cpp`
- `examples/example7_support_vectors.cpp`
- `README.md`
- `reports/README.md`
- `reports/commit-file-allocation.md`
- `reports/final-report.md`
- `reports/ai-use-declaration.md`
- Compiled weekly summaries: `reports/week-01_Majorine.md`, `reports/week-02_Majorine.md`, `reports/week-03_Majorine.md`, `reports/week-04_Majorine.md`
- Week 3 class-layout figures: `reports/week_03/class_layouts/scaler_hierarchy.jpg`, `reports/week_03/class_layouts/linear_svm_encapsulation.jpg`
- Final presentation coordinated with the team: `presentation/ML8_svm_Final_Presentation.pptx`
- Reports: `reports/week_01/Majorine_Week1.md`, `reports/week_02/Majorine_week2.md`, `reports/week_03/Majorine_week-03.md`, `reports/week_04/Majorine_week4.md`

## Liz (M9) — decision function and binary classification

**Directories:** `include/ML8_svm/`, `src/`, `tests/`, `examples/`, `reports/week_01/` through `reports/week_04/`.

- `include/ML8_svm/decision.hpp`
- `src/decision.cpp`
- `include/ML8_svm/linear_svm.hpp`
- `src/linear_svm.cpp`
- `tests/test_decision.cpp`
- `tests/test_linear_svm.cpp`
- `examples/example4_train_predict.cpp`
- Reports: `reports/week_01/Ankunda_Liz_week1.md`, `reports/week_02/Ankunda_Liz_week2.md`, `reports/week_03/Liz_week3_status.md`, `reports/week_04/Liz_week4.md`

## Jesse (M10) — evaluation metrics and end-to-end pipeline

**Directories:** `include/ML8_svm/`, `src/`, `tests/`, `examples/`, `data/output/`, `reports/week_01/` through `reports/week_04/`.

- `include/ML8_svm/metrics.hpp`
- `src/metrics.cpp`
- `tests/test_metrics.cpp`
- `tests/test_pipeline.cpp`
- `examples/example5_full_pipeline.cpp`
- `data/output/predictions.csv`
- Reports: `reports/week_01/sserunjogi_jesse_ssemakula_week_01.md`, `reports/week_02/Sserunjogi_week2.md`, `reports/week_03/Jesse_week3.md`, `reports/week_04/Jesse_week4.md`

## Shared project files

These support the whole team and should be included by whoever prepares the integration/submission commit. They are not assigned exclusively to one module:

- `.gitignore`
- `LICENSE`
- `tests/test_utils.hpp` (shared test helper)
- `data/output/.gitkeep` (keeps the output directory in Git)

Majorine maintains `reports/README.md` and coordinates the presentation; the presentation should receive a team review before submission.

## Directories to include

Commit the project directories and their required files: `cmake/`, `data/input/`, `data/output/`, `examples/`, `include/ML8_svm/`, `presentation/`, `reports/` (including all four week folders and figures), `src/`, and `tests/`. Do not commit generated build folders such as `build/` or `cmake-build-*`; `.gitignore` excludes them.

Before each member commits, check `git status --short`, stage only their files plus any explicitly agreed shared files, and confirm the resulting commit contains no unrelated generated build output.
