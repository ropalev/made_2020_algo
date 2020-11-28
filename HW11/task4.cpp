#include <bits/stdc++.h>

#define INF LLONG_MAX
#define M_INF LLONG_MIN

void dfs(int v, std::vector<std::vector<int>> &graph, std::vector<bool> &used) {
	used[v] = true;
	for (int i = 0; i < graph[v].size(); i++) {
		int to = graph[v][i];
		if (!used[to]) {
			dfs(to, graph, used);
		}
	}
}

int main() {
	int n, m, s;
	std::cin >> n >> m >> s;
	std::vector<std::tuple<int, int, long long int>> edges;
	std::vector<long long int> dist(n, INF);
	std::vector<std::vector<int>> graph(n);
	std::vector<bool> used(n, false);
	for (int i = 0; i < m; i++) {
		int u, v;
		long long int w;
		std::cin >> u >> v >> w;
		u--;
		v--;
		graph[u].push_back(v);
		edges.emplace_back(std::make_tuple(u, v, w));
	}
	s--;
	dist[s] = 0;
	for (int i = 0; i < n; i++) {
		int u, v;
		long long int w;
		for (auto & edge : edges) {
			u = std::get<0>(edge);
			v = std::get<1>(edge);
			w = std::get<2>(edge);
			if ((dist[u] < INF) && (dist[v] > dist[u] + w)) {
				dist[v] = std::max(M_INF, dist[u] + w);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		int u, v;
		long long int w;
		for (auto & edge : edges) {
			u = std::get<0>(edge);
			v = std::get<1>(edge);
			w = std::get<2>(edge);
			if ((dist[u] < INF) && (dist[v] > dist[u] + w) && !used[v]) {
				dfs(v, graph, used);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (dist[i] == INF) {
			std::cout << "*\n";
		}
		else if (used[i]) {
			std::cout << "-\n";
		}
		else {
			std::cout << dist[i] << "\n";
		}
	}
	return 0;
}