#ifndef INTERPOLATION_HPP
#define INTERPOLATION_HPP

#include <vector>
#include <string>

class Interpolation {
private:
    std::vector<double> x_vals;
    std::vector<double> y_vals;

public:
    bool readDataFromFile(const std::string& filename);
    double lagrangeInterpolation(double x);

    void leastSquaresLine(double& a, double& b);
    void leastSquaresParabola(double& a, double& b, double& c);
    void leastSquaresExponential(double& a, double& b);
};

#endif
