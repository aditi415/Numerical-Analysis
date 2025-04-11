#include "matrix.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cmath>

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data.resize(rows, std::vector<double>(cols, 0));
}

Matrix::Matrix(const std::string& filename) {
    readFromFile(filename);
}

void Matrix::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    file >> rows >> cols;
    data.resize(rows, std::vector<double>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> data[i][j];
        }
    }
}

void Matrix::writeToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    file << rows << " " << cols << "\n";
    for (const auto& row : data) {
        for (double val : row) {
            file << val << " ";
        }
        file << "\n";
    }
}


bool Matrix::isDiagonallyDominant() const {
    if (rows != cols) return false;
    for (int i = 0; i < rows; ++i) {
        double diag = std::abs(data[i][i]);
        double sum = 0.0;
        for (int j = 0; j < cols; ++j) {
            if (i != j) sum += std::abs(data[i][j]);
        }
        if (diag < sum) return false;
    }
    return true;
}

void Matrix::print() const {
    for (const auto& row : data) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}

std::vector<double> Matrix::gaussJacobi(double tolerance) const {
    if (rows + 1 != cols) {
        throw std::invalid_argument("Invalid augmented matrix format for Gauss-Jacobi");
    }

    std::vector<double> x(rows, 0.0);
    std::vector<double> x_new(rows, 0.0);

    while (true) {
        for (int i = 0; i < rows; ++i) {
            double sum = data[i][cols - 1];
            for (int j = 0; j < cols - 1; ++j) {
                if (j != i) {
                    sum -= data[i][j] * x[j];
                }
            }
            x_new[i] = sum / data[i][i];
        }

        bool converged = true;
        for (int i = 0; i < rows; ++i) {
            if (std::abs(x_new[i] - x[i]) > tolerance) {
                converged = false;
                break;
            }
        }
        x = x_new;
        if (converged) break;
    }

    return x;
}

std::vector<double> Matrix::gaussSeidel(double tolerance) const {
    if (rows + 1 != cols) {
        throw std::invalid_argument("Invalid augmented matrix format for Gauss-Seidel");
    }

    std::vector<double> x(rows, 0.0);

    while (true) {
        std::vector<double> x_old = x;

        for (int i = 0; i < rows; ++i) {
            double sum = data[i][cols - 1];
            for (int j = 0; j < cols - 1; ++j) {
                if (j != i) {
                    sum -= data[i][j] * x[j];
                }
            }
            x[i] = sum / data[i][i];
        }

        bool converged = true;
        for (int i = 0; i < rows; ++i) {
            if (std::abs(x[i] - x_old[i]) > tolerance) {
                converged = false;
                break;
            }
        }
        if (converged) break;
    }

    return x;
}

