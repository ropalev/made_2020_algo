#include <bits/stdc++.h>

std::vector<unsigned long long> poly;
std::vector<unsigned long long> hash;

unsigned long long gethash(int l, int r) {
	return hash[r + 1] - hash[l] * poly[r - l + 1];
}

bool check(int a, int b, int c, int d) {
	return gethash(a, b) == gethash(c, d);
}


int main() {
	std::string s;
	size_t m;
	std::cin >> s;
	std::cin >> m;
	poly.resize(s.length() + 1);
	hash.resize(s.length() + 1);
	const long long PRIME = 387066959;
	hash[0] = 0;
	poly[0] = 1;

	for (int i = 0; i < s.length(); i++) {
		hash[i + 1] = hash[i] * PRIME + s[i];
		poly[i + 1] = poly[i] * PRIME;
	}

	for (int i = 0; i < m; i++) {
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		a--;
		b--;
		c--;
		d--;
		std::cout << (check(a, b, c, d) ? "Yes\n" : "No\n");
	}
	return 0;
}