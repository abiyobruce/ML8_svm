# Week 3 Report (Mon 19 – Sun 25 Oct 2026): M2 Data Preprocessing

**Member:** M2 | **Branch:** `feature/m2-preprocessing`
**Week goal:** integration, edge cases and invalid inputs covered by tests.

## Completed

| Item | File | Status |
|---|---|---|
| Stratified split verified on imbalanced data (20 / 5 samples, 20% test → 4 + 1) | `tests/test_preprocessing.cpp` | Done |
| Feature names kept in both train and test sets | `tests/test_preprocessing.cpp` | Done |
| Different seed gives a different split; input dataset is not modified | `tests/test_preprocessing.cpp` | Done |
| Ratio clamping: each class keeps at least 1 train and 1 test sample | `tests/test_preprocessing.cpp` | Done |
| Single-class error: `validate`, `train_test_split` and `encode_binary_labels` all throw `InvalidArgument` | `tests/test_preprocessing.cpp` | Done |
| Loader → preprocessing integration test: `load_csv` → `impute_missing` → `encode_binary_labels` → `validate` → `shuffle` → `train_test_split` | `tests/test_preprocessing.cpp` | Done |

`src/preprocessing.cpp` did not need changes this week. The Week 2 code already handled stratification and the single-class case, so the new work was proving it with tests.

## Testing

| Group | What is checked |
|---|---|
| stratified | class proportions in train and test, names, seeds, input unchanged, clamping |
| single class | three functions throw `InvalidArgument` |
| integration | CSV file is loaded with M1's `load_csv`, then runs through the full preprocessing chain; a missing file throws `SvmError` |

All earlier Week 2 tests still pass. Tests passed (local `ctest`): ____ / ____

## Git activity

| Commits (at least 3) | PR # | Reviewer | Merged |
|---|---|---|---|
| ____ | ____ | ____ | ☐ |

## In Progress

- 

## Challenges / Blockers

- 

## Next Week (Week 4)

- Add comments to `preprocessing.hpp`
- Fix any remaining bugs found during integration
- Write my section of `final-report.md` (preprocessing, label encoding and split choices)
- Add my contribution lines to `README.md`
- Prepare the "lessons learned" part of the presentation

## AI Use

| Tool | Purpose | Reason |
|---|---|---|
| Claude (Anthropic) | Drafted the new tests in `tests/test_preprocessing.cpp` and this report | Save time on writing test cases |

I compiled and ran the code with warnings enabled, and I reviewed and understood the tests before committing.