#ifndef LAGRANGE_HPP
#define LAGRANGE_HPP

class Lagrange {
private:
    double* x_vals;
    double* y_vals;
    int n;

public:
    Lagrange(int size);
    ~Lagrange();

    void setData(double x_array[], double y_array[]);
    double interpolate(double x);
};

#endif
