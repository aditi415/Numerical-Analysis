#include <iostream>
#include <fstream>
#include "lagrange.hpp"
using namespace std;

int main() {
    const int n = 3;
    double x_arr[n], y_arr[n];

    ifstream file("data.txt");
    for (int i = 0; i < n && file; ++i)
        file >> x_arr[i] >> y_arr[i];
    file.close();

    double x;
    cout << "Enter x: ";
    cin >> x;

    Lagrange lag(n);
    lag.setData(x_arr, y_arr);

    cout << "Interpolated value: " << lag.interpolate(x) << endl;

    return 0;
}
