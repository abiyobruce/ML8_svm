# Week 1 Progress Report

## Work Completed
- Created scaler.hpp with declarations for StandardScaler and MinMaxScaler.
- Prepared scaler.cpp with stub implementations for the scaling functions.
- Set up CMakeLists.txt and tests/CMakeLists.txt for building the library and registering tests with CTest.
- Prepared tests/test_utils.hpp and tests/test_scaler.cpp for basic test support.
- Prepared .gitignore to exclude unnecessary build files and identified the need for the group's agreed LICENSE.

## Challenges
- Understanding the project directory structure and placing files in the correct folders.
- Ensuring that declarations in the header file match the implementation file.
- Configuring CMake and CTest to build the library and register tests correctly.

## Work Planned for Week 2
- Implement fit(), transform(), fit_transform(), and inverse_transform() for both scalers.
- Add tests to verify scaling calculations and inverse transformations.
- Handle invalid datasets, inconsistent feature counts, and zero-variance features.
- Ensure errors are handled when a scaler is used before fitting.
- Build the project and run the tests using CTest.
- Ensure that scalers are fitted on training data only before transforming training and test datasets.

## AI Tool Usage

- Tool: Claude AI
- Purpose: To assist in creating and configuring the CMakeLists.txt files for the ML8_svm project, including setting up the library build configuration, specifying the C++ standard, configuring include directories, and registering tests with CTest. Claude AI was also used to assist in preparing the README file by organizing the project information, explaining the build and installation steps, and documenting how to run the tests.