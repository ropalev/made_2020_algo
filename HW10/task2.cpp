#include <bits/stdc++.h>
#include <iostream>

int dfs(std::string str, std::map<std::string, bool> &used, std::map<std::string, std::vector<std::string>> &graph) {
	if (used[str]) {
		return 0;
	}
	int dist = 0;
	used[str] = true;
	for (auto &i : graph[str]) {
		dist = std::max(dfs(i, used, graph), dist);
	}
	return dist + 1;
}

int main() {
	int i;
	int n;
	std::string str1, str2;
	std::cin >> n;
	std::map<std::string, std::vector<std::string>> graph;
	std::map<std::string, bool> used;
	for (i = 0; i < n; i++) {
		std::cin >> str1 >> str2 >> str2;
		transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
		transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
		graph[str2].push_back(str1);
		graph[str1].push_back(str2);
	}
	std::cout << dfs("polycarp", used, graph) << std::endl;
	return 0;
}