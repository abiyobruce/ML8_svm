cmake_minimum_required(VERSION 3.16)

project(ML8_svm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ML8_svm
    src/scaler.cpp
)

add_library(ML8_svm::ML8_svm ALIAS ML8_svm)

target_include_directories(ML8_svm
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()

add_subdirectory(tests)