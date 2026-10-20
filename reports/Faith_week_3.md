# M3 Week 3 Progress Report

### 1. Feature Scaling

I worked on StandardScaler and MinMaxScaler, including data transformation, inverse transformation, and handling constant features to prevent division by zero. I also worked on ensuring that the scalers handle data correctly and produce reliable results. This helps prepare the features for use in the machine learning model.

### 2. CMake Build System

I updated the root CMakeLists.txt to integrate project source files, configure testing, and support installation and export of the library. I also worked on connecting the different source files and ensuring that the library was configured correctly. The changes were intended to make the project easier to build, test, and install on other systems.

### 3. Challenges and Delays

Errors in CMake configuration, source-file integration, and test linking required additional debugging, causing delays in completing the build setup. Some errors made it difficult to build the project successfully and required checking the configuration files. These issues took extra time to identify and resolve, affecting progress on the remaining tasks.

### 4. Next Steps

I will resolve remaining errors, run the tests, verify installation and export, and perform a fresh-clone build test. I will also check that all source files are included correctly and that the tests run without errors. Finally, I will confirm that another user can clone the repository and build the project using the provided instructions.

### 5. AI Usage

Claude AI was used to help debug CMake configuration errors and organize the README file to improve its structure and readability. It helped identify possible causes of build problems and provided guidance on correcting the configuration. The README improvements were intended to make the project documentation clearer and easier for other users to follow.
