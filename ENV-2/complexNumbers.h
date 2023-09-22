//#ifndef COMPLEXNUM_H
//#define COMPLEXNUM_H
#include<iostream>
#include<vector>
class Complex{
private:
double a;
double b;
public:
Complex();
Complex(double, double);
Complex operator+(const Complex&);
Complex operator-(const Complex&);
Complex operator*(const Complex&);
double Abs();
};
void sort(std::vector<Complex>&);
//#endif