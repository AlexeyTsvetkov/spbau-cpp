#include <cstddef>

#include <iostream>

#include "stack.hpp"

int main(){
  Stack<size_t> st;
  
  const size_t count = 5;
  for(size_t i = 0; i < count; ++i) {
    size_t value = (i+1)*10;
    st.push(value);
    std::cout << "push: " << value << std::endl;
  }

  std::cout << std::endl << "stack size: " << st.size() << std::endl << std::endl;

  while(!st.empty()) {
    std::cout << "pop: " << st.top() << std::endl;
    st.pop();
  }

	return 0;
}