// main.cpp
#include "matrix.hpp"
#include <iostream>
#include <vector>

int main() {
    try {
        Matrix A;
        A.readFromFile("matrix.txt");

        std::cout << "Matrix A:" << std::endl;
        A.print();

        std::cout << "Is Symmetric? " << (A.isSymmetric() ? "Yes" : "No") << std::endl;
        std::cout << "Is Identity? " << (A.isIdentity() ? "Yes" : "No") << std::endl;
        std::cout << "Is Diagonally Dominant? " << (A.isDiagonallyDominant() ? "Yes" : "No") << std::endl;

        if (!A.isDiagonallyDominant()) {
            std::cout << "Making A diagonally dominant..." << std::endl;
            A.makeDiagonallyDominant();
            A.print();
        }

        Matrix B;
        B.readFromFile("matrix2.txt");

        std::cout << "Matrix A + B:" << std::endl;
        Matrix C = A.add(B);
        C.print();

        std::cout << "Matrix A - B:" << std::endl;
        C = A.subtract(B);
        C.print();

        std::cout << "Matrix A * B:" << std::endl;
        C = A.multiply(B);
        C.print();

        std::ifstream bfile("b.txt");
        int n;
        bfile >> n;
        std::vector<double> b(n);
        for (int i = 0; i < n; ++i) bfile >> b[i];

        std::cout << "Gaussian Elimination Solution:" << std::endl;
        std::vector<double> x = A.gaussianElimination(b);
        for (double xi : x) std::cout << xi << " ";
        std::cout << std::endl;

        std::cout << "Gauss-Jacobi Solution:" << std::endl;
        x = A.gaussJacobi(b);
        for (double xi : x) std::cout << xi << " ";
        std::cout << std::endl;

        std::cout << "Gauss-Seidel Solution:" << std::endl;
        x = A.gaussSeidel(b);
        for (double xi : x) std::cout << xi << " ";
        std::cout << std::endl;

        std::cout << "Cholesky Decomposition (L):" << std::endl;
        Matrix L(A.getRows(), A.getCols());
        A.choleskyDecomposition(L);
        L.print();

        std::cout << "Crout Decomposition (L and U):" << std::endl;
        Matrix L1(A.getRows(), A.getCols());
        Matrix U1(A.getRows(), A.getCols());
        A.croutDecomposition(L1, U1);
        std::cout << "L:" << std::endl;
        L1.print();
        std::cout << "U:" << std::endl;
        U1.print();

        std::cout << "Doolittle Decomposition (L and U):" << std::endl;
        Matrix L2(A.getRows(), A.getCols());
        Matrix U2(A.getRows(), A.getCols());
        A.doolittleDecomposition(L2, U2);
        std::cout << "L:" << std::endl;
        L2.print();
        std::cout << "U:" << std::endl;
        U2.print();

    } catch (std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}
