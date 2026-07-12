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

bool Matrix::isDiagonallyDominant() const {
    if (rows != cols) {
        return false;
    }

    for (int i = 0; i < rows; ++i) {
        double diag = std::abs(data[i][i]);
        double sum = 0.0;
        for (int j = 0; j < cols; ++j) {
            if (i != j) {
                sum += std::abs(data[i][j]);
            }
        }

        if (diag < sum) {
            return false;
        }
    }
    return true;
}

void Matrix::makeDiagonallyDominant() {
    if (isDiagonallyDominant()) {
        std::cout << "Matrix is already diagonally dominant.\n";
        return;
    }

    std::vector<std::vector<double>> newMatrix = data;
    bool changed = false;

    for (int i = 0; i < rows; ++i) {
        int bestRow = -1;
        for (int j = i; j < rows; ++j) {
            double diag = std::abs(newMatrix[j][i]);
            double sum = 0.0;
            for (int k = 0; k < cols; ++k) {
                if (k != i) sum += std::abs(newMatrix[j][k]);
            }

            if (diag >= sum) {
                bestRow = j;
                break;
            }
        }

        if (bestRow != -1 && bestRow != i) {
            std::swap(newMatrix[i], newMatrix[bestRow]);
            changed = true;
        }
    }

    Matrix temp(newMatrix);
    if (temp.isDiagonallyDominant()) {
        data = newMatrix;
        std::cout << "Matrix was transformed into diagonally dominant form.\n";
    } else {
        std::cout << "It is not possible to make the matrix diagonally dominant.\n";
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

                                //LU Decomposition methods

LUDecomposition::LUDecomposition(const std::vector<std::vector<double>>& matrix) : A(matrix) {
    n = matrix.size();
}

void LUDecomposition::croutDecomposition(std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U) {
    L.assign(n, std::vector<double>(n, 0));
    U.assign(n, std::vector<double>(n, 0));

    for (int j = 0; j < n; ++j) {
        U[j][j] = 1.0;

        for (int i = j; i < n; ++i) {
            double sum = 0;
            for (int k = 0; k < j; ++k)
                sum += L[i][k] * U[k][j];
            L[i][j] = A[i][j] - sum;
        }

        for (int i = j + 1; i < n; ++i) {
            double sum = 0;
            for (int k = 0; k < j; ++k)
                sum += L[j][k] * U[k][i];
            U[j][i] = (A[j][i] - sum) / L[j][j];
        }
    }
}

void LUDecomposition::doolittleDecomposition(std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U) {
    L.assign(n, std::vector<double>(n, 0));
    U.assign(n, std::vector<double>(n, 0));

    for (int i = 0; i < n; ++i) {
        L[i][i] = 1.0;

        for (int k = i; k < n; ++k) {
            double sum = 0;
            for (int j = 0; j < i; ++j)
                sum += L[i][j] * U[j][k];
            U[i][k] = A[i][k] - sum;
        }

        for (int k = i + 1; k < n; ++k) {
            double sum = 0;
            for (int j = 0; j < i; ++j)
                sum += L[k][j] * U[j][i];
            L[k][i] = (A[k][i] - sum) / U[i][i];
        }
    }
}

void LUDecomposition::choleskyDecomposition(std::vector<std::vector<double>>& L) {
    L.assign(n, std::vector<double>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            double sum = 0;

            if (i == j) {
                for (int k = 0; k < j; ++k)
                    sum += L[j][k] * L[j][k];
                L[j][j] = std::sqrt(A[j][j] - sum);
            } else {
                for (int k = 0; k < j; ++k)
                    sum += L[i][k] * L[j][k];
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
}

void LUDecomposition::printMatrix(const std::vector<std::vector<double>>& matrix, const std::string& name) {
    std::cout << name << " Matrix:\n";
    for (const auto& row : matrix) {
        for (double val : row)
            std::cout << val << "\t";
        std::cout << "\n";
    }
    std::cout << std::endl;
}
