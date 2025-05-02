#include "matrix.hpp"
#include <iostream>

int main() {
    try {
        Matrix mat1("matrix1.txt");
        Matrix mat2("matrix2.txt");

        std::cout << "Matrix 1:\n";
        mat1.print();
        std::cout << "Matrix 2:\n";
        mat2.print();

        Matrix sum = mat1 + mat2;
        std::cout << "Sum of matrices:\n";
        sum.print();
        sum.writeToFile("sum_matrix.txt");

        Matrix diff = mat1 - mat2;
        std::cout << "Difference of matrices:\n";
        diff.print();
        diff.writeToFile("diff_matrix.txt");

        if (mat1.isSymmetric()) {
            std::cout << "Matrix 1 is symmetric.\n";
        } else {
            std::cout << "Matrix 1 is not symmetric.\n";
        }

        if (mat2.isSymmetric()) {
            std::cout << "Matrix 2 is symmetric.\n";
        } else {
            std::cout << "Matrix 2 is not symmetric.\n";
        }

        if (mat1.isIdentity()) {
            std::cout << "Matrix 1 is an identity matrix.\n";
        } else {
            std::cout << "Matrix 1 is not an identity matrix.\n";
        }

        // Diagonal Dominance Check
        if (mat1.isDiagonallyDominant()) {
            std::cout << "Matrix 1 is diagonally dominant.\n";
        } else {
            std::cout << "Matrix 1 is not diagonally dominant.\n";
            mat1.makeDiagonallyDominant();
            std::cout << "Matrix 1 after attempting to make diagonally dominant:\n";
            mat1.print();
        }

        // Solve system of equations
        Matrix augMatrix("augmented_matrix.txt");
        std::vector<double> solution;
        augMatrix.gaussianElimination(solution);

        std::cout << "Solution to linear system:\n";
        for (double val : solution) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
