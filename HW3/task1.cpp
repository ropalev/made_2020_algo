#include <vector>
#include <iostream>

long long int bin_search(std::vector <long long int> &nums, int value) {
  long long int left, right, mid, res;

  if (nums.back() < value) {
	return nums.back();
  }
  else if (nums.front() > value) {
    return nums.front();
  }
  left = 0;
  right = nums.size() - 1;
  while (left <= right) {
    mid = left + (right - left) / 2;
    if (nums[mid] == value) {
      right == mid;
      break;
    }
    else if (nums[mid] >= value) {
      right = mid - 1;
    }
    else {
      left = mid + 1;
    }
  }
  if (right >= 0 && left <= nums.size() - 1) {
    if (abs(value - nums[left]) < abs(value - nums[right])) {
      res = nums[left];
    }
    else {
      res = nums[right];
    }
  }
  return res;
}

int main() {
  int n, k;

  std::cin >> n;
  std::cin >> k;
  std::vector <long long int> v_nums1(n);
  std::vector <long long int> v_nums2(k);
  for (int i = 0; i < n; i++) {
    std::cin >> v_nums1[i];
  }
  for (int i = 0; i < k; i++) {
	std::cin >> v_nums2[i];
  }
  for (int i = 0; i < k; i++) {
    std::cout << bin_search(v_nums1, v_nums2[i]) << "\n";
  }
  return (0);
}
