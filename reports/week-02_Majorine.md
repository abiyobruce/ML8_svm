# Week 2 Progress Report

**Compiled by:** Ngadire Majorine
**Project phase:** Implementation and unit tests

## Completed

- **M1 Bruce - Dataset loading:** implemented CSV parsing for headers, delimiters, selected label columns, missing feature values, quoted numeric fields, BOMs, whitespace, and common numeric formats; expanded loader tests and documented the bundled data.
- **M2 Jeremiah - Preprocessing:** implemented binary-label encoding, column-mean imputation, seeded shuffling, dataset validation, and stratified splitting. Tests cover normal and invalid inputs. The individual report left its pass count blank, so this summary does not claim a recorded test total.
- **M3 Faith - Feature scaling and integration:** added working standard and min-max scaling, including constant-feature handling, with build and test scaffolding in the repository.
- **M4 Martha - Hyperplane geometry:** implemented scores, signed distances, functional and geometric margins, and margin width; added hand-calculated and edge-case tests. Her report records the tests passing locally.
- **M5 Roland - Hinge loss:** implemented mean hinge loss and its subgradient, including a zero subgradient at the margin kink; added hand-checked and numerical-gradient tests.
- **M6 Trevor - Core types and regularization:** implemented L2 penalty, gradient, objective, and the shared linear-algebra functions; added tests for regularization and vector shapes.
- **M7 Mercellinous - Optimization:** the repository now contains batch, stochastic, and mini-batch updates, seeded sample ordering, learning-rate decay, and tolerance-based stopping. No Week 2 individual M7 report was found, so the feature status is based on the source present in the repository.
- **M8 Majorine - Support vectors and documentation:** implemented support-vector identification and its hand-checked tests; maintained the weekly documentation and AI-use declaration.
- **M9 Liz - Decision and binary classification:** implemented decision scores, label conversion, and `LinearSVM` training and prediction APIs; prepared unit tests. Her report said full training verification was waiting for the optimizer integration.
- **M10 Jesse - Evaluation:** implemented confusion-matrix counts and accuracy, precision, recall, F1, and classification-report output. The report records the metrics tests passing locally.

## In Progress

- Integration among the optimizer, `LinearSVM`, and end-to-end pipeline was still being completed.
- Members were checking test registration and exchanging code reviews as modules came together.
- Results and regression checks on the two-class Iris data were planned for Week 3.

## Challenges and Blockers

- The preprocessing report did not record a test pass count, and the M7 Week 2 individual report was absent. Mercellinous's Week 2 AI use is unrecorded.
- Liz reported that training verification depended on the optimizer being merged.
- The original test helper name was inconsistent across test files, and CTest registration still needed a project-wide check.

## Next Week

- Run the complete load-preprocess-scale-train-predict-evaluate pipeline on both datasets.
- Finish examples 1-7, cover edge cases, and add the pipeline test.
- Run the lambda sweep and save its results; record test and accuracy results in the final report.

## AI Use

The available Week 2 notes disclose Claude (Anthropic) for drafts, debugging, implementation, and test-case support across several modules and ChatGPT (OpenAI) for hinge-loss implementation and test support. Mercellinous's Week 2 AI-use details are unrecorded. The project-wide AI declaration lists the specific gaps without guessing.
