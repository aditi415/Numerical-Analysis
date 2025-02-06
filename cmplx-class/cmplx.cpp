#include "complex.hpp"

// Default Constructor
Complex::Complex() : real(0), img(0) {}

// Parameterized Constructor
Complex::Complex(double r, double i) : real(r), img(i) {}

// Function to add two complex numbers
Complex Complex::add(const Complex& other) {
    return Complex(real + other.real, img + other.img);
}

// Function to subtract two complex numbers
Complex Complex::sub(const Complex& other) {
    return Complex(real - other.real, img - other.img);
}

// Function to multiply two complex numbers
Complex Complex::mult(const Complex& other) {
    return Complex((real * other.real) - (img * other.img), (real * other.img) + (img * other.real));
}

// Function to return the complex conjugate
Complex Complex::conjugate() {
    return Complex(real, -img);
}

// Function to return the norm (magnitude squared)
double Complex::norm() {
    return (real * real) + (img * img);
}

// Function to display the complex number
void Complex::display() {
    std::cout << real;
    if (img >= 0) {
        std::cout << " + " << img << "i" << std::endl;
    } else {
        std::cout << " - " << -img << "i" << std::endl;
    }
}

