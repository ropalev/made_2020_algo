#include <bits/stdc++.h>
#include <iostream>
#define INF INT_MAX

int main() {
	int n, m;
	std::cin >> n >> m;
	int u, v, w;
	std::vector<std::vector<std::pair<int, int>>> graph(n);
	for (int i = 0; i < m; i++) {
		std::cin >> u >> v >> w;
		u--;
		v--;
		graph[u].push_back({v, w});
		graph[v].push_back({u, w});
	}
	std::vector<long long int> distances(n, INF);
	distances[0] = 0;
	std::set<std::pair<long long int, int>> queue;
	queue.insert({0, 0});
	while (!queue.empty()) {
		auto top = queue.begin();
		int u = top->second;
		queue.erase(top);
		for (auto next : graph[u]) {
			int v = next.first;
			int len = next.second;
			if (distances[v] > distances[u] + len) {
				if (queue.find({distances[v], v}) != queue.end()) {
					queue.erase(queue.find({distances[v], v}));
				}
				distances[v] = distances[u] + len;
				queue.insert({distances[v], v});
			}
		}
	}
	for (auto d : distances) {
		std::cout << d << " ";
	}
	return 0;
}
