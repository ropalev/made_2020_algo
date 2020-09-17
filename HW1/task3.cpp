#include 	<iostream>
#include 	<vector>

static std::vector <int> merge_sort(std::vector <int> v_lst)
{
	int mid, start, end;
	std::vector <int> v_merge_lst;

	if (v_lst.size() == 1)
		return v_lst;
	start = 0;
	end = v_lst.size() - 1;
	mid = end - (end - start) / 2;
	std::vector <int> v_left_lst(mid - start);
	std::vector <int> v_right_lst(end - mid + 1);
	copy(v_lst.begin(), v_lst.begin() + mid, v_left_lst.begin());
	copy(v_lst.begin() + mid, v_lst.end(), v_right_lst.begin());
	v_left_lst = merge_sort(v_left_lst);
	v_right_lst = merge_sort(v_right_lst);
	while (v_left_lst.size() != 0 && v_right_lst.size() != 0)
	{
		if (v_left_lst[0] >= v_right_lst[0])
		{
			v_merge_lst.push_back(v_right_lst[0]);
			v_right_lst.erase(v_right_lst.begin());
		}
		else
		{
			v_merge_lst.push_back(v_left_lst[0]);
			v_left_lst.erase(v_left_lst.begin());
		}
	}
	if (v_left_lst.size() == 0)
	{
		v_merge_lst.insert(v_merge_lst.end(), v_right_lst.begin(),
						   v_right_lst.end());
	}
	else
	{
		v_merge_lst.insert(v_merge_lst.end(), v_left_lst.begin(),
						   v_left_lst.end());
	}
	return v_merge_lst;
}

int main()
{
	int count;

	std::cin >> count;
	std::vector <int> v_lst(count);
	for (int i = 0; i < count; i++)
	{
		std::cin >> v_lst[i];
	}
	v_lst = merge_sort(v_lst);
	for (int i = 0; i < count; i++)
	{
		std::cout << v_lst[i] << " ";
	}
	return 0;
}
