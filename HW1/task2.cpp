#include 	<iostream>
#include 	<vector>

int main()
{
	int count;
	
	std::cin >> count;
	std::vector <int> v_lst(count);
	for (int i = 0; i < count; i++)
	{
		std::cin >> v_lst[i];
	}
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			if (v_lst[i] > v_lst[j])
			{
				std::swap(v_lst[i],v_lst[j]);
			}
		}
	}
	for (int i = 0; i < count; i++)
	{
		std::cout << v_lst[i] << " ";
	}
	return 0;
}