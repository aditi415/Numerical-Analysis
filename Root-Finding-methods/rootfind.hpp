#ifndef ROOTFIND_HPP
#define ROOTFIND_HPP

#include <vector>

class RootFind {
public:
    RootFind(std::vector<double> coeffs);

    double bisection(double a, double b, double tol);
    double newtonRaphson(double x0);
    double fixedPoint(double x0);

private:
    std::vector<double> coefficients;
    double func(double x);
    double func_prime(double x);
};

#endif
