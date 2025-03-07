
#include "gaussian_elimination.hpp"
#include <iostream>

int main() {
    std::vector<std::vector<double>> matrix = {
        {2, 1, -1, 8},                     //3x4 augmented matrix
        {-3, -1, 2, -11},
        {-2, 1, 2, -3}
    };

    GaussianElimination ge(matrix);            //create instance & initi with matrix
    std::cout << "Original matrix:" << std::endl;
    ge.printMatrix();                     //print original matrix 

    ge.eliminate();                       //perform gaussian elimination
    std::cout << "Matrix after elimination:" << std::endl;
    ge.printMatrix();

    std::vector<double> solution;            //perform back substitution 
    ge.backSubstitute(solution);

    std::cout << "Solution:" << std::endl;      //print final solution
    for (double val : solution) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
