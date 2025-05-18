// matrix.hpp
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <string>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows, cols;

public:
    Matrix();
    Matrix(int r, int c);
    void readFromFile(const std::string& filename);
    void print() const;

    bool isSymmetric() const;
    bool isIdentity() const;
    bool isDiagonallyDominant() const;
    void makeDiagonallyDominant();

    Matrix add(const Matrix& other) const;
    Matrix subtract(const Matrix& other) const;
    Matrix multiply(const Matrix& other) const;

    std::vector<double> gaussianElimination(std::vector<double> b);

    void choleskyDecomposition(Matrix& L);
    void croutDecomposition(Matrix& L, Matrix& U);
    void doolittleDecomposition(Matrix& L, Matrix& U);

    std::vector<double> gaussJacobi(const std::vector<double>& b, int maxIter, double tol);
    std::vector<double> gaussSeidel(const std::vector<double>& b, int maxIter, double tol);

    int getRows() const;
    int getCols() const;
    double& at(int r, int c);
    const double& at(int r, int c) const;
};

#endif
