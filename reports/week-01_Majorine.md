# Week 1 Progress Report

**Compiled by:** Ndagire Majorine  
**Project phase:** Design and skeleton

## Completed

- **M1 Bruce - Dataset loading:** declared the dataset and CSV-loading interface, added the two input datasets and their data notes, and prepared the loader test skeleton.
- **M2 Jeremiah - Preprocessing:** declared label encoding, missing-value imputation, seeded shuffle, validation, and train/test split; added the initial implementation and test skeleton.
- **M3 Faith - Feature scaling and integration:** added the scaler interface and initial build/test setup. The Git history attributes the scaler and CMake setup to Faith.
- **M4 Martha - Hyperplane geometry:** declared the hyperplane and margin functions, added a compiling stub and test skeleton, and wrote the margin derivation.
- **M5 Roland - Hinge loss:** declared the loss and subgradient functions, added their initial source and test files, and recorded the subgradient derivation.
- **M6 Trevor - Core types and regularization:** added `Vector` and `Matrix`, the shared exception hierarchy, linear-algebra helpers, and the regularization interface and stub.
- **M7 Mercellinous - Optimization:** declared optimizer settings and training history, and prepared the source and test scaffolding.
- **M8 Majorine - Support vectors and documentation:** declared support-vector identification, added the umbrella header, and started the README, report, and AI-use declaration structures.
- **M9 Liz - Decision and binary classification:** declared the decision functions and `LinearSVM` interface and added the initial source files.
- **M10 Jesse - Evaluation:** declared the confusion matrix and evaluation API and prepared the test skeleton and output directory.

## In Progress

- Members were checking their headers against the shared interface contract before the planned header freeze.
- The core headers and error types needed to be merged before dependent modules could be fully built and tested.
- The team was preparing unit-test cases for the implementation phase.

## Challenges and Blockers

- Several modules were still stubs and depended on interfaces owned by other members.
- M6's types and error classes were on the critical path for integrating the library.
- The individual reports do not fully identify AI use for every member. Jeremiah's, Jesse's, and Mercellinous's tool and purpose details are unrecorded, and Martha's note does not identify the tool.

## Next Week

- Implement the CSV loader, preprocessing functions, feature scalers, hyperplane calculations, hinge loss, regularization, optimizer, support-vector search, decision functions, and metrics.
- Add unit tests for normal and invalid inputs and register each test with CTest.
- Keep the implementation aligned with the interface contract and integrate modules as dependencies become available.

## AI Use

The available Week 1 notes record Claude (Anthropic) for several planning and starter-code tasks and ChatGPT (OpenAI) for hinge-loss support. Majorine's note records Claude assistance with the allocation and interface plan. Jeremiah's, Jesse's, and Mercellinous's tool and purpose details are unrecorded; Martha's note says AI assistance was used but does not identify the tool. These omissions are listed in `ai-use-declaration.md` rather than filled by inference.
