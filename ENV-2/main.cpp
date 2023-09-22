//#include <iostream>
//#include <vector>
#include "complexNumbers.h"

int main() {
  std::vector<Complex> v;
  v.push_back(Complex(6.0,7.5));
  v.push_back(Complex(2.7,1.3));
  v.push_back(Complex(4.0,1.1));
  v.push_back(Complex(7.1,9.7));
  v.push_back(Complex(1.3,5.0));
  
  sort(v);
  for(std::size_t i=0; i<v.size(); ++i){
   std::cout<<v[i].Abs()<<std::endl;}
  

}