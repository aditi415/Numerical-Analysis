#include<iostream>
 class cmplx     
{
 public:
   double real;
   double img;
   
public :
    cmplx();           //default constructor
   void display();
 cmplx add(cmplx y);       //function call 
 cmplx sub(cmplx y);       //function call 
 cmplx mult(cmplx y);

};
