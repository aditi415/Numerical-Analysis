#include <iostream>
#include "cmplx.hpp"

int main()
{
    cmplx a, b, result;
 
    a.real = 3;
    a.img = 4;

    b.real = 1;
    b.img = 2;
    
    a.display();       //dispaly 1st cmplx no.
    b.display();       //display 2nd cmplx no.

    result = a.add(b);
    std::cout << "Addition: " << result.real << " + " << result.img << "i\n";

    result = a.sub(b);
    std::cout << "Subtraction: " << result.real << " + " << result.img << "i\n";

    result = a.mult(b);
    std::cout << "Multiplication : " << result.real << " * " << result.img << "i\n";
    
    return 0;
}
