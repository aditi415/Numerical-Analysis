#include "cmplx.hpp"
using namespace std;

cmplx::cmplx()    //default constructor for complex class
{
    real=0;
    img=0;
  cout<< "Default Constructor\n ";
}

void cmplx::display()            //prints cmplx no. in 2 forms
{
cout << real << "+" << img <<"i"<<std::endl;
cout << real << "-" << img <<"i"<<std::endl;
cout << real << "*" << img <<"i"<<std::endl;
}

cmplx cmplx::add (cmplx y)       
{
    return cmplx(real + y.real, img + y.img);
}

cmplx cmplx::sub (cmplx y)        
{
   return cmplx(real - y.real, img - y.img);
}

cmplx cmplx::mult (cmplx y)        
{
  return cmplx((real * y.real)-(img * y.img),(real * y.img) + (img * y.real));
}

cmplx cmplx::conj(){
    return cmplx(real,-img);
}
