#include "types.h"
#include <iostream>

int main(int argc, char const *argv[])
{

	Float64x4 a = {1.0,2.0,3.0,4.0};

	
	// std::cout << (double)a.value << std::endl;

	// double array[4] = {1.0,2.0,3.0,4.0};
	// std::initializer_list<double> list = {1.0,2.0,3.0,4.0};

	std::cout << (double)a[1] << std::endl;

	return 0;
}