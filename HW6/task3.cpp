#include <iostream>
#include <vector>


void subseq(const std::vector<int>& arr, const int& n) {
	std::vector<int> subseq_len(n);
	std::vector<int> pred(n);
	std::vector<int> subseq;
	subseq_len[0] = 1;
	for (int i = 1; i < n; i++) {
		subseq_len[i] = 1;
		pred[i] = i;
		for (int j = 0; j < i; j++) {
			if (arr[j] < arr[i] && subseq_len[j] + 1 > subseq_len[i]) {
				subseq_len[i] = subseq_len[j] + 1;
				pred[i] = j;
			}
		}
	}
	int max_el = 0;
	int max_idx = 0;
	for (int i = 0; i < n; i++) {
		if (subseq_len[i] > max_el) {
			max_el = subseq_len[i];
			max_idx = i;
		}
	}
	int idx = max_idx;
	subseq.push_back(arr[idx]);
	while (idx > 0 and pred[idx] != idx) {
		subseq.push_back(arr[pred[idx]]);
		idx = pred[idx];
	}
	std::cout << max_el << "\n";
	for (int i = subseq.size() - 1; i >= 0; i--) {
		std::cout << subseq[i] << ' ';
	}
}


int main() {
	int n;
	std::cin >> n;
	std::vector<int> v_arr(n);
	for (int i = 0; i < n; i++) {
		std::cin >> v_arr[i];
	}
	subseq(v_arr, n);
	return 0;
}