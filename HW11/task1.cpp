#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <vector>

bool isin(int x, int y, int n) {
	if (x >= 0 && x < n && y >= 0 && y < n)
		return true;
	return false;
}

void bfs(int start_x, int start_y, int end_x, int end_y, int n, std::vector<std::vector<std::pair<int, int>>> &board) {
	std::queue<std::pair<int, int>> queue;
	std::vector<std::pair<int, int>> res;
	std::pair<int, int> cell;
	int x_move[] = {2, 2, 1, -1, -2, -2, -1, 1};
	int y_move[] = {1, -1, -2, -2, -1, 1, 2, 2};
	cell = std::make_pair(start_x, start_y);
	queue.push(cell);
	while (true) {
		cell = queue.front();
		if (cell.first == end_x && cell.second == end_y) {
			break;
		}
		for (int i = 0; i < 8; i++) {
			if (isin(cell.first + x_move[i], cell.second + y_move[i], n)) {
				if (board[cell.first + x_move[i]][cell.second + y_move[i]].first == -1 &&
					board[cell.first + x_move[i]][cell.second + y_move[i]].second == -1) {
					board[cell.first + x_move[i]][cell.second + y_move[i]] = cell;
					queue.push(std::make_pair(cell.first + x_move[i], cell.second + y_move[i]));
				}
			}
		}
		queue.pop();
	}
	int x, y;
	x = cell.first;
	y = cell.second;
	res.push_back(cell);
	while (true) {
		int tmp_x, tmp_y;
		tmp_x = board[x][y].first;
		tmp_y = board[x][y].second;
		res.emplace_back(tmp_x, tmp_y);
		x = tmp_x;
		y = tmp_y;
		if (x == start_x && y == start_y) {
			break;
		}
	}
	std::cout << res.size() << "\n";
	for (int i = res.size() - 1; i >= 0; i--) {
		std::cout << res[i].first + 1 << " " << res[i].second + 1 << "\n";
	}
}
int main() {

	int n;
	int x1, y1, x2, y2;
	std::cin >> n;
	std::vector<std::vector<std::pair<int, int>>> board(n, std::vector<std::pair<int, int>>(n, std::make_pair(-1, -1)));
	std::cin >> x1 >> y1 >> x2 >> y2;
	bfs(x1 - 1, y1 - 1, x2 - 1, y2 - 1, n, board);
	return 0;
}