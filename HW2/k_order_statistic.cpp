#include <iostream>
#include <vector>


int partition(std::vector <int> &nums, int l, int r) {
  int b = l;
  int pivot = nums[r - (r - l) / 2];
  while (l < r) {
	while (l < r && nums[r] >= pivot) {
	  r--;
	}
	while (l < r && nums[l] <= pivot) {
	  l++;
	}
	std::swap(nums[l], nums[r]);
  }
  std::swap(nums[l], nums[b]);
  return l;
}

void quickSelect(std::vector <int> &nums, int l, int r, int k) {
  if (l >= r) {
	return ;
  }
  int mid = partition(nums, l, r);
  if (mid - l + 1 == k) {
	return ;
  } 
  else if (mid - l + 1 < k) {
	quickSelect(nums, mid + 1, r, k - (mid - l + 1));
  } 
  else {
	quickSelect(nums, l, mid - 1, k);
  }
}

int main()
{
  int count, start, end, k, m;

  std::cin >> count;
  std::vector <int> v_lst(count);
  for (int i = 0; i < count; i++)
  {
	std::cin >> v_lst[i];
  }
  std::cin >> m;
  std::vector <int> v_res(m);
  for (int i = 0; i < m; i++) {
	std::cin >> start;
	std::cin >> end;
	std::cin >> k;
	quickSelect(v_lst, 0, v_lst.size() - 1, start + k - 2);
	v_res[i] = v_lst[start + k - 2];
  }
  for (int i = 0; i < m; i++) {
	std::cout << v_res[i] << "\n";
  }
  return 0;
}
