// Compare standard scaling with min-max scaling on a small matrix.
#include <ML8_svm/scaler.hpp>
#include <iomanip>
#include <iostream>

int main() {
    using namespace ml8_svm;

    const Matrix training_data = {
        {2.0, 1000.0},
        {4.0, 3000.0},
        {6.0, 2000.0},
    };

    // Both scaler objects can be used through the same base-class interface.
    // The selected object's fit() and transform() methods are called.
    StandardScaler standard;
    Scaler& standard_interface = standard;
    const Matrix standardized = standard_interface.fit_transform(training_data);

    MinMaxScaler min_max(0.0, 1.0);
    Scaler& min_max_interface = min_max;
    const Matrix min_max_scaled = min_max_interface.fit_transform(training_data);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Feature scaling example\n";
    std::cout << "Rows are samples; columns are features.\n\n";
    std::cout << "Original data       StandardScaler       MinMaxScaler\n";

    for (std::size_t row = 0; row < training_data.size(); ++row) {
        std::cout << "(" << training_data[row][0] << ", "
                  << training_data[row][1] << ")       ("
                  << standardized[row][0] << ", "
                  << standardized[row][1] << ")          ("
                  << min_max_scaled[row][0] << ", "
                  << min_max_scaled[row][1] << ")\n";
    }

    std::cout << "\nThe scaler is fitted on training data only.\n";
    return 0;
}
