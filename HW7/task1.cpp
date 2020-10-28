#include <iostream>
#include <vector>
#include <cmath>

#define MOD16 (int) std::pow(2, 16)
#define MOD30 (int) std::pow(2, 30)

int main() {
	unsigned int n, m, xz, ab;
	int yt, idx_min, idx_max;
	unsigned long long sum = 0;
	std::cin >> n >> xz >> yt >> ab;
	std::vector<unsigned int> v_a(n);
	std::vector<unsigned long long> v_sum(n);
	for (unsigned int& i : v_a) {
		i = ab;
		ab = (xz * ab % MOD16 + yt % MOD16) % MOD16;
	}
	std::cin >> m >> xz >> yt >> ab;
	std::vector<unsigned int> v_b(2 * m);
	std::vector<unsigned int> v_c(2 * m);
	for (unsigned int& i : v_b) {
		i = ab;
		ab = (xz * ab % MOD30 + yt % MOD30) % MOD30;
	}
	for (unsigned int i = 0; i < v_c.size(); i++) {
		v_c[i] = v_b[i] % n;
	}
	v_sum[0] = v_a[0];
	for (unsigned int i = 1; i < v_sum.size(); i++) {
		v_sum[i] = v_sum[i - 1] + v_a[i];
	}
	for (unsigned int i = 0; i < v_c.size(); i += 2) {
		idx_min = std::min(v_c[i], v_c[i + 1]);
		idx_max = std::max(v_c[i], v_c[i + 1]);
		if (!idx_min) {
			sum += v_sum[idx_max];
		} else {
			sum += v_sum[idx_max] - v_sum[idx_min - 1];
		}
	}
	std::cout << sum << std::endl;
}