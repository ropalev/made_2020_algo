#include <iostream>
#include <set>
#include <vector>

struct vertex {
	int used, color;
	std::vector<int> graph, graph_tr;
};

void dfs_g(int v, std::vector<vertex> &components, std::vector<int> &list) {
	components[v].used = 1;
	for (int i = 0; i < components[v].graph.size(); i++) {
		if (components[components[v].graph[i]].used != 1) {
			dfs_g(components[v].graph[i], components, list);
		}
	}
	list.push_back(v);
}

void dfs_tr(int v, int color, std::vector<vertex> &components) {
	components[v].used = 2;
	components[v].color = color;
	for (int i = 0; i < components[v].graph_tr.size(); i++) {
		if (components[components[v].graph_tr[i]].used != 2) {
			dfs_tr(components[v].graph_tr[i], color, components);
		}
	}
}

int main() {
	int n, m;
	int a, b;
	int color, answer;
	std::cin >> n >> m;
	std::vector<int> list(n);
	std::vector<vertex> components(n);
	std::set<int> ribs[n];
	for (int i = 0; i < m; i++) {
		std::cin >> a >> b;
		a--;
		b--;
		components[a].graph.push_back(b);
		components[b].graph_tr.push_back(a);
	}
	for (int i = 0; i < n; i++) {
		if (components[i].used != 1) {
			dfs_g(i, components, list);
		}
	}
	color = 0;
	for (int i = list.size() - 1; i >= 0; i--) {
		if (components[list[i]].used != 2) {
			dfs_tr(list[i], color, components);
			color++;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < components[i].graph.size(); j++) {
			if (components[i].color != components[components[i].graph[j]].color) {
				ribs[components[i].color].insert(components[components[i].graph[j]].color);
			}
		}
	}
	answer = 0;
	for (int i = 0; i < n; i++) {
		answer += ribs[i].size();
	}
	std::cout << answer;
	return 0;
}