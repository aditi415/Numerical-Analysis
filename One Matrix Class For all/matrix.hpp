#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <fstream>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows, cols;

    void pivot(int row);
    void backSubstitution(std::vector<double>& solution);

public:
    Matrix(int r, int c);
    Matrix(const std::string& filename);

    void readFromFile(const std::string& filename);
    void writeToFile(const std::string& filename) const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;

    bool isSymmetric() const;
    bool isIdentity() const;
    bool isDiagonallyDominant() const;
    void makeDiagonallyDominant();

    void gaussianElimination(std::vector<double>& solution);
    void print() const;
};

#endif // MATRIX_HPP
