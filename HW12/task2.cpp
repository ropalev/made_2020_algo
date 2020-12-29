#include <bits/stdc++.h>

int find_set(int v, std::vector<int> &parent) {
	if (v == parent[v])
		return v;
	return parent[v] = find_set(parent[v], parent);
//	return find_set(parent[v], parent);
}

void union_sets(int a, int b, std::vector<int> &parent, std::vector<int> &rank,std::vector<std::vector<int>> &children) {
	a = find_set(a, parent);
	b = find_set(b, parent);
	if (a != b) {
		if (rank[a] < rank[b])
			std::swap(a, b);
		parent[b] = a;
		children[a].push_back(b);
		if (rank[a] == rank[b])
			rank[a]++;
	}
}


void add(int x, int v, std::vector<int> &expa, std::vector<int> &parent,std::vector<std::vector<int>> &chldren) {
	int a = find_set(v, parent);
	std::queue<int> query;
	query.push(a);
	while (query.size()) {
		int top = query.front();
		query.pop();
		for (int i = 0; i < chldren[top].size(); i++) {
			query.push(chldren[top][i]);
		}
		expa[top] += x;
	}
}


int main() {
	int n, m, value1, value2;
	std::cin >> n >> m;
	std::vector<int> parent(n);
	std::vector<std::vector<int>> children(n, std::vector<int>());
	std::vector<int> rank(n, 0), expa(n, 0), size(n, 1);
	for (int i = 0; i < rank.size(); i++) {
		parent[i] = i;
	}
	std::string str;
	while (m--) {
		std::cin >> str;
		if (str == "join") {
			std::cin >> value1 >> value2;
			value1--;
			value2--;
			if (value1 != value2) {
				union_sets(value1, value2, parent, rank, children);
			}
		} else if (str=="add") {
			std::cin >> value1 >> value2;
			value1--;
			add(value2, value1, expa, parent, children);
		}
		else if (str == "get") {
			std::cin >> value1;
			value1--;
			std::cout << expa[value1] << "\n";
		}
	}
	std::cout << std::endl;
	return 0;
}
/*
 *
add 1  100
join 2 3
join 3 1
add 2 50
add 4 40
join 4 5
add 5 50
join 5 6
add 6 60
join 7 8
join 4 9
join 7 10
 */