# Week 3 Progress Report

**Compiled by:** Ndagire Majorine 
**Project phase:** Integration, examples, and edge cases

## Completed

- **M1 Bruce - Dataset loading:** added loader edge-case handling and tests, and created the CSV summary example. The report notes include quoted numeric fields, scientific notation, tabs, CRLF, whitespace, and files without a final newline.
- **M2 Jeremiah - Preprocessing:** the implementation and tests are present in the repository. No individual Week 3 progress note was found.
- **M3 Faith - Feature scaling and integration:** Git history records scaler integration, zero-variance handling, and CMake changes. Direct end-to-end compilation and runtime checks were completed with Clang on 24 October; a CMake/CTest run remains unverified on this host.
- **M4 Martha - Hyperplane geometry:** extended edge-case tests and wrote the margin example, including the zero-weight case.
- **M5 Roland - Hinge loss:** the implementation and tests are present; no individual Week 3 report was found.
- **M6 Trevor - Core types and regularization:** added further edge-case tests and the lambda-sweep program. The individual report says the sweep output was saved.
- **M7 Mercellinous - Optimization:** Git history records the completed optimizer implementation and loss-curve example. The checked-in Week 3 report was empty and has been replaced with a status record; individual Week 3 AI-use detail is unrecorded.
- **M8 Majorine - Support vectors and documentation:** added the real-data support-vector example and drafted the final report and README.
- **M9 Liz - Decision and binary classification:** the API, implementation, and tests are present; no individual Week 3 progress note was found.
- **M10 Jesse - Evaluation:** added the pipeline test and full-pipeline example, including training-only scaling and prediction output. The Iris two-class run and measured metrics are now included in the final report.
- **Integration check (24 October):** compiled and linked the 12 library sources, 13 test programs, and eight examples with Clang; all test programs and examples ran successfully. The full pipeline was run on both bundled datasets, and the prediction and lambda-sweep CSVs were regenerated.
- **Week 3 class diagrams:** added JPG layouts for the scaler inheritance hierarchy and `LinearSVM` encapsulation in `week_03/class_layouts/`.

## Week 3 object-oriented implementation

- **Inheritance:** `StandardScaler` and `MinMaxScaler` publicly derive from the abstract `Scaler` interface and override its virtual scaling operations. `Scaler::fitted_` is protected; each derived scaler keeps its own statistics private.
- **Polymorphism:** callers and tests can use either derived scaler through a `Scaler&`. The shared `fit_transform` method calls virtual `fit` and `transform`, selecting the derived implementation at runtime.
- **Encapsulation:** `LinearSVM` exposes fitting, scoring, prediction, and read-only model access through public methods. Its lambda, optimizer settings, fitted flag, learned model/history, and training rows are private. It contains a `Hyperplane`; that is composition rather than inheritance.

The JPGs are included in [Majorine's individual Week 3 report](week_03/Majorine_week-03.md): `week_03/class_layouts/scaler_hierarchy.jpg` and `week_03/class_layouts/linear_svm_encapsulation.jpg`.

## In Progress

- Run the documented CMake/CTest workflow on a host with a working generator and C++17 toolchain.
- Complete the scikit-learn comparison planned in the project objectives when that package is available.
- Check the generated files from a clean CMake build directory on the target submission environment.

## Challenges and Blockers

- CMake/CTest could not be run on this host: NMake was missing, the available MinGW programs failed to start, and Ninja and Visual Studio C++ build tools were absent. Direct Clang compilation and runtime checks succeeded.
- The checked-in `data/output/predictions.csv` was malformed and contained shell instructions; it was replaced by generated prediction rows during integration.
- Scikit-learn was not installed in the available Python environment, so the planned external-library comparison is not reported as complete.
- Individual Week 3 notes for Liz and Roland were not available. Mercellinous's Week 3 AI-use details are unrecorded. Status records make these gaps explicit.

## Next Week

- Complete documentation and API comments, final report chapters, and the AI-use declaration.
- Build and run the project from a clean environment following only the README.
- Regenerate the predictions and lambda-sweep outputs, record measured results, and prepare the final demonstration.

## AI Use

The available Week 3 notes disclose Claude (Anthropic) for code drafts, test ideas, examples, and report templates. Mercellinous's Week 3 AI-use details are unrecorded; no individual Week 3 notes were available for Liz and Roland. These gaps are recorded in `ai-use-declaration.md` without inferred disclosures.
