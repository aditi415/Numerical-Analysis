#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <cmath> // For norm calculation

class Complex {
public:
    double real, img;

    // Constructors
    Complex();
    Complex(double r, double i);

    // Basic operations
    Complex add(const Complex& other);
    Complex sub(const Complex& other);
    Complex mult(const Complex& other);
    Complex conjugate();
    double norm();

    // Display function
    void display();
};

#endif
