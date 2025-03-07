
#include "gaussian_elimination.hpp"
#include <iostream>
#include <cmath>

GaussianElimination::GaussianElimination(std::vector<std::vector<double>> &matrix)                                         //constructor 
    : matrix(matrix), n(matrix.size()) {}        //matrix to store augmented matrix

void GaussianElimination::eliminate() {                        //upper triangular form
    for (int i = 0; i < n; ++i) {
        pivot(i);                          //to swaps rows
        for (int j = i + 1; j < n; ++j) {
            double factor = matrix[j][i] / matrix[i][i];        //make ele below pivot 0
            for (int k = i; k < n + 1; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
}

void GaussianElimination::backSubstitute(std::vector<double> &solution) {
    solution.resize(n);   //ensure solution vector has correct size 
    for (int i = n - 1; i >= 0; --i) {
        solution[i] = matrix[i][n];             //initi rhs value 
        for (int j = i + 1; j < n; ++j) {
            solution[i] -= matrix[i][j] * solution[j];
        }
        solution[i] /= matrix[i][i];
    }
}

void GaussianElimination::pivot(int row) {         //swaps rows to avoid divisions
    int max_row = row;         
    for (int i = row + 1; i < n; ++i) {
        if (std::abs(matrix[i][row]) > std::abs(matrix[max_row][row])) {
            max_row = i;
        }
    }
    if (max_row != row) {
        std::swap(matrix[row], matrix[max_row]);     //swap rows 
    }
}

void GaussianElimination::printMatrix() const {              //prints augumented matrix
    for (const auto &row : matrix) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}
