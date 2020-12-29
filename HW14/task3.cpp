#include <bits/stdc++.h>


std::vector<int> prefixfunction(std::string s) {
	size_t len = s.length();
	std::vector<int> prefix(len);
	prefix[0] = 0;
	for (int i = 1; i < len; i++) {
		int j = prefix[i - 1];
		while (j > 0 && s[i] != s[j]) {
			j = prefix[j - 1];
		}
		if (s[i] == s[j]) {
			j++;
		};
		prefix[i] = j;
	}
	return prefix;
}

std::vector<int> kmp(std::string pattern, std::string text) {
	int p_size = pattern.length();
	int t_size = text.length();
	std::vector<int> prefix = prefixfunction(pattern + "#" + text);
	std::vector<int> res;
	for (int i = p_size; i < p_size + 1 + t_size; i++) {
		if (prefix[i] == p_size) {
			res.push_back(i - p_size * 2 + 1);
		}
	}
	return res;
}


int main() {
	std::string p, t;
	std::cin >> p >> t;
	std::vector<int> res = kmp(p, t);
	std::cout << res.size() << "\n";
	for (int re : res) {
		std::cout << re << " ";
	}
	return 0;
}