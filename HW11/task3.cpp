#include <bits/stdc++.h>
#include <iostream>
#include <tuple>

#define INF INT_MAX
#define NOEDGE 10000000

int main() {
	int n, z, w;
	std::cin >> n;
	std::vector<std::tuple<int, int, int>> edges;
	std::vector<int> distances(n, INF);
	std::vector<int> p(n, -1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> w;
			if (w != NOEDGE) {
				edges.emplace_back(std::make_tuple(i, j, w));
			}
		}
	}
	distances[0] = 0;
	for (int i = 0; i < n; i++) {
		z = -1;
		for (auto &edge : edges) {
			int u = std::get<0>(edge);
			int v = std::get<1>(edge);
			int w = std::get<2>(edge);
			if (distances[v] > distances[u] + w) {
				distances[v] = std::max(-INF, distances[u] + w);
				p[v] = u;
				z = v;
			}
		}
	}
	if (z != -1) {
		std::vector<int> circuit;
		int y = z;
		for (int i = 0; i < n; i++) {
			y = p[y];
		}
		for (int cur = y;; cur = p[cur]) {
			circuit.emplace_back(cur);
			if (cur == y && circuit.size() > 1) {
				break;
			}
		}
		std::cout << "YES" << "\n";
		std::cout << circuit.size() - 1 << "\n";
		reverse(circuit.begin(), circuit.end());
		circuit.erase(circuit.begin());
		for (auto i : circuit) {
			std::cout << i + 1 << " ";
		}
	}
	else {
		std::cout << "NO";
	}
	return 0;
}