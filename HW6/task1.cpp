#include <iostream>
#include <vector>
#include <algorithm>
#include <set>


void jump(std::vector<int>& arr, const int& n, const int& k) {
	std::set<int> s_jumps;
	int max_money;
	int max_jumps = 0;
	int start_position;
	for (int i = 1; i < n; i++) {
		max_money = arr[i - 1];
		start_position = std::max(0, i - k);
		for (int j = start_position; j < i; j++) {
			if (arr[j] >= max_money) {
				max_money = arr[j];
				max_jumps = j;
			}
		}
		s_jumps.insert(max_jumps + 1);
		arr[i] += max_money;
	}
	s_jumps.insert(n);
	std::cout << arr[n - 1]<< '\n' << s_jumps.size() - 1 << '\n';
	for (auto el: s_jumps) {
		std::cout << el << ' ';
	}
}


int main() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> v_coin(n);
	for (size_t i = 1; i < n - 1; i++) {
		std::cin >> v_coin[i];
	}
	jump(v_coin, n, k);
	return 0;
}