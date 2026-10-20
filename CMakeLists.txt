cmake_minimum_required(VERSION 3.16)

project(ML8_svm VERSION 1.0.0 LANGUAGES CXX)

# use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# if no build type is given, use Release
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

# turn this OFF if you dont want to build the tests
option(ML8_SVM_BUILD_TESTS "Build tests" ON)

# our library (all the files in src)
add_library(ML8_svm
    src/dataset.cpp
    src/Decision.cpp
    src/hinge_loss.cpp
    src/linalg.cpp
    src/Linear_svm.cpp
    src/metrics.cpp
    src/optimizer.cpp
    src/regularization.cpp
    src/scaler.cpp
)

add_library(ML8_svm::ML8_svm ALIAS ML8_svm)

# where the header files are
target_include_directories(ML8_svm
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# show warnings
if(MSVC)
    target_compile_options(ML8_svm PRIVATE /W4)
else()
    target_compile_options(ML8_svm PRIVATE -Wall -Wextra)
endif()

# install part
include(GNUInstallDirs)

install(TARGETS ML8_svm
    EXPORT ML8_svmTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/ML8_svm
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
)

install(EXPORT ML8_svmTargets
    NAMESPACE ML8_svm::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ML8_svm
)

# tests
if(ML8_SVM_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()