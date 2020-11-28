#include <algorithm>
#include <iostream>
#include <vector>

bool cyclic(int v, int &cycle_st, std::vector<int> *graph, std::vector<int> &color) {
	color[v] = 1;
	for (size_t i = 0; i < graph[v].size(); ++i) {
		int to = graph[v][i];
		if (color[to] == 0) {
			if (cyclic(to, cycle_st, graph, color)) {
				return true;
			}
		}
		else if (color[to] == 1) {
			cycle_st = to;
			return true;
		}
	}
	color[v] = 2;
	return false;
}

void dfs(int v, std::vector<int> *graph, std::vector<bool> &used, std::vector<int> &answer) {
	used[v] = true;
	for (int i = 0; i < graph[v].size(); i++) {
		int to = graph[v][i];
		if (!used[to]) {
			dfs(to, graph, used, answer);
		}
	}
	answer.push_back(v + 1);
}

void topological_sort(int n, std::vector<int> *graph, std::vector<bool> &used, std::vector<int> &answer) {
	for (int i = 0; i < n; i++) {
		used[i] = false;
	}
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i, graph, used, answer);
		}
	}
	reverse(answer.begin(), answer.end());
}

int main() {
	int n, m;
	std::cin >> n >> m;
	int a, b;
	std::vector<int> graph[n];
	std::vector<bool> used(n, false);
	std::vector<int> answer;
	std::vector<int> color(n, 0);
	int cycle_st = -1;
	for (int i = 0; i < m; i++) {
		std::cin >> a >> b;
		a--;
		b--;
		graph[a].push_back(b);
	}
	for (int i = 0; i < n; i++) {
		if (cyclic(i, cycle_st, graph, color)) {
			break;
		}
	}
	if (cycle_st != -1) {
		std::cout << "-1";
	}
	else {
		topological_sort(n, graph, used, answer);
		for (int i: answer) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}