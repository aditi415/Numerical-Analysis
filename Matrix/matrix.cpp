#include "matrix.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

//constructor for creating empty matrix
Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data.resize(rows, std::vector<int>(cols, 0));
}

//constructor to read matrix from file
Matrix::Matrix(const std::string& filename) {
    readFromFile(filename);
}

//reading from a file 
void Matrix::readFromFile(const std::string& filename) {
    std::ifstream file(filename);                 //open file
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    file >> rows >> cols;            //reads rows cols from file
    data.resize(rows, std::vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> data[i][j];               //read mat value from file int data 
        }
    }
}

//writing to file
void Matrix::writeToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    file << rows << " " << cols << "\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file << data[i][j] << " ";
        }
        file << "\n";
    }
}

//Add
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrices dimensions do not match for addition");     //not match
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

//subtract
Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrices dimensions do not match for subtraction");
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

//printing matrix
void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << "\n";
    }
}
