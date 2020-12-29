//
// Created by roman on 10.12.2020.
//
#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX;


//struct Edge {
//	int a, b, c, f;
//};
//
//int dfs(int u, int flow) {
//	if (u == t || flow == 0) {
//		return flow;
//	}
//	for (; p[u] < graph[u].size(); ++p[u]) {
//		int id = graph[u][p[u]];
//		int v = edges[id].b;
//		if (d[v] == d[u] + 1) {
//			int pushed = dfs(v, std::min(flow, edges[id].c - edges[id].f));
//			if (pushed) {
//				edges[id].f += pushed;
//				edges[id ^ 1].f -= pushed;
//				return pushed;
//			}
//		}
//	}
//	return 0;
//}
//
//bool bfs() {
//	d.assign(n, INF);
//	d[s] = 0;
//	q.push(s);
//	while (!q.empty()) {
//		int u = q.front();
//		q.pop();
//		for (int i = 0; i < graph[u].size(); ++i) {
//			int id = graph[u][i];
//			int v = edges[id].b;
//
//			if (d[v] == INF && edges[id].f < edges[id].c) {
//				d[v] = d[u] + 1;
//				q.push(v);
//			}
//		}
//	}
//	return d[t] != INF;
//}
//
//int algoDinic() {
//	int flow = 0;
//	while (bfs()) {
//		p.assign(n, 0);
//		int f = dfs(s, INF);
//		while (f) {
//			flow += f;
//			f = dfs(s, INF);
//		}
//	}
//	return flow;
//}
//
//int main() {
//	int n, m, s, t;
//	std::cin >> n >> m;
//	std::vector<std::vector<int>> graph(n, std::vector<int>());
//	std::vector<Edge> edges;
//	std::vector<int> d(n), p(n), q(n);
//
//	s = 0;
//	t = n - 1;
//
//	for (int i = 0; i < m; ++i) {
//		int a, b, c;
//		std::cin >> a >> b >> c;
//		a--;
//		b--;
//		graph[a].push_back(edges.size());
//		graph[b].push_back(edges.size());
//		edges.push_back({a, b, c, 0});
//		edges.push_back({b, a, c, 0});
//	}
//	int res = algoDinic();
//	std::cout << res << "\n";
//	for (int i = 0; i < 2 * m; i += 2) {
//		std::cout << edges[i].f << "\n";
//	}
//	return 0;
//}

const int inf = 1000 * 1000 * 1000;


typedef vector<int> graf_line;
typedef vector<graf_line> graf;

typedef vector<int> vint;
typedef vector<vint> vvint;


int main() {
	int n, m;
	cin >> n >> m;
	vvint c(n, vint(n));
	vvint f(n, vint(n));
	//	for (int i=0; i<n; i++)
	//		for (int j=0; j<n; j++)
	//			cin >> c[i][j];
	//	// исток - вершина 0, сток - вершина n-1
	while (m--) {
		int u, v, cost;
		cin >> u >> v >> cost;
		u--;
		v--;
		c[u][v] = cost;
	}
	int s, tt;
	s = 0;
	tt = n - 1;
	for (;;) {

		vint from(n, -1);
		vint q(n);
		int h = 0, t = 0;
		q[t++] = 0;
		from[0] = 0;
		for (int cur; h < t;) {
			cur = q[h++];
			for (int v = 0; v < n; v++) {
				if (from[v] == -1 && c[cur][v] - f[cur][v] > 0) {
					q[t++] = v;
					from[v] = cur;
				}
			}
		}

		if (from[n - 1] == -1)
			break;
		int cf = inf;
		for (int cur = n - 1; cur != 0;) {
			int prev = from[cur];
			cf = min(cf, c[prev][cur] - f[prev][cur]);
			cur = prev;
		}

		for (int cur = n - 1; cur != 0;) {
			int prev = from[cur];
			f[prev][cur] += cf;
			f[cur][prev] -= cf;
			cur = prev;
		}
	}
	int flow = 0;
	for (int i = 0; i < n; i++)
		if (c[0][i])
			flow += f[0][i];
	cout << flow;
}