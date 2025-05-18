// main.cpp
#include "matrix.hpp"
#include <iostream>
#include <fstream>
#include <vector>

int main() {
    Matrix A;
    if (!A.readFromFile("49l.txt")) {
        std::cerr << "Failed to read matrix from 49l.txt\n";
        return 1;
    }

    std::ifstream bfile("49r.txt");
    if (!bfile.is_open()) {
        std::cerr << "Failed to read vector from 49r.txt\n";
        return 1;
    }

    std::vector<double> b;
    double val;
    while (bfile >> val) b.push_back(val);
    bfile.close();

    std::cout << "Matrix A:\n";
    A.print();

    std::cout << "\nVector b:\n";
    for (double bi : b) std::cout << bi << " ";
    std::cout << "\n";

    std::cout << "\nIs Symmetric? " << (A.isSymmetric() ? "Yes" : "No") << "\n";
    std::cout << "Is Identity? " << (A.isIdentity() ? "Yes" : "No") << "\n";
    std::cout << "Is Diagonally Dominant? " << (A.isDiagonallyDominant() ? "Yes" : "No") << "\n";

    if (!A.isDiagonallyDominant()) {
        std::cout << "Making A diagonally dominant...\n";
        A.makeDiagonallyDominant();
        A.print();
    }

    std::cout << "\nGaussian Elimination Solution:\n";
    std::vector<double> x = A.gaussianElimination(b);
    for (double xi : x) std::cout << xi << " ";
    std::cout << "\n";

    std::cout << "\nGauss-Jacobi Solution:\n";
    x = A.gaussJacobi(b, 1000, 1e-6);
    for (double xi : x) std::cout << xi << " ";
    std::cout << "\n";

    std::cout << "\nGauss-Seidel Solution:\n";
    x = A.gaussSeidel(b, 1000, 1e-6);
    for (double xi : x) std::cout << xi << " ";
    std::cout << "\n";

    std::cout << "\nCholesky Decomposition (L):\n";
    Matrix L(A.getRows(), A.getCols());
    A.choleskyDecomposition(L);
    L.print();

    std::cout << "\nCrout Decomposition (L and U):\n";
    Matrix L1(A.getRows(), A.getCols());
    Matrix U1(A.getRows(), A.getCols());
    A.croutDecomposition(L1, U1);
    std::cout << "L:\n";
    L1.print();
    std::cout << "U:\n";
    U1.print();

    std::cout << "\nDoolittle Decomposition (L and U):\n";
    Matrix L2(A.getRows(), A.getCols());
    Matrix U2(A.getRows(), A.getCols());
    A.doolittleDecomposition(L2, U2);
    std::cout << "L:\n";
    L2.print();
    std::cout << "U:\n";
    U2.print();

    return 0;
}
