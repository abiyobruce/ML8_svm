# ML8_svm Final Report

**Project:** Linear Support Vector Machine for binary classification in C++17 (ML8_svm)
**Project group:** Group 16

## 1. Introduction and project structure

This project implements a reusable linear Support Vector Machine (SVM) library for binary classification. The goal was to make the mathematics and training process visible in ordinary C++ code, while still providing a practical pipeline for reading data, preprocessing features, training a model, making predictions, and measuring results. The implementation has no external machine-learning library dependency.

The decision score is `w . x + b`. Labels are represented as -1 and +1. Training minimizes the mean hinge loss plus an L2 penalty on the weights. The library is organized into public headers in `include/ML8_svm/`, implementations in `src/`, 13 focused test programs in `tests/`, eight runnable examples in `examples/`, two CSV datasets in `data/input/`, generated output in `data/output/`, and project reports and figures in `reports/`.

The public umbrella header is `<ML8_svm/ML8_svm.hpp>`. The top-level CMake project builds the library, test programs, examples, and installable CMake package. The README describes the public API, build commands, data, examples, and limitations.

## 2. Dataset loading and data description (Bruce)

`load_csv` reads numeric CSV data with an optional header, configurable delimiter, and selectable label column. It handles whitespace, blank lines, Windows line endings, a UTF-8 byte-order mark, quoted numeric fields, common numeric formats, and recognized missing-value markers in features. It reports malformed rows and labels through the library's exception types. Quoted fields containing the delimiter and text-valued columns are outside the supported format.

Two datasets are included:

| Dataset | Rows | Features | Labels | Use |
|---|---:|---:|---|---|
| `linear_separable.csv` | 200 | 2 | -1 and +1, balanced | Quick training and pipeline checks on separated Gaussian clusters |
| `iris_versicolor_virginica.csv` | 100 | 4 | versicolor and virginica | Small real-data binary classification example |

The input-data README records each dataset's provenance, columns, label format, and CSV limitations. The synthetic data is intentionally easy to separate; perfect accuracy on it is not evidence of general performance.

## 3. Preprocessing (Jeremiah)

The preprocessing module supports binary-label encoding, feature-wise mean imputation, seeded shuffling, data validation, and stratified train/test splitting. Validation checks that samples have consistent feature counts, that labels are valid, and that both classes are available where training requires them. The split keeps class proportions as similar as possible in the training and test portions and can be repeated with a fixed seed.

The end-to-end example fits the scaler only on training features, then applies those training statistics to the test features. The k-fold example repeats the same rule inside each fold, preventing the held-out fold from influencing its scaler.

## 4. Feature scaling and build integration (Faith)

`StandardScaler` stores per-feature means and population standard deviations. `MinMaxScaler` stores per-feature minima and maxima and maps values into a selected range. Both support inverse transformation and report whether they have been fitted. Constant features are handled without division by zero.

The classes implement a shared abstract `Scaler` interface. Code can call `fit_transform` or transform data through a base-class reference, while virtual functions select the derived scaler's calculations at runtime. This demonstrates inheritance and polymorphism in a useful API rather than in an unrelated example.

The CMake configuration declares C++17, builds all 12 implementation files into the library, registers the 13 tests with CTest, and builds seven teaching examples plus the lambda sweep. Installation exports the library and a `find_package(ML8_svm CONFIG)` package. The configuration is present, but a CMake-generated build could not be run on the verification host because it had no installed make/Ninja/Visual Studio build tool. Direct compilation and execution results are reported in Section 12.

## 5. Hyperplane geometry and margin (Martha)

For a hyperplane with weights `w` and bias `b`, the score is `w . x + b`. The boundary has score zero. The signed distance from a point to the boundary is `(w . x + b) / ||w||`; the functional margin is `y * score(x)` and the geometric margin is `y * score(x) / ||w||`. The two margin boundaries have scores +1 and -1, so their distance is `2 / ||w||`.

For the example `w = (3, 4)`, `b = -1`, and `x = (1, 1)`, the score is 6 and `||w|| = 5`. The point's signed distance is 1.2, and for label +1 its geometric margin is also 1.2. The margin width is 0.4. When `w` is zero, the score and functional margin remain defined, but distance-based operations reject division by zero with `InvalidArgument`.

The margin example prints scores and margins for hand-selected two-dimensional points. The report figure is [margin_geometry.svg](figures/margin_geometry.svg).

## 6. Hinge loss (Roland)

For `n` labelled samples, mean hinge loss is

```text
L(w, b) = (1 / n) * sum(max(0, 1 - y_i * (w . x_i + b)))
```

Samples with margin at least one contribute zero loss. Samples below the margin contribute their margin shortfall. For an active sample (`y_i * score(x_i) < 1`), its contribution to the weight subgradient is `-y_i * x_i / n` and to the bias subgradient is `-y_i / n`. At the hinge kink, the implementation selects the valid zero subgradient. Tests cover hand-computed values, invalid dimensions and labels, and a numerical gradient check.

## 7. Regularization and core types (Travor)

The objective is

```text
J(w, b) = L(w, b) + (lambda / 2) * ||w||^2
```

The corresponding weight gradient adds `lambda * w`; the bias is not regularized. The library's `Vector` and `Matrix` aliases and linear-algebra helpers are shared by the modules. A common exception hierarchy distinguishes invalid arguments, dimension mismatches, file errors, and model use before fitting.

The lambda sweep was run on the synthetic dataset with a fixed split and optimizer seed. All 11 settings in `data/output/lambda_sweep.csv` produced 1.0 training and test accuracy on this separable dataset. At lambda `0.0001`, the margin width was `2.6202` with 76 identified support vectors; at lambda `10`, it was `14.7797` with 160 support vectors. The objective increased from `0.0788` to `0.9084`. These observations describe this run only: changing lambda changes the weight scale and support-vector count, while the easy dataset remains perfectly classified.

## 8. Gradient-based optimization (Mercellinous)

`OptimizerConfig` holds the learning rate, maximum epoch count, batch size, stopping tolerance, optional learning-rate decay, and random seed. The optimizer supports full-batch, stochastic, and mini-batch updates. Each update combines the hinge-loss subgradient with the L2 weight gradient. Seeded shuffling makes repeated runs reproducible. `TrainingHistory` stores the loss per epoch, epoch count, and convergence status.

The existing loss-curve example report records a 50-epoch toy run in which loss decreased from `0.550675` to `0.097213`, approximately 82.3%. The run reached its epoch limit rather than reporting convergence. The small toy run illustrates optimizer behavior but does not establish generalization. The related figure is [M7_optimizer_loss_curve.html](figures/M7_optimizer_loss_curve.html); it is an approximate illustration of the trend, while the reported endpoint values came from program output.

## 9. Support vectors (Majorine)

The support-vector helper returns training-row indices whose signed functional margin is at most `1 + tolerance`. It checks label values, dimensions, empty inputs, and tolerance validity. `LinearSVM::support_vector_indices()` evaluates the model against the training data retained during fitting. The support-vector example reports the selected rows, margin width, and test accuracy.

## 10. Decision function and `LinearSVM` (Liz)

The decision module calculates scores for a single feature vector or a matrix of samples. A score of zero maps to +1; a negative score maps to -1. `LinearSVM` provides a small public workflow: configure, `fit`, then call `decision_function` or `predict`. It exposes read-only access to the learned hyperplane and training history. The model checks invalid configuration and data, and methods requiring a trained model throw `NotFitted`. A failed refit leaves an existing fitted model unchanged.

## 11. Evaluation and measured results (Jesse)

The metrics module calculates a binary confusion matrix, accuracy, precision, recall, F1, and a formatted classification report. The full-pipeline example uses seed 42 and lambda 0.01. It also runs five-fold accuracy with a scaler fitted independently inside each training fold.

| Dataset and run | Test samples | Accuracy | Precision | Recall | F1 | 5-fold accuracy |
|---|---:|---:|---:|---:|---:|---:|
| Synthetic, scaled | 50 | 1.0000 | 1.0000 | 1.0000 | 1.0000 | 1.0000 |
| Iris two-class, scaled | 26 | 0.9231 | 1.0000 | 0.8462 | 0.9167 | 0.9300 |

For the Iris test split, the confusion counts were TP=11, FN=2, FP=0, TN=13 (positive label is +1). The same training/test split without feature scaling gave accuracy `0.5385`, compared with `0.9231` after scaling. This is one seeded split and should not be interpreted as a general performance guarantee. The pipeline writes per-row truth, prediction, and score to `data/output/predictions.csv`; the lambda experiment is recorded in `data/output/lambda_sweep.csv`.

A scikit-learn comparison was planned in the objectives, but it is not reported as completed: scikit-learn was not installed in the available Python environment, and network access was unavailable for adding it. The C++ results above are measurements from the project implementation only.

## 12. Integration, verification, lessons, and limitations

The integrated sources were syntax-checked and compiled with Clang 23 targeting the available 32-bit MinGW environment. The 12 library source files were linked into a static library, then all 13 test executables and all eight example executables were linked. All 13 test programs and all eight examples ran successfully. The full pipeline was also run against both bundled datasets, and the predictions and lambda-sweep CSVs were generated.

The host could not perform the documented CMake/CTest workflow: CMake selected NMake, which was not installed; the available MinGW make/compiler programs failed to start with an operating-system DLL relocation error; and no Ninja or Visual Studio C++ build installation was present. Therefore, these results verify compilation, linking, tests, and examples through direct Clang commands, but do not verify CMake generation or CTest registration on this machine. A final clean CMake/CTest run should be made on a standard C++17/CMake environment before submission if that check is required by the instructor.

The project is binary-only and linear; it does not implement kernels or multiclass classification. It expects numeric features and does not parse quoted fields containing the CSV delimiter. Missing feature values must be imputed before scaling and training. Results depend on data, split, and hyperparameters. The synthetic dataset is easy and the Iris dataset is small, so broader validation would be needed for performance claims.

The work showed the value of shared interfaces and module tests: a scaler base class enabled runtime substitution, while dataset validation and clear errors made incorrect inputs easier to identify. Seeded randomness made examples repeatable. Results should be interpreted with their dataset and split stated, and build claims should distinguish direct compiler verification from CMake/CTest verification.

### 12.1 AI-use summary

Historical individual reports record use of Claude (Anthropic) and ChatGPT (OpenAI) for code drafts, test ideas, debugging, CMake assistance, and documentation. This final integration pass also used ChatGPT to inspect the repository, debug and refactor code, run the available compilation and runtime checks, and prepare documentation and diagrams. The project-wide declaration is in [ai-use-declaration.md](ai-use-declaration.md). Several historical entries do not identify the AI tool or purpose; those entries are marked unrecorded there instead of inferred.

## Appendix: demonstration sequence

From the project root, after configuring and building with a working C++17/CMake toolchain:

1. Run `example1_load_csv` to inspect a dataset.
2. Run `example2_scaling` and `example3_margin` to demonstrate scaling and margin geometry.
3. Run `example4_train_predict` to train and predict on held-out rows.
4. Run `example5_full_pipeline` to view metrics and generate `data/output/predictions.csv`.
5. Run `example6_loss_curve`, `example7_support_vectors`, and `lambda_sweep` to show training progress, support-vector identification, and the effect of lambda.
6. Run `ctest --test-dir build --output-on-failure` on a supported CMake generator.
