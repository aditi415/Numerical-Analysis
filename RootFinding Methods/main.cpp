#include <iostream>
#include "RootFinding.hpp"

using namespace std;

int main()
{
    RootFinding rfind;

    double a=-10 , b=10 , tole;
    int max_iter = 5;

    cout << "Enter tolerance: ";
    cin >> tole;

    double rootbisection = rfind.bisection(a, b, max_iter, tole);

    cout << "\n Root using Bisection: " << rootbisection << "\n";

    double x0 = 1.0, tol;
    int iter = 4;

    RootFinding rf;

    cout << "Enter tolerance: ";
    cin >> tol;

    double root = rf.newtonRaphson(x0, tol, iter);
    cout << "\n Estimated Root: " << root << "\n";

    double x1 = 1.5, tolerance;
    int iterations = 5;
    RootFinding rootf;

    cout << "Enter tolerance: ";
    cin >> tolerance;

    double rootfixed = rootf.fixedpoint(x1, tolerance, iterations);
    cout << "\nEstimated Root: " << rootfixed << "\n";

    return 0;
}
