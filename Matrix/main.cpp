#include "matrix.hpp"
#include <iostream>
using namespace std;

int main() {
    // Read matrices from files
    Matrix mat1("matrix1.txt");
    Matrix mat2("matrix2.txt");

    // Print matrices
    cout << "Matrix 1:\n";
    mat1.print();
    cout << "Matrix 2:\n";
    mat2.print();

    // Perform addition
    Matrix sum = mat1 + mat2;
    cout << "Sum of matrices:\n";
    sum.print();
    sum.writeToFile("sum_matrix.txt");

    // Perform subtraction
    Matrix diff = mat1 - mat2;
    cout << "Difference of matrices:\n";
    diff.print();
    diff.writeToFile("diff_matrix.txt");

    // Check if matrices are symmetric
    if (mat1.isSymmetric()) {
        cout << "Matrix 1 is symmetric.\n";
    } else {
        cout << "Matrix 1 is not symmetric.\n";
    }

    if (mat2.isSymmetric()) {
        cout << "Matrix 2 is symmetric.\n";
    } else {
        cout << "Matrix 2 is not symmetric.\n";
    }

    return 0;
}
