function(add_ml_test TEST_NAME SOURCE_FILE)
    add_executable(${TEST_NAME} ${SOURCE_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE ML8_svm::ML8_svm)
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    if(MSVC)
        target_compile_options(${TEST_NAME} PRIVATE /W4)
    else()
        target_compile_options(${TEST_NAME} PRIVATE -Wall -Wextra)
    endif()

    add_test(NAME ${TEST_NAME}
             COMMAND ${TEST_NAME}
             WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endfunction()

add_ml_test(test_dataset     test_dataset.cpp)
add_ml_test(test_hinge_loss  test_hinge_loss.cpp)
add_ml_test(test_metrics     test_metrics.cpp)
add_ml_test(test_optimizer   test_optimizer.cpp)
add_ml_test(test_scaler      test_scaler.cpp)
add_ml_test(test_decision    Decision.cpp)
add_ml_test(test_linear_svm  Linear_svm.cpp)