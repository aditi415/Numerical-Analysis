
#ifndef GAUSSIAN_ELIMINATION_HPP
#define GAUSSIAN_ELIMINATION_HPP

#include <vector>

class GaussianElimination {                //defines class
public:
    GaussianElimination(std::vector<std::vector<double>> &matrix);     //constructor take reference to matrix(2D)
    void eliminate();       //converting to upper triangular
    void backSubstitute(std::vector<double> &solution);     //back substitution
    void printMatrix() const;

private:
    std::vector<std::vector<double>> matrix;      //stores augumented matrix
    int n;                                        //stores number of equation
    void pivot(int row);                         //partial pivoting
};
#endif // GAUSSIAN_ELIMINATION_HPP
