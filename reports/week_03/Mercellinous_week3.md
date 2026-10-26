# Week 3 Progress Record for Mercellinous

**Project area:** Gradient-based optimization  

## Completed

- The repository contains batch, stochastic, and mini-batch gradient updates.
- The optimizer uses seeded sample ordering, optional learning-rate decay, and tolerance-based stopping.
- The optimizer test covers loss reduction, several batch sizes, early stopping, and repeatability with a fixed seed.
- The loss-curve example prints one objective value per completed epoch.

## Verification

- The optimizer test passed as part of the 13-program direct Clang test run, and the loss-curve example ran successfully.
- Direct compile and link verification succeeded for all 12 library sources, all test programs, and all examples. CMake/CTest remains unverified on this host because its build tools were unavailable.

## Challenges and Blockers

- The original Week 3 M7 report was empty. This record summarizes the source and test files rather than claiming to reproduce the missing individual account.
- The local MinGW compiler cannot start, so CMake's normal build path was unavailable. The separate direct Clang verification succeeded.

## Next Week

- Verify the optimizer and loss-curve example in the complete build, record the exact configuration and output, and review the README limitations.

