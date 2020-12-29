#include <bits/stdc++.h>

struct Node {
	int v, u, w;
	explicit Node(int v = 0, int u = 0, int w = 0) : v(v), u(u), w(w) {}
};

int find_set(int v, std::vector<int> &parent) {
	if (v == parent[v])
		return v;
	return parent[v] = find_set(parent[v], parent);
}

void union_sets(int a, int b, std::vector<int> &parent, std::vector<int> &rank) {
	a = find_set(a, parent);
	b = find_set(b, parent);
	if (a != b) {
		if (rank[a] < rank[b])
			std::swap(a, b);
		parent[b] = a;
		if (rank[a] == rank[b])
			rank[a]++;
	}
}


int main() {
	int n, m;
	long long int cost;
	std::cin >> n >> m;
	std::vector<Node> graph(m);
	std::vector<int> parent(n), rank(n,0);
	for (size_t i = 0; i < m; ++i) {
		int b, e, w;
		std::cin >> b >> e >> w;
		graph[i] = Node(--b, --e, w);
	}
	for (int i=0; i < parent.size(); i++) {
		parent[i] = i;
	}
	sort(graph.begin(), graph.end(), [](Node a, Node b) { return a.w < b.w; });
	cost = 0;
	for (auto edge : graph) {
		if (find_set(edge.u, parent) != find_set(edge.v, parent)) {
			union_sets(edge.v, edge.u, parent, rank);
			cost += edge.w;
		}
	}
	std::cout << cost << std::endl;
	return 0;
}