#include <iostream>
#include <cmath>

#include <iomanip>

class RootFinding
{
public:
    double bisection(double a, double b, int max_iter, double tole);

    double fun(double x);
    double dfun(double x);
    double newtonRaphson(double x0, double tol, int iter);
    double gfun(double x);
    double fixedpoint(double x1, double tolerance, int iterations);
};
