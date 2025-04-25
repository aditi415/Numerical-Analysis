#include <iostream>
#include <fstream>
#include "lagrange.hpp"
using namespace std;

int main() {
    const int n = 3;
    double x_vals[n], y_vals[n];
    ifstream infile("poly.txt");

    if (!infile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        infile >> x_vals[i] >> y_vals[i];
    }
    infile.close();

    double x;
    cout << "Enter value of x to evaluate the polynomial: ";
    cin >> x;

    double result = lagrangeInterpolation(x, x_vals, y_vals, n);
    cout << "Interpolated value at x = " << x << " is " << result << endl;

    return 0;
}
