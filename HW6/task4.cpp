#include <iostream>
#include <algorithm>

void distance(const std::string str1, const std::string str2, const int &m,
			  const int &n) {
	int dp[m + 1][n + 1];
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0) {
				dp[i][j] = j;
			} else if (j == 0) {
				dp[i][j] = i;
			} else if (str1[i - 1] == str2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1];
			} else {
				dp[i][j] = 1 + std::min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
			}
		}
	}
	std::cout << dp[m][n];
}

int main() {
	std::string str1, str2;
	std::cin >> str1 >> str2;
	distance(str1, str2, str1.length(), str2.length());
	return 0;
}