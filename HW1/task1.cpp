#include 	<iostream>
#include 	<vector>

int main()
{
	int count;

	std::cin >> count;
	std::vector <int> v_n1(count);
	std::vector <int> v_n2(count);
	for (int i = 0; i < count; i++)
	{
		std::cin >> v_n1[i];
		std::cin >> v_n2[i];
	}
	for (int i = 0; i < count; i++)
	{
		std::cout << v_n1[i] + v_n2[i] << std::endl;
	}
	return 0;
}