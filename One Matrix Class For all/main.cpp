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

                           // Solve system of equations by Gaussian Elimination
        Matrix augMatrix("augmented_matrix.txt");
        std::vector<double> solution;
        augMatrix.gaussianElimination(solution);

        std::cout << "Solution to linear system:\n";
        for (double val : solution) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
                       //Iterative methods Gauss-Jacobi  & Seidel
        
        std::cout << "Gauss-Jacobi Iterative Method Solution:\n";
            std::vector<double> jacobiSolution = augMatrix.gaussJacobi(1e-6);
            for (double val : jacobiSolution) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
            std::cerr << "Gauss-Jacobi failed: " << e.what() << std::endl;
        }

        std::cout << "Gauss-Seidel Iterative Method Solution:\n";
            std::vector<double> seidelSolution = augMatrix.gaussSeidel(1e-6);
            for (double val : seidelSolution) {
                std::cout << val << " ";
            }
            std::cout << std::endl;

    std::vector<std::vector<double>> readMatrix(const std::string& filename) {
    std::ifstream file(filename);
    int n;
    file >> n;

    std::vector<std::vector<double>> mat(n, std::vector<double>(n));
    for (auto& row : mat)
        for (double& val : row)
            file >> val;

    return mat;
}  
    auto matrix = readMatrix("matrix.txt");
    LUDecomposition lu(matrix);

    std::vector<std::vector<double>> L, U;

    lu.croutDecomposition(L, U);
    lu.printMatrix(L, "Crout L");
    lu.printMatrix(U, "Crout U");

    lu.doolittleDecomposition(L, U);
    lu.printMatrix(L, "Doolittle L");
    lu.printMatrix(U, "Doolittle U");

    lu.choleskyDecomposition(L);
    lu.printMatrix(L, "Cholesky L");
        

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Gauss-Jacobi failed: " << e.what() << std::endl;
        std::cerr << "Gauss-Seidel failed: " << e.what() << std::endl;

    }

    return 0;
}
