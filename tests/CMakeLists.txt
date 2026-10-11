add_executable(scaler_test
    test_scaler.cpp
)
target_include_directories(scaler_test PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(scaler_test
    PRIVATE
        ML8_svm::ML8_svm
)

add_test(NAME scaler_test COMMAND scaler_test)