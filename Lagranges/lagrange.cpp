#include "lagrange.h"

Lagrange::Lagrange(int size) {
    n = size;
    x_vals = new double[n];
    y_vals = new double[n];
}

Lagrange::~Lagrange() {
    delete[] x_vals;
    delete[] y_vals;
}

void Lagrange::setData(double x_array[], double y_array[]) {
    for (int i = 0; i < n; ++i) {
        x_vals[i] = x_array[i];
        y_vals[i] = y_array[i];
    }
}

double Lagrange::interpolate(double x) {
    double result = 0;
    for (int i = 0; i < n; ++i) {
        double term = y_vals[i];
        for (int j = 0; j < n; ++j) {
            if (j != i)
                term *= (x - x_vals[j]) / (x_vals[i] - x_vals[j]);
        }
        result += term;
    }
    return result;
}
