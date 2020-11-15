#include <iostream>

class BST {
	struct node {
		int key;
		node *left;
		node *right;
		int height;
	};
	node *root;

	node *insert(node *node_ptr, int value) {
		if (node_ptr == nullptr) {
			node_ptr = new node;
			node_ptr->key = value;
			node_ptr->height = 0;
			node_ptr->left = node_ptr->right = nullptr;
		} else if (value < node_ptr->key) {
			node_ptr->left = insert(node_ptr->left, value);
			if (height(node_ptr->left) - height(node_ptr->right) == 2) {
				if (value < node_ptr->left->key)
					node_ptr = singleRightRotate(node_ptr);
				else
					node_ptr = doubleRightRotate(node_ptr);
			}
		} else if (value > node_ptr->key) {
			node_ptr->right = insert(node_ptr->right, value);
			if (height(node_ptr->right) - height(node_ptr->left) == 2) {
				if (value > node_ptr->right->key)
					node_ptr = singleLeftRotate(node_ptr);
				else
					node_ptr = doubleLeftRotate(node_ptr);
			}
		}
		node_ptr->height = std::max(height(node_ptr->left), height(node_ptr->right)) + 1;
		return node_ptr;
	}

	node *singleRightRotate(node *&node_ptr) {
		node *u = node_ptr->left;
		node_ptr->left = u->right;
		u->right = node_ptr;
		node_ptr->height = std::max(height(node_ptr->left), height(node_ptr->right)) + 1;
		u->height = std::max(height(u->left), node_ptr->height) + 1;
		return u;
	}

	node *singleLeftRotate(node *&node_ptr) {
		node *u = node_ptr->right;
		node_ptr->right = u->left;
		u->left = node_ptr;
		node_ptr->height = std::max(height(node_ptr->left), height(node_ptr->right)) + 1;
		u->height = std::max(height(node_ptr->right), node_ptr->height) + 1;
		return u;
	}

	node *doubleLeftRotate(node *&node_ptr) {
		node_ptr->right = singleRightRotate(node_ptr->right);
		return singleLeftRotate(node_ptr);
	}

	node *doubleRightRotate(node *&node_ptr) {
		node_ptr->left = singleLeftRotate(node_ptr->left);
		return singleRightRotate(node_ptr);
	}

	node *findMin(node *node_ptr) {
		if (node_ptr == nullptr)
			return nullptr;
		else if (node_ptr->left == nullptr)
			return node_ptr;
		else
			return findMin(node_ptr->left);
	}

	node *findMax(node *node_ptr) {
		if (node_ptr == nullptr)
			return nullptr;
		else if (node_ptr->right == nullptr)
			return node_ptr;
		else
			return findMax(node_ptr->right);
	}

	node *del(node *node_ptr, int value) {
		node *temp;
		if (node_ptr == nullptr)
			return nullptr;
		else if (value < node_ptr->key)
			node_ptr->left = del(node_ptr->left, value);
		else if (value > node_ptr->key)
			node_ptr->right = del(node_ptr->right, value);
		else if (node_ptr->left && node_ptr->right) {
			temp = findMin(node_ptr->right);
			node_ptr->key = temp->key;
			node_ptr->right = del(node_ptr->right, node_ptr->key);
		} else {
			temp = node_ptr;
			if (node_ptr->left == nullptr)
				node_ptr = node_ptr->right;
			else if (node_ptr->right == nullptr)
				node_ptr = node_ptr->left;
			delete temp;
		}
		if (node_ptr == nullptr)
			return node_ptr;
		node_ptr->height = std::max(height(node_ptr->left), height(node_ptr->right)) + 1;
		if (height(node_ptr->left) - height(node_ptr->right) == 2) {
			if (height(node_ptr->left->left) - height(node_ptr->left->right) == 1)
				return singleLeftRotate(node_ptr);
			else
				return doubleLeftRotate(node_ptr);
		} else if (height(node_ptr->right) - height(node_ptr->left) == 2) {
			if (height(node_ptr->left->right) - height(node_ptr->left->left) == 1)
				return singleRightRotate(node_ptr);
			else
				return doubleRightRotate(node_ptr);
		}
		return node_ptr;
	}

	int height(node *node_ptr) {
		return (node_ptr == nullptr ? -1 : node_ptr->height);
	}

	void inorder(node *node_ptr) {
		if (node_ptr == nullptr)
			return;
		inorder(node_ptr->left);
		std::cout << node_ptr->key << " ";
		inorder(node_ptr->right);
	}

	int k_max(node *node_ptr, int &k) {
		if (node_ptr) {
			int x = k_max(node_ptr->right, k);
			return !k ? x : !--k ? node_ptr->key
								 : k_max(node_ptr->left, k);
		}
		return 0;
	}

public:
	BST() {
		this->root = nullptr;
	}

	void insert(int value) {
		this->root = insert(this->root, value);
	}

	void del(int value) {
		this->root = del(this->root, value);
	}

	int k_max(int k) {
		return k_max(this->root, k);
		}
};


int main() {
	int n, value, c;
	BST avl;
	std::cin >> n;
	std::string str;
	while (n != 0) {
		std::cin >> c >> value;
		if (c == 1) {
			avl.insert(value);
		} else if (c == 0) {
			std::cout << avl.k_max(value) << "\n";
		} else if (c == -1) {
			avl.del(value);
		}
		n--;
	}
	return 0;
}