cmake_minimum_required(VERSION 3.16)

project(ML8_svm VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CTest)
include(CMakePackageConfigHelpers)

option(ML8_SVM_BUILD_EXAMPLES "Build the example programs" ON)

add_library(ML8_svm
    src/dataset.cpp
    src/decision.cpp
    src/hinge_loss.cpp
    src/hyperplane.cpp
    src/linalg.cpp
    src/linear_svm.cpp
    src/metrics.cpp
    src/optimizer.cpp
    src/preprocessing.cpp
    src/regularization.cpp
    src/scaler.cpp
    src/support_vectors.cpp
)

add_library(ML8_svm::ML8_svm ALIAS ML8_svm)

target_compile_features(ML8_svm PUBLIC cxx_std_17)
target_include_directories(ML8_svm
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

if(ML8_SVM_BUILD_EXAMPLES)
    # Keep explicit source names so each example is easy to find and modify.
    set(ML8_SVM_EXAMPLES
        example1_load_csv
        example2_scaling
        example3_margin
        example4_train_predict
        example5_full_pipeline
        example6_loss_curve
        example7_support_vectors
        lambda_sweep
    )
    foreach(example_name IN LISTS ML8_SVM_EXAMPLES)
        if(example_name STREQUAL "lambda_sweep")
            set(example_source examples/lambda_sweep.cpp)
        else()
            set(example_source examples/${example_name}.cpp)
        endif()
        get_filename_component(example_target ${example_name} NAME_WE)
        add_executable(${example_target} ${example_source})
        target_link_libraries(${example_target} PRIVATE ML8_svm::ML8_svm)
    endforeach()
endif()

install(TARGETS ML8_svm
    EXPORT ML8_svmTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT ML8_svmTargets
    FILE ML8_svmTargets.cmake
    NAMESPACE ML8_svm::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ML8_svm
)

configure_package_config_file(
    cmake/ML8_svmConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ML8_svmConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ML8_svm
)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ML8_svmConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ML8_svmConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ML8_svmConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ML8_svm
)
