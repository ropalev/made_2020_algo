#include 	<iostream>
#include 	<vector>

int 		main()
{
	int					count;
	std::vector<int> 	n1;
	std::vector<int> 	n2;

	std::cin >> count;
	n1.resize(count);
	n2.resize(count);
	for (int i = 0; i < count; i++){
		std::cin >> n1[i];
		std::cin >> n2[i];
	}
	for (int i = 0; i < count; i++){
		std::cout << n1[i] + n2[i] << std::endl;
	}
}