#include "RootFinding.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double func(double x)
{
    return x * x - 6;
}

double RootFinding::bisection(double a, double b, int max_iter, double tole)
{

    if (func(a) * func(b) >= 0)
    {
        cerr << " f(a) and f(b) should have opposite signs.\n";
    }
    double mid;

    cout << "| " << setw(10) <<  "Iteration"
         << " | " << setw(10) <<  "a"
         << " | " << setw(10) <<  "f(a)"
         << " | " << setw(10) <<  "b"
         << " | " << setw(10) <<  "f(b)"
         << " | " << setw(10) <<  "mid"
         << " | " << setw(10) <<  "f(mid)"
         << " |\n";
    cout << "------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < max_iter; i++)
    {
        double fa = func(a);
        double fb = func(b);
        mid = (a + b) / 2;
        double f_mid = func(mid);

        cout << "| "  << i
             << " | " << setw(10) << fixed << setprecision(3) << a
             << " | " << setw(10) << fa
             << " | " << setw(10) << b
             << " | " << setw(10) << fb
             << " | " << setw(10) << mid
             << " | " << setw(10) << f_mid
             << " |\n";

        if (abs(f_mid) < tole)
        {
            cout << "-----------------------------------------------------------------\n";
            return mid;
        }

        if (fa * f_mid < 0)
        {

            b = mid;
        }
        else
        {

            a = mid;
        }
    }

    return mid;
}

double RootFinding::fun(double x)
{
    return x * x * x - 6;
}
double RootFinding::dfun(double x)
{
    return 3 * x * x;
}
double RootFinding::newtonRaphson(double x0, double tol, int iter)
{
    double x = x0;

    cout << "\nNewton-Raphson Iterations:\n";
    cout << "--------------------------------------\n";
    cout << "| Iteration |    x    |   f(x) |\n";
    cout << "--------------------------------------\n";
    for (int i = 1; i <= iter; i++)
    {
        double fx = fun(x);
        double dfx = dfun(x);
        double xn = x - fun(x) / dfun(x);

        cout << "| " << i << "          | " << fixed << setprecision(3) << x << " | " << fx << " |\n";
        if (fabs(xn - x) < tol)
        {
            return xn;
        }
        x = xn;
    }
    return x;
}

double RootFinding::gfun(double x)
{
    return (x * x + 5) / 5;
}
double RootFinding::fixedpoint(double x1, double tolerance, int iterations)
{
    double x = x1;
    cout << "\nFixed Point Iterations:\n";
    cout << "--------------------------------------\n";
    cout << "| Iteration |    x    |   g(x) |\n";
    cout << "--------------------------------------\n";
    for (int i = 1; i <= iterations; i++)
    {
        double xnew = gfun(x);
        cout << "| " << i << "          | " << fixed << setprecision(3) << x << " | " << xnew << " |\n";

        if (fabs(xnew - x) < tolerance)
            return xnew;
        x = xnew;
    }
    return x;
}
