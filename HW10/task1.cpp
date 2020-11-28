#include <iostream>
#include <vector>

void dfs(int v, std::vector<int> &used, std::vector<std::vector<int>> &graph, int &cnt) {
	used[v] = cnt;
	for (auto u : graph[v]) {
		if (!used[u]) {
			dfs(u, used, graph, cnt);
		}
	}
}

void find_comps(std::vector<int> &used, std::vector<std::vector<int>> &graph) {
	int cnt;
	cnt = 0;
	for (int i = 0; i < used.size(); ++i)
		if (!used[i]) {
			cnt++;
			dfs(i, used, graph, cnt);
		}
	std::cout << cnt << "\n";
	for (int i : used) {
		std::cout << i << " ";
	}
}

int main() {
	int n, m;
	int v, u;
	std::cin >> n >> m;
	std::vector<int> used(n, 0);
	std::vector<std::vector<int>> graph(n);
	while (m--) {
		std::cin >> v >> u;
		v--;
		u--;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	find_comps(used, graph);
	return 0;
}