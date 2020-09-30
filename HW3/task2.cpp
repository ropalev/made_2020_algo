#include <vector>
#include <iostream>


int lower_bound(std::vector <int> &nums, int value) {
  int left, right, mid;

  left = -1;
  right = nums.size();
  while (left < right - 1) {
	mid = left + (right -left) / 2;
	if (nums[mid] >= value) {
	  right = mid;
	}
	else {
	  left = mid;
	}
  }
  return (right);
}

int upper_bound(std::vector <int> &nums, int value) {
  int left, right, mid;

  left = -1;
  right = nums.size();
  while (left < right - 1) {
    mid = left + (right -left) / 2;
    if (nums[mid] > value) {
      right = mid;
    }
    else {
      left = mid;
    }
  }
  return (right);
}

void quick_sort(std::vector <int> &lst, int a, int b)
{
  int l, r, piv;

  l = a;
  r = b;
  piv = lst[r - (r - l) / 2];
  while (l < r) {
	while (lst[l] < piv) {
	  l++;
	}
	while (lst[r] > piv) {
	  r--;
	}
	if (l <= r)	{
	  std::swap(lst[l], lst[r]);
	  l++;
	  r--;
	}
  }
  if (a < r) {
	quick_sort(lst, a, r);
  }
  if (b > l) {
	quick_sort(lst, l, b);
  }
}

int main()
{
  int len, n, start, end;

  std::cin >> len;
  std::vector <int> v_lst(len);
  for (int i = 0; i < len; i++) {
	std::cin >> v_lst[i];
  }
  quick_sort(v_lst, 0, v_lst.size() - 1);
  std::cin >> n;
  std::vector <int> v_result(n);
  for (int i = 0; i < n; i++) {
    std::cin >> start;
    std::cin >> end;
    v_result[i] = (upper_bound(v_lst, end) - lower_bound(v_lst, start));
  }
  for (int i = 0; i < n; i++) {
    std::cout << v_result[i] << " ";
  }
  return 0;
}