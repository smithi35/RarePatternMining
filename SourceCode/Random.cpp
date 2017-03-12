#include <iostream>
#include <cstdlib>

int main()
{
	int i;
	for (i = 0; i < 1000; i++)
	{
		std::cout << rand() % 5 << std::endl;
	}
}
