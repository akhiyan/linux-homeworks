
#include <cmath>
#include "complexNumbers.h"

Complex::Complex():a(0),b(0){}
Complex::Complex(double _a, double _b):a(_a), b(_b){}
Complex Complex::operator+(const Complex& c){
  Complex t;
  t.a=a+c.a;
  t.b=b+c.b;
  return t;
}
Complex Complex::operator-(const Complex& c){
  Complex t;
  t.a=a-c.a;
  t.b=b-c.b;
  return t;
}
Complex Complex::operator*(const Complex& c){
  Complex t;
  t.a=a*c.a;
  t.b=b*c.b;
  return t;
}

double Complex::Abs(){
  double abs=std::sqrt((a*a)+(b*b));
  return abs;
}
