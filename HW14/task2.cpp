#include <bits/stdc++.h>


std::vector<int> zfunction(std::string s) {
	size_t n = s.length();
	std::vector<int> z(n);
	z[0] = 0;
	int left = 0;
	int right = 0;
	for (int i = 1; i < n; i++) {
		if (i <= right) {
			z[i] = std::min(right - i + 1, z[i - left]);
		}
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
			z[i] += 1;
		}
		if (i + z[i] - 1 > right) {
			left = i;
			right = i + z[i] - 1;
		}
	}
	return z;
}

int main() {
	std::string s;
	std::cin >> s;
	std::vector<int> z = zfunction(s);
	for (int i = 1; i < z.size(); i++) {
		std::cout << z[i] << " ";
	}
	return 0;
}