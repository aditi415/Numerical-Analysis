#include <iostream>
#include "rootfind.hpp"

using namespace std;

int main() {
    vector<double> coeffs = {1, 0, -4}; // Example: x^2 - 4
    RootFind rf(coeffs);

    double tol = 0.001;
    cout << "Bisection Method Root: " << rf.bisection(0, 3, tol) << endl;
    cout << "Newton-Raphson Method Root: " << rf.newtonRaphson(3) << endl;
    cout << "Fixed Point Iteration Root: " << rf.fixedPoint(3) << endl;

    return 0;
}
