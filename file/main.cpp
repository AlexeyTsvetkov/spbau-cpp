#include <iostream>
#include <string>
#include "file.hpp"

int main() {
  file input("input.txt", file::open_mode::Read);
  file output("output.txt", file::open_mode::Write);

  std::string line;
  std::string word;
  char c;
  long l;
  unsigned long ul;
  double d;

  input.readline(line);
  input.read(c);
  input.read(word);
  input.read(l);
  input.read(ul);
  input.read(d);
  
  output.write(line); 
  output.write(c);
  output.write(' ');
  output.write(word);   
  output.write(' ');
  output.write(l);
  output.write(' ');
  output.write(ul);
  output.write(' ');
  output.write(d);

  return 0;
}