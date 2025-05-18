#include "interpolation.hpp"
#include <fstream>
#include <cmath>
#include <iostream>

bool Interpolation::readDataFromFile(const std::string& filename) {
    std::ifstream file(filename);
    double x, y;
    if (!file.is_open()) return false;

    while (file >> x >> y) {
        x_vals.push_back(x);
        y_vals.push_back(y);
    }

    return !x_vals.empty();
}

double Interpolation::lagrangeInterpolation(double x) {
    double result = 0.0;
    int n = x_vals.size();

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

void Interpolation::leastSquaresLine(double& a, double& b) {
    int n = x_vals.size();
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < n; ++i) {
        sum_x += x_vals[i];
        sum_y += y_vals[i];
        sum_xy += x_vals[i] * y_vals[i];
        sum_x2 += x_vals[i] * x_vals[i];
    }

    double denom = n * sum_x2 - sum_x * sum_x;
    a = (n * sum_xy - sum_x * sum_y) / denom;
    b = (sum_y * sum_x2 - sum_x * sum_xy) / denom;
}

void Interpolation::leastSquaresParabola(double& a, double& b, double& c) {
    int n = x_vals.size();
    double Sx = 0, Sx2 = 0, Sx3 = 0, Sx4 = 0;
    double Sy = 0, Sxy = 0, Sx2y = 0;

    for (int i = 0; i < n; ++i) {
        double x = x_vals[i], y = y_vals[i];
        double x2 = x * x;
        double x3 = x2 * x;
        double x4 = x3 * x;

        Sx += x;
        Sx2 += x2;
        Sx3 += x3;
        Sx4 += x4;
        Sy += y;
        Sxy += x * y;
        Sx2y += x2 * y;
    }

    double D = n * (Sx2 * Sx4 - Sx3 * Sx3) - Sx * (Sx * Sx4 - Sx2 * Sx3) + Sx2 * (Sx * Sx3 - Sx2 * Sx2);
    a = (Sy * (Sx2 * Sx4 - Sx3 * Sx3) - Sx * (Sxy * Sx4 - Sx3 * Sx2y) + Sx2 * (Sxy * Sx3 - Sx2 * Sx2y)) / D;
    b = (n * (Sxy * Sx4 - Sx3 * Sx2y) - Sy * (Sx * Sx4 - Sx2 * Sx3) + Sx2 * (Sx * Sx2y - Sxy * Sx2)) / D;
    c = (n * (Sx2 * Sx2y - Sx3 * Sxy) - Sx * (Sx * Sx2y - Sxy * Sx2) + Sy * (Sx * Sx3 - Sx2 * Sx2)) / D;
}

void Interpolation::leastSquaresExponential(double& a, double& b) {
    int n = x_vals.size();
    double sum_x = 0, sum_logy = 0, sum_xlogy = 0, sum_x2 = 0;

    for (int i = 0; i < n; ++i) {
        if (y_vals[i] <= 0) {
            a = b = 0;
            return;
        }
        double logy = log(y_vals[i]);
        sum_x += x_vals[i];
        sum_logy += logy;
        sum_xlogy += x_vals[i] * logy;
        sum_x2 += x_vals[i] * x_vals[i];
    }

    double denom = n * sum_x2 - sum_x * sum_x;
    b = (n * sum_xlogy - sum_x * sum_logy) / denom;
    double loga = (sum_logy * sum_x2 - sum_x * sum_xlogy) / denom;
    a = exp(loga);
}
