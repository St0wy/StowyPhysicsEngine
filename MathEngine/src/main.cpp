#include <iostream>

#include "Vector2.hpp"

int main()
{
	Vector2 vec = { 1, 2 };
	std::cout << vec.ToString() << "\n";
	std::cout << vec.Magnitude() << "\n";

	vec = vec.Normalized();

	std::cout << vec.ToString() << "\n";
	std::cout << vec.Magnitude() << "\n";

	std::cin.get();
	return EXIT_SUCCESS;
}