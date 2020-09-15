#include 	<iostream>
#include 	<vector>

static std::vector<int>	merge_sort(std::vector<int> lst) {
	int					mid, start,end;
	std::vector<int>	left_lst, right_lst;
	std::vector<int>	merge_lst;

	if (lst.size() == 1)
		return lst;
	start = 0;
	end = lst.size() - 1;
	mid = end - (end - start) / 2;
	left_lst.resize(mid - start);
	right_lst.resize(end - mid + 1);
	copy(lst.begin(), lst.begin() + mid, left_lst.begin());
	copy(lst.begin() + mid, lst.end(), right_lst.begin());
	left_lst = merge_sort(left_lst);
	right_lst = merge_sort(right_lst);
	while (left_lst.size() != 0 && right_lst.size() != 0) {
		if (left_lst[0] >= right_lst[0]) {
			merge_lst.push_back(right_lst[0]);
			right_lst.erase(right_lst.begin());
		} else {
			merge_lst.push_back(left_lst[0]);
			left_lst.erase(left_lst.begin());
		}
	}
	if (left_lst.size() == 0)
		merge_lst.insert(merge_lst.end(), right_lst.begin(), right_lst.end());
	else
		merge_lst.insert(merge_lst.end(), left_lst.begin(), left_lst.end());
	return (merge_lst);
}

int 					main()
{
	int					count;
	std::vector<int> 	lst;

	std::cin >> count;
	lst.resize(count);
	for (int i = 0; i < count; i++){
		std::cin >> lst[i];
	}
	lst = merge_sort(lst);
	for (int i = 0; i < count; i++){
		std::cout << lst[i] << " ";
	}
	return (0);
}