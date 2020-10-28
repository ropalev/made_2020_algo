#include <iostream>
#include <vector>
#include <cmath>

int main() {
	unsigned int n, m, a;
	std::cin >> n >> m >> a;
	std::vector<unsigned int> v_a(n);

	std::vector<std::vector<unsigned  int>> v_matmin(n , std::vector<unsigned  int> (n, 0));
	for (auto & i: v_a) {
		i = a;
		a = (23 * a + 21563) % 16714589;
	}

	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (i == j) {
				v_matmin[i][j] = v_a[j];
			} else {
				v_matmin[i][j] = std::min(v_matmin[i][j - 1], v_a[j]);
			}
		}
	}
	unsigned int u, v, res;
	int idx_min, idx_max;
	std::cin >> u >> v;
	for (int i = 0; i < m; i++) {
		idx_min = std::min(u,v) - 1;
		idx_max = std::max(u,v) - 1;
		res = v_matmin[idx_min][idx_max];
		if ( i == m - 1) {
			std::cout << u << " " << v << " " << res << "\n";
		}
		u = ((17 * u + 751 + res + 2 * (i + 1)) % n) + 1;
		v = ((13 * v + 593 + res + 5 * (i + 1)) % n) + 1;
	}
	return (0);
}