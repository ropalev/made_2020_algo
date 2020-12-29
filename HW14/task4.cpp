#include <bits/stdc++.h>


struct automat {
	automat() {
		nodes.emplace_back();
	}

	struct node {
		int next[26];
		std::vector<int> terminant;
		int link;
		int slink;
	};

	std::vector<node> nodes;
	int size = 0;

	void add(const std::string &s) {
		int curr = 0;
		for (char c : s) {
			int nextC = c - 'a';
			if (!nodes[curr].next[nextC]) {
				nodes.emplace_back();
				nodes[curr].next[nextC] = nodes.size() - 1;
			}
			curr = nodes[curr].next[nextC];
		}
		nodes[curr].terminant.emplace_back(size++);
	}

	void build() {
		std::queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int curr = q.front();
			q.pop();
			for (int i = 0; i < 26; i++) {
				if (!nodes[curr].next[i]) {
					nodes[curr].next[i] = nodes[nodes[curr].link].next[i];
				} else {
					int next = nodes[curr].next[i];
					if (curr) {
						nodes[next].link = nodes[nodes[curr].link].next[i];
						if (!nodes[nodes[next].link].terminant.empty()) {
							nodes[next].slink = nodes[next].link;
						} else {
							nodes[next].slink = nodes[nodes[next].link].slink;
						}
					}
					q.push(next);
				}
			}
		}
	}

	std::vector<bool> find(std::string &t) {
		std::vector<bool> res(size);
		std::vector<bool> found(nodes.size());
		int curr = 0;
		for (char c : t) {
			curr = nodes[curr].next[c - 'a'];
			int tmp = curr;
			while (!found[tmp]) {
				if (!nodes[tmp].terminant.empty()) {
					for (auto &&ends : nodes[tmp].terminant) {
						res[ends] = true;
					}
				}
				found[tmp] = true;
				tmp = nodes[tmp].slink;
			}
		}
		return res;
	}
};


int main() {
	int m;
	std::string s, t;
	std::cin >> t;
	std::cin >> m;
	automat ak;
	for (int i = 0; i < m; i++) {
		std::cin >> s;
		ak.add(s);
	}
	ak.build();
	std::vector<bool> res = ak.find(t);
	for (auto &&r : res) {
		std::cout << (r ? "Yes\n" : "No \n");
	}
	return 0;
}