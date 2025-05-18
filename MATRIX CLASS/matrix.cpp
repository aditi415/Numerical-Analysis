// matrix.cpp
#include "matrix.hpp"
#include <iostream>
#include <fstream>
#include <cmath>

Matrix::Matrix() : rows(0), cols(0) {}

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<double>(c, 0.0)) {}

bool Matrix::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::vector<double> flatData;
    double value;
    while (file >> value) flatData.push_back(value);
    file.close();

    int size = static_cast<int>(std::sqrt(flatData.size()));
    if (size * size != static_cast<int>(flatData.size())) return false;

    rows = cols = size;
    data.resize(rows, std::vector<double>(cols));

    int idx = 0;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            data[i][j] = flatData[idx++];

    return true;
}

void Matrix::print() const {
    for (const auto& row : data) {
        for (double val : row)
            std::cout << val << " ";
        std::cout << "\n";
    }
}

bool Matrix::isSymmetric() const {
    if (rows != cols) return false;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (data[i][j] != data[j][i]) return false;
    return true;
}

bool Matrix::isIdentity() const {
    if (rows != cols) return false;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if ((i == j && data[i][j] != 1) || (i != j && data[i][j] != 0)) return false;
    return true;
}

bool Matrix::isDiagonallyDominant() const {
    for (int i = 0; i < rows; ++i) {
        double sum = 0;
        for (int j = 0; j < cols; ++j)
            if (i != j) sum += std::abs(data[i][j]);
        if (std::abs(data[i][i]) < sum) return false;
    }
    return true;
}

void Matrix::makeDiagonallyDominant() {
    for (int i = 0; i < rows; ++i) {
        double rowSum = 0;
        for (int j = 0; j < cols; ++j)
            if (i != j) rowSum += std::abs(data[i][j]);
        data[i][i] = rowSum + 1;
    }
}

Matrix Matrix::add(const Matrix& other) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.data[i][j] = data[i][j] + other.data[i][j];
    return result;
}

Matrix Matrix::subtract(const Matrix& other) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.data[i][j] = data[i][j] - other.data[i][j];
    return result;
}

Matrix Matrix::multiply(const Matrix& other) const {
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < other.cols; ++j)
            for (int k = 0; k < cols; ++k)
                result.data[i][j] += data[i][k] * other.data[k][j];
    return result;
}

std::vector<double> Matrix::gaussianElimination(std::vector<double> b) {
    for (int i = 0; i < rows; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < rows; ++k)
            if (std::abs(data[k][i]) > std::abs(data[maxRow][i]))
                maxRow = k;
        std::swap(data[i], data[maxRow]);
        std::swap(b[i], b[maxRow]);
        for (int k = i + 1; k < rows; ++k) {
            double factor = data[k][i] / data[i][i];
            for (int j = i; j < cols; ++j)
                data[k][j] -= factor * data[i][j];
            b[k] -= factor * b[i];
        }
    }
    std::vector<double> x(rows);
    for (int i = rows - 1; i >= 0; --i) {
        x[i] = b[i];
        for (int j = i + 1; j < cols; ++j)
            x[i] -= data[i][j] * x[j];
        x[i] /= data[i][i];
    }
    return x;
}

void Matrix::choleskyDecomposition(Matrix& L) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j <= i; ++j) {
            double sum = 0;
            for (int k = 0; k < j; ++k)
                sum += L.data[i][k] * L.data[j][k];
            if (i == j)
                L.data[i][j] = std::sqrt(data[i][i] - sum);
            else
                L.data[i][j] = (data[i][j] - sum) / L.data[j][j];
        }
}

void Matrix::croutDecomposition(Matrix& L, Matrix& U) {
    for (int i = 0; i < rows; ++i) U.data[i][i] = 1;
    for (int j = 0; j < cols; ++j) {
        for (int i = j; i < rows; ++i) {
            double sum = 0;
            for (int k = 0; k < j; ++k) sum += L.data[i][k] * U.data[k][j];
            L.data[i][j] = data[i][j] - sum;
        }
        for (int i = j + 1; i < cols; ++i) {
            double sum = 0;
            for (int k = 0; k < j; ++k) sum += L.data[j][k] * U.data[k][i];
            U.data[j][i] = (data[j][i] - sum) / L.data[j][j];
        }
    }
}

void Matrix::doolittleDecomposition(Matrix& L, Matrix& U) {
    for (int i = 0; i < rows; ++i) L.data[i][i] = 1;
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i <= j; ++i) {
            double sum = 0;
            for (int k = 0; k < i; ++k) sum += L.data[i][k] * U.data[k][j];
            U.data[i][j] = data[i][j] - sum;
        }
        for (int i = j + 1; i < rows; ++i) {
            double sum = 0;
            for (int k = 0; k < j; ++k) sum += L.data[i][k] * U.data[k][j];
            L.data[i][j] = (data[i][j] - sum) / U.data[j][j];
        }
    }
}

std::vector<double> Matrix::gaussJacobi(const std::vector<double>& b, int maxIter, double tol) {
    std::vector<double> x(rows, 0.0), x_new(rows);
    for (int iter = 0; iter < maxIter; ++iter) {
        for (int i = 0; i < rows; ++i) {
            double sigma = 0;
            for (int j = 0; j < cols; ++j)
                if (j != i) sigma += data[i][j] * x[j];
            x_new[i] = (b[i] - sigma) / data[i][i];
        }
        double err = 0;
        for (int i = 0; i < rows; ++i)
            err += std::abs(x_new[i] - x[i]);
        if (err < tol) break;
        x = x_new;
    }
    return x;
}

std::vector<double> Matrix::gaussSeidel(const std::vector<double>& b, int maxIter, double tol) {
    std::vector<double> x(rows, 0.0);
    for (int iter = 0; iter < maxIter; ++iter) {
        std::vector<double> x_old = x;
        for (int i = 0; i < rows; ++i) {
            double sigma = 0;
            for (int j = 0; j < cols; ++j)
                if (j != i) sigma += data[i][j] * x[j];
            x[i] = (b[i] - sigma) / data[i][i];
        }
        double err = 0;
        for (int i = 0; i < rows; ++i)
            err += std::abs(x[i] - x_old[i]);
        if (err < tol) break;
    }
    return x;
}

int Matrix::getRows() const { return rows; }
int Matrix::getCols() const { return cols; }
double& Matrix::at(int r, int c) { return data[r][c]; }
const double& Matrix::at(int r, int c) const { return data[r][c]; }
