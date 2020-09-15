#include 	<iostream>
#include 	<vector>

int 					main()
{
	int					count;
	int 				tmp;
	std::vector<int> 	lst;

	std::cin >> count;
	lst.resize(count);
	for (int i = 0; i < count; i++){
		std::cin >> lst[i];
	}
	for (int i = 0; i < count; i++){
		for (int j = i + 1; j < count; j++){
			if (lst[i] > lst[j]){
				tmp = lst[i];
				lst[i] = lst[j];
				lst[j] = tmp;
			}
		}
	}
	for (int i = 0; i < count; i++){
		std::cout << lst[i] << " ";
	}
	return (0);
}