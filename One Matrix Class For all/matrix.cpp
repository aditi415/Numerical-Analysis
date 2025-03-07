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
//Addition
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions do not match for addition");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}
//substraction
Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions do not match for subtraction");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}
//symmetric
bool Matrix::isSymmetric() const {
    if (rows != cols) {
        return false;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (data[i][j] != data[j][i]) {
                return false;
            }
        }
    }
    return true;
}
//identity
bool Matrix::isIdentity() const {
    if (rows != cols) {
        return false;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((j==j && data[i][j]!=1)||(i!=j && data[i][j]!=0)) {
                return false;
            }
        }
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

void Matrix::gaussianElimination(std::vector<double>& solution) {         //upper triangular 
    if (rows + 1 != cols) {
        throw std::invalid_argument("Invalid augmented matrix format");
    }
    for (int i = 0; i < rows; ++i) {
        pivot(i);
        for (int j = i + 1; j < rows; ++j) {
            double factor = data[j][i] / data[i][i];       //make ele below pivot zero
            for (int k = i; k < cols; ++k) {
                data[j][k] -= factor * data[i][k];
            }
        }
    }
    backSubstitution(solution);
}

void Matrix::backSubstitution(std::vector<double>& solution) {
    solution.resize(rows);
    for (int i = rows - 1; i >= 0; --i) {
        solution[i] = data[i][cols - 1];
        for (int j = i + 1; j < rows; ++j) {
            solution[i] -= data[i][j] * solution[j];
        }
        solution[i] /= data[i][i];
    }
}

void Matrix::pivot(int row) {
    int max_row = row;
    for (int i = row + 1; i < rows; ++i) {
        if (std::abs(data[i][row]) > std::abs(data[max_row][row])) {
            max_row = i;
        }
    }
    if (max_row != row) {
        std::swap(data[row], data[max_row]);
    }
}

