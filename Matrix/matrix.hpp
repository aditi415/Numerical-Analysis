#include <vector>
#include <string>

class Matrix {
private:
    std::vector<std::vector<int>> data;
    int rows, cols;

public:
    Matrix(int r, int c);     //constructs matrix 
    Matrix(const std::string& filename);          //constructs matrix by reading from file

    void readFromFile(const std::string& filename);              //read mat data from file
    void writeToFile(const std::string& filename) const;         //write current matrix data

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    bool isSymmetric() const;

    void print() const;
};


