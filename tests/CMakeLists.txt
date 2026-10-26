
set(ML8_SVM_TESTS
    dataset
    decision
    hinge_loss
    hyperplane
    linalg
    linear_svm
    metrics
    optimizer
    pipeline
    preprocessing
    regularization
    scaler
    support_vectors
)

foreach(test_name IN LISTS ML8_SVM_TESTS)
    add_executable(test_${test_name} test_${test_name}.cpp)
    target_link_libraries(test_${test_name} PRIVATE ML8_svm::ML8_svm)
    add_test(NAME ${test_name}_test COMMAND test_${test_name})
    set_tests_properties(${test_name}_test PROPERTIES
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    )
endforeach()
