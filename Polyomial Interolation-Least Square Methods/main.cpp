#include "interpolation.hpp"
#include <iostream>

int main() {
    Interpolation interp;
    if (!interp.readDataFromFile("data.txt")) {
        std::cerr << "Failed to read data.\n";
        return 1;
    }

    double x;
    std::cout << "Enter the value of x for Lagrange Interpolation: ";
    std::cin >> x;

    double lagrangeVal = interp.lagrangeInterpolation(x);
    std::cout << "Lagrange Interpolated value at x = " << x << " is " << lagrangeVal << "\n";

    double a, b, c;
    interp.leastSquaresLine(a, b);
    std::cout << "Least Squares Line Fit: y = " << a << "x + " << b << "\n";

    interp.leastSquaresParabola(a, b, c);
    std::cout << "Least Squares Parabola Fit: y = " << a << "x^2 + " << b << "x + " << c << "\n";

    interp.leastSquaresExponential(a, b);
    std::cout << "Least Squares Exponential Fit: y = " << a << " * e^(" << b << "x)\n";

    return 0;
}
