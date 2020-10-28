#include <iostream>
#include <vector>


void turtle(int** arr, const int& n, const int& k, char *path) {
	std::vector<std::vector<std::pair<int, int>>> route(n);
	route[0].push_back(std::make_pair(0, 0));
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < k; j++) {
			if (i == 0 && j > 0) {
				arr[i][j] = arr[i][j] + arr[i][j - 1];
				route[i].push_back(std::make_pair(i, j -1));
			}
			else if (j == 0 && i > 0) {
				arr[i][j] += arr[i - 1][j];
				route[i].push_back(std::make_pair(i - 1, j));
			}
			else if (i > 0 && j > 0) {
				arr[i][j] += std::max(arr[i][j - 1], arr[i - 1][j]);
				if (arr[i][j - 1] > arr[i - 1][j]) {
					route[i].push_back(std::make_pair(i, j -1));
				}
				else {
					route[i].push_back(std::make_pair(i - 1, j));
				}
			}
		}
	}
	int i = n - 1;
	int j = k - 1;
	int it = 0;
	while (i > 0 || j > 0) {
		if (i > 0 && route[i][j].first == i - 1) {
			path[it] = 'D';
			i--;
		}
		else if (j > 0 && route[i][j].first == i) {
			path[it] = 'R';
			j--;
		}
		it++;
	}
}

int main() {
	int n, k;
	std::cin >> n >> k;
	char path[n + k - 2];
	int** arr = new int* [n];
	for (size_t i = 0; i < n; i++) {
		arr[i] = new int[k];
		for (int j = 0; j < k; j++) {
			std::cin >> arr[i][j];
		}
	}
	turtle(arr, n, k, path);
	std::cout << arr[n - 1][k - 1] << "\n";
	for (int i = n + k - 3; i >= 0; i--) {
		std::cout << path[i];
	}
	return 0;
}