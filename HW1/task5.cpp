#include 	<iostream>
#include 	<vector>

void 					quick_sort (std::vector<int> &lst, int a, int b) {
	int					l, r, tmp, piv;

	l = a;
	r = b;
	piv = lst[r -(r - l) / 2];
	while (l < r)
	{
		while (lst[l] < piv)
			l++;
		while (lst[r] > piv)
			r--;
		if (l <= r) {
			tmp = lst[l];
			lst[l] = lst[r];
			lst[r] = tmp;
			l++;
			r--;
		}
	}
	if (a < r)
		quick_sort (lst, a, r);
	if (b > l)
		quick_sort (lst, l, b);
}

int 					main() {
	int					count;
	std::vector<int> 	lst;

	std::cin >> count;
	lst.resize(count);
	for (int i = 0; i < count; i++) {
		std::cin >> lst[i];
	}
	quick_sort(lst, 0 , lst.size() - 1);
	for (int i = 0; i < count; i++) {
		std::cout << lst[i] << " ";
	}
	return (0);
}