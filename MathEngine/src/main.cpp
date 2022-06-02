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

	const Vector2 vec2 = {2, 1};

	std::cout << vec2.ToString() << "\n";
	std::cout << (vec + vec2).ToString() << "\n";

	const Vector2 test{2, 2};

	std::cout << "Division" << "\n" << (vec2 / test).ToString() << "\n";

	std::cin.get();
}