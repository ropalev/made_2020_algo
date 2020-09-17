#include	<iostream>
#include 	<vector>

void quick_sort(std::vector <int> &lst, int a, int b)
{
	int l, r, piv;

	l = a;
	r = b;
	piv = lst[r - (r - l) / 2];
	while (l < r)
	{
		while (lst[l] < piv)
		{
			l++;
		}
		while (lst[r] > piv)
		{
			r--;
		}
		if (l <= r)
		{
			std::swap(lst[l], lst[r]);
			l++;
			r--;
		}
	}
	if (a < r)
	{
		quick_sort(lst, a, r);
	}
	if (b > l)
	{
		quick_sort(lst, l, b);
	}
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
	quick_sort(v_lst, 0 , v_lst.size() - 1);
	for (int i = 0; i < count; i++)
	{
		std::cout << v_lst[i] << " ";
	}
	return 0;
}