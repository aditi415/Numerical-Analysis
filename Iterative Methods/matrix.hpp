#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <string>

class Matrix {
private:
    int rows, cols;
    std::vector<std::vector<double>> data;

    void pivot(int row);
    void backSubstitution(std::vector<double>& solution);

public:
    Matrix(int r, int c);
    Matrix(const std::string& filename);

    void readFromFile(const std::string& filename);
    void writeToFile(const std::string& filename) const;
    void print() const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;

    bool isSymmetric() const;
    bool isIdentity() const;
    bool isDiagonallyDominant() const;

    void gaussianElimination(std::vector<double>& solution);
    std::vector<double> gaussJacobi(double tolerance = 1e-6) const;
    std::vector<double> gaussSeidel(double tolerance = 1e-6) const;
};

#endif // MATRIX_HPP
