add_executable(test_scaler
    test_scaler.cpp
)

target_link_libraries(test_scaler
    PRIVATE
        ML8_svm::ML8_svm
)

add_test(
    NAME scaler_test
    COMMAND test_scaler
)

add_executable(test_optimizer
    test_optimizer.cpp
)

target_link_libraries(test_optimizer
    PRIVATE
        ML8_svm::ML8_svm
)

add_test(
    NAME optimizer_test
    COMMAND test_optimizer
)

add_executable(test_linalg
    test_linalg.cpp
)

target_link_libraries(test_linalg
    PRIVATE
        ML8_svm::ML8_svm
)

add_test(
    NAME linalg_test
    COMMAND test_linalg
)

add_executable(test_regularization
    test_regularization.cpp
)

target_link_libraries(test_regularization
    PRIVATE
        ML8_svm::ML8_svm
)

add_test(
    NAME regularization_test
    COMMAND test_regularization
)