#include <bits/stdc++.h>
#define INF INT_MAX

double calc_distance(int v, int u, std::vector<std::pair<int, int>> &vertexs) {
	std::pair<int, int> v1 = vertexs[v];
	std::pair<int, int> v2 = vertexs[u];
	return sqrt((v2.first - v1.first) * (v2.first - v1.first) + (v2.second - v1.second) * (v2.second - v1.second));
}

int main() {
	int n, m;
	double distance;
	std::cin >> n;
	std::vector<std::pair<int, int>> vertexs;
	std::vector<bool> used(n, false);
	std::vector<double> edges(n, INF);
	std::vector<double> used_edges(n, -1);
	m = 0;
	while (m++ < n) {
		int x, y;
		std::cin >> x >> y;
		vertexs.emplace_back(std::make_pair(x, y));
	}
	distance = 0;
	edges[0] = 0;
	for (int i = 0; i < n; i++) {
		int v = -1;
		for (int j = 0; j < n; j++) {
			if ((v == -1 || edges[v] > edges[j]) && !used[j]) {
				v = j;
			}
		}
		used[v] = true;
		if (used_edges[v] != -1) {
			distance += (calc_distance(v, used_edges[v], vertexs));
		}
		for (int u = 0; u < n; u++) {
			double dist = calc_distance(v, u, vertexs);
			if (dist < edges[u]) {
				edges[u] = dist;
				used_edges[u] = v;
			}
		}
	}
	std::cout << std::setprecision(11) << distance << std::endl;
	return 0;
}
