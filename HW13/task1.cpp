#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#define INF INT_MAX
using namespace std;

struct Edge {
	int a, b, c, f, edge;
};

int pushFlow(int v, int t ,int curflow, std::vector<std::vector<int>> &graph,
			 std::vector<bool> &used, std::vector<Edge> &edges) {
	if (v == t) {
		return curflow;
	}
//	used[v] = true;
	for (int i = 0; i < edges.size(); i+=2) {
		if (edges[i].f < edges[i].c) {
//			std::min(curflow,4);
			int nextflow = std::min(curflow, edges[i].c - edges[i].f);
			int delta = pushFlow(edges[i].b, t, nextflow, graph, used, edges);
			if (delta > 0) {
				edges[i+1].f -= delta;
				edges[i].f += delta;
				return delta;
			}

		}
	}
	return 0;
}

//int dfs(int u, int t ,int curflow, std::vector<std::vector<int>> &graph,
//		std::vector<bool> &used, std::vector<Edge> &edges,
//		std::vector<int> d, std::vector<int> p) {
//	if (u == t || curflow == 0) {
//		return curflow;
//	}
//	for (; p[u] < graph[u].size(); ++p[u]) {
//		int id = graph[u][p[u]];
//		int v = edges[id].b;
//		if (d[v] == d[u] + 1) {
//			int pushed = dfs(v, t, std::min(curflow, edges[id].c - edges[id].f), graph, used, edges, d, p);
//			if (pushed) {
//				edges[id].f += pushed;
//				edges[id ^ 1].f -= pushed;
//				return pushed;
//			}
//		}
//	}
//	return 0;
//}
int main() {
	int n, m, s, t;
	std::cin >> n >> m;
	std::vector<std::vector<int>> graph(n, std::vector<int>());
	std::vector<Edge> edges;
	std::vector<int> d(n), p(n);
	std::vector<bool> used;
	long long ans = 0;
	s = 0;
	t = n - 1;
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		std::cin >> a >> b >> c;
		a--;
		b--;
		graph[a].push_back(edges.size());
		edges.push_back({a, b, c, 0});
		graph[b].push_back(edges.size());
		edges.push_back({b, a, c, 0});
	}
	while (1){
		used.assign(n,false);
		int delta = pushFlow(s, t, INF, graph, used, edges);
		if (delta > 0) {
			ans += delta;
		}
		else {
			break;
		}

	}
	return 0;
}