#include <bits/stdc++.h>

int find_set(int v, std::vector<int> &parent) {
	if (v == parent[v])
		return v;
	return parent[v] = find_set(parent[v], parent);
}

void union_sets(int a, int b, std::vector<int> &parent, std::vector<int> &rank,
				std::vector<int> &maximum, std::vector<int> &minimum, std::vector<int> &size) {
	a = find_set(a, parent);
	b = find_set(b, parent);
	if (a != b) {
		if (rank[a] < rank[b])
			std::swap(a, b);
		parent[b] = a;
		size[a] += size[b];
		maximum[a] = std::max(maximum[a], maximum[b]);
		minimum[a] = std::min(minimum[a], minimum[b]);
		if (rank[a] == rank[b])
			rank[a]++;
	}
}


int main() {
	int n, value1, value2;
	std::cin >> n;
	std::vector<int> parent(n);
	std::vector<int> rank(n, 0), maximum(n), minimum(n), size(n, 1);
	for (int i = 0; i < rank.size(); i++) {
		parent[i] = i;
		maximum[i] = i;
		minimum[i] = i;
	}
	std::string str;
	while (std::cin >> str) {
		if (str == "union") {
			std::cin >> value1 >> value2;
			value1--;
			value2--;
			union_sets(value1, value2, parent, rank, maximum, minimum, size);
		} else if (str == "get") {
			std::cin >> value1;
			value1--;
			std::cout << minimum[find_set(value1, parent)] + 1 << " ";
			std::cout << maximum[find_set(value1, parent)] + 1 << " ";
			std::cout << size[find_set(value1, parent)];
			std::cout << "\n";
		}
	}
	std::cout << std::endl;
	return 0;
}