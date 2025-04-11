#include "matrix.hpp"
#include <iostream>

int main() {
        if (augMatrix.isDiagonallyDominant()) {
            std::cout << "Augmented matrix is diagonally dominant.\n";
        } else {
            std::cout << "Augmented matrix is not diagonally dominant.\n";
        }

      
        std::cout << "Gauss-Jacobi Iterative Method Solution:\n";
        try {
            std::vector<double> jacobiSolution = augMatrix.gaussJacobi(1e-6);
            for (double val : jacobiSolution) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Gauss-Jacobi failed: " << e.what() << std::endl;
        }

        std::cout << "Gauss-Seidel Iterative Method Solution:\n";
        try {
            std::vector<double> seidelSolution = augMatrix.gaussSeidel(1e-6);
            for (double val : seidelSolution) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Gauss-Seidel failed: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

