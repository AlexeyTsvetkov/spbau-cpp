#include <cstddef>

#include <iostream>

#include "vector.hpp"

int main(){
  Vector<int> vect;
  
  const int count = 20;
  for(int i = 0; i < count; ++i) {
    int value = (i+1);
    vect.push_back(value);
    std::cout << "SET vect[" << i << "]=" << value << std::endl;
  }

  std::cout << std::endl << "vector size: " << vect.size() << std::endl << std::endl;

  for(size_t i = 0; i < vect.size(); ++i) {
    std::cout << "GET vect[" << i << "]=" << vect[i] << std::endl;
  }

	return 0;
}