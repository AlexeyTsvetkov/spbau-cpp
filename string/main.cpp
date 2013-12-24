#include <iostream>
#include "string.hpp"


int main(){
	string hello("Hello");
	string comma(", ");
	string world("world");

	std::cout << hello.append(comma).append(world) << std::endl;
	std::cout << string().c_str() << std::endl;
	return 0;
}