#include <iostream>
#include <string>
#include <vector>

class FenwickTree {
private:
	std::vector<long long int> bit;
	int n;

public:
	explicit FenwickTree(int n) {
		this->n = n;
		this->bit.assign(this->n, 0);
	}

	explicit FenwickTree(std::vector<long long int> a) : FenwickTree(a.size()) {
		for (size_t i = 0; i < a.size(); i++) {
			add(i, a[i]);
		}
	}

	long long int sum(int r) {
		long long int res = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1) {
			res += this->bit[r];
		}
		return res;
	}

	long long int sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	void add(int idx, long long int delta) {
		for (; idx < this->n; idx = idx | (idx + 1)) {
			this->bit[idx] += delta;
		}
	}
};

int main() {
	int n;
	std::cin >> n;
	std::vector<long long int> v_arr(n);
	for (int i = 0; i < n; i++) {
		std::cin >> v_arr[i];
	}
	FenwickTree f_tree = FenwickTree(v_arr);
	std::string str;
	int li, rx;
	while (std::cin >> str) {
		std::cin >> li >> rx;
		if (str == "sum") {
			if (li == 1) {
				std::cout << f_tree.sum(rx - 1);
			} else {
				std::cout << f_tree.sum(li - 1, rx - 1);
			}
		} else if (str == "set") {
			f_tree.add(li - 1, rx - v_arr[li - 1]);
			v_arr[li - 1] = rx;
		}
		if (str == "sum") {
			std::cout << "\n";
		}
	}
	return 0;
}