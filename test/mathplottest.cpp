#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main() {
    // Data to be plotted
    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {2, 4, 6, 8, 10};

    // Create a plot
    plt::plot(x, y);

    // Show the plot
    plt::show();

    return 0;
}

