#include <iostream>

int ComputeMultiples(int max);

int main()
{
	std::cout << "EX 1: \nSum of multiples of 5 or 3 : " << ComputeMultiples(1000) << "\n";
	std::cin.get();
}

int ComputeMultiples(const int max)
{
	int sum = 0;
	for (int i = 0; i < max; ++i)
	{
		if (i % 3 == 0 || i % 5 == 0)
		{
			sum += i;
		}
	}

	return sum;
}