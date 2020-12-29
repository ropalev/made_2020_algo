#include <iostream>
#include <vector>
using namespace std;

struct NumArray {
	vector<int>& arr;
	vector<int> tree;

	int buildTree(int node, int L, int R) {
		if (L == R)
			tree[node] = arr[L];
		else {
			int mid = L + (R - L) / 2;
			int leftSum = buildTree(2 * node, L, mid);
			int rightSum = buildTree(2 * node + 1, mid + 1, R);
			tree[node] = min(leftSum, rightSum);
		}
		return tree[node];
	}

	int min_query(int node, int i, int j, int L, int R) {
		if (i > R || j < L) return 0;
		if (i <= L && j >= R) return tree[node];
		int mid = L + (R - L) / 2;
		int leftSum = min_query(2 * node, i, j, L, mid);
		int rightSum = min_query(2 * node + 1, i, j, mid + 1, R);
		return min(leftSum, rightSum);
	}

	void update(int node, int i, int L, int R, int delta) {
		if (i < L || i > R) return;
		tree[node] += delta;
		if (L == R) return;
		int mid = L + (R - L) / 2;
		update(2 * node, i, L, mid, delta);
		update(2 * node + 1, i, mid + 1, R, delta);
	}

public:
	NumArray(vector<int>& nums): arr(nums) , tree(4 * nums.size()) {
		if (!arr.empty())
			buildTree(1, 0, nums.size() - 1);
	}

	void update(int i, int val) {
		update(1, i, 0, arr.size() - 1, val - arr[i]);
		arr[i] = val;
	}

	int min_q(int i, int j) {
		return min_query(1, i, j, 0, arr.size() - 1);
	}
};

int main() {
	const int N = 1e5;  // limit for array size
	int n;  // array size

	std::cin >> n;//scanf("%d", &n);
	vector<int> a(n);
	for (int i =0; i < a.size(); i++) {
		cin >> a[i];
	}
	NumArray numArray(a);
	cout << numArray.min_q(0,4);
	numArray.update(2,0);
	cout << numArray.min_q(0,4);
	return 0;
}

