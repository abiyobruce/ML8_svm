// Show how a point's score relates to its distance from a hyperplane.
#include <ML8_svm/ML8_svm.hpp>

#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    using namespace ml8_svm;

    Hyperplane plane;
    plane.w = {3.0, 4.0};
    plane.b = -1.0;

    const std::vector<Vector> points = {{1.0, 1.0}, {0.0, 0.25}, {-1.0, 0.0}};
    const std::vector<int> labels = {1, -1, -1};

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Hyperplane: score(x) = 3*x1 + 4*x2 - 1\n";
    std::cout << "Margin width: " << plane.margin_width() << "\n\n";
    std::cout << "point       label  score  distance  functional  geometric\n";

    for (std::size_t i = 0; i < points.size(); ++i) {
        std::cout << '(' << points[i][0] << ", " << points[i][1] << ")  "
                  << labels[i] << "      " << plane.score(points[i]) << "   "
                  << plane.distance(points[i]) << "      "
                  << plane.functional_margin(points[i], labels[i]) << "       "
                  << plane.geometric_margin(points[i], labels[i]) << '\n';
    }

    return 0;
}
