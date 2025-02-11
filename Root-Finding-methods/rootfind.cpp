#include <iostream>
#include <cmath>
#include "rootfind.hpp"

using namespace std;

// Constructor
RootFind::RootFind(vector<double> coeffs) {
    coefficients = coeffs;
}

// Function to evaluate polynomial f(x)
double RootFind::func(double x) {
    double result = 0;
    int degree = coefficients.size() - 1;
    for (double coeff : coefficients) {
        result += coeff * pow(x, degree);
        degree--;
    }
    return result;
}

// Function to evaluate derivative f'(x)
double RootFind::func_prime(double x) {
    double result = 0;
    int degree = coefficients.size() - 1;
    for (int i = 0; i < degree; i++) {
        result += coefficients[i] * (degree - i) * pow(x, degree - i - 1);
    }
    return result;
}

// Bisection Method
double RootFind::bisection(double a, double b, double tol) {
    if (func(a) * func(b) >= 0) {
        cout << "Invalid interval. Choose different a and b.\n";
        return -1;
    }
    while ((b - a) / 2 > tol) {
        double c = (a + b) / 2;
        if (func(c) == 0.0) return c;
        if (func(c) * func(a) < 0)
            b = c;
        else
            a = c;
    }
    return (a + b) / 2;
}

// Newton-Raphson Method
double RootFind::newtonRaphson(double x0) {
    int maxIter = 100;
    double x1;
    for (int i = 0; i < maxIter; i++) {
        if (func_prime(x0) == 0) {
            cout << "Derivative is zero. Choose a different starting point.\n";
            return -1;
        }
        x1 = x0 - func(x0) / func_prime(x0);
        if (fabs(x1 - x0) < 1e-6) break;
        x0 = x1;
    }
    return x1;
}

// Fixed Point Iteration Method
double RootFind::fixedPoint(double x0) {
    int maxIter = 100;
    double x1;
    for (int i = 0; i < maxIter; i++) {
        x1 = func(x0) + x0;  // A simple transformation g(x) = f(x) + x
        if (fabs(x1 - x0) < 1e-6) break;
        x0 = x1;
    }
    return x1;
}
