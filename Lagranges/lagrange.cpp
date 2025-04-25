#include "lagrange.hpp"

double lagrangeInterpolation(double x, double x_vals[], double y_vals[], int n) {
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        double term = y_vals[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                term *= (x - x_vals[j]) / (x_vals[i] - x_vals[j]);
            }
        }
        result += term;
    }

    return result;
}
