#include <iostream>
#include <string>

/*
struct node {
public:
	int key;
	node *left;
	node *right;
	//node *parent;
	explicit node(int value) {
		this->key = value;
		this->left = nullptr;
		this->right = nullptr;
		//this->parent = nullptr;
	}
};

class bin_tree {
public:
	node *root;

	bin_tree() {
		this->root = nullptr;
	}

	void insert(int value) {
		node *ptr;
		if (!this->root) {
			this->root = new node(value);
			return;
		}
		ptr = this->root->key > value ? this->root->left : this->root->right;
		if (!ptr) {
			if (this->root->key > value) {
				this->root->left = new node(value);
			} else {
				this->root->right = new node(value);
			}
			return;
		}
		while (ptr) {
			if (ptr->key < value) {
				if (ptr->right) {
					ptr = ptr->right;
				} else {
					ptr->right = new node(value);
					//ptr->right->parent = ptr;
					return;
				}
			} else if (ptr->key > value) {
				if (ptr->left) {
					ptr = ptr->left;
				} else {
					ptr->left = new node(value);
					//ptr->left->parent = ptr;
					return;
				}
			} else {
				return;
			}
		}
	}

	node *exists(int value) const {
		node *ptr;
		node *exs;
		ptr = this->root;
		exs = nullptr;
		while (ptr) {
			if (ptr->key == value) {
				exs = ptr;
				break;
				//return true;
			} else if (ptr->key > value) {
				ptr = ptr->left;
			} else {
				ptr = ptr->right;
			}
		}
		return exs;
	}

	std::string next(node *v, int x) {
		std::string res = "none";
		while (v != nullptr) {
			if (v->key <= x) {
				v = v->right;
			} else if (v->key > x) {
				res = std::to_string(v->key);
				v = v->left;
			}
		}
		return res;
	}

	std::string prev(node *v, int x) const {
		std::string res = "none";
		while (v != nullptr) {
			if (v->key < x) {
				res = std::to_string(v->key);
				v = v->right;
			} else if (v->key >= x) {

				v = v->left;
			}
		}
		return res;
	}


	node *del(node *node_ptr, int value) {
		node * noda;
		noda = node_ptr;
		if (node_ptr == nullptr)
			return node_ptr;
		else if (value < noda->key)
			noda->left = del(noda->left, value);
		else if (value > noda->key)
			noda->right = del(noda->right, value);
		else {
			if (noda->left == nullptr && noda->right == nullptr) {
				delete noda;
				noda = nullptr;
			} else if (noda->left == nullptr) {
				node *temp = noda;
				noda = noda->right;
				delete temp;
			} else if (noda->right == nullptr) {
				node *temp = noda;
				noda = noda->left;
				delete temp;
			} else {
				node *temp = max(noda->left);
				noda->key = temp->key;
				noda->left = del(noda->left, temp->key);
			}
		}
		return noda;
	}

	static node *max(node *node_ptr) {
		while (node_ptr->right != nullptr) {
			node_ptr = node_ptr->right;
		}
		return node_ptr;
	}
};
 */


#include <iostream>
#include <string>
#include <vector>


struct node {
	int key;
	node *left;
	node *right;

	node(int x) : key(x), left(nullptr), right(nullptr) {}
};

struct bin_tree {
	node *root;

	bin_tree() : root(nullptr) {}

	node *search(node *node_ptr, int x) {
		if (node_ptr == nullptr) {
			return nullptr;
		}
		if (node_ptr->key == x) {
			return node_ptr;
		} else if (x < node_ptr->key) {
			return search(node_ptr->left, x);
		} else {
			return search(node_ptr->right, x);
		}
	}

	node *insert(node *node_ptr, int x) {
		if (node_ptr == nullptr) {
			return new node(x);
		} else if (x < node_ptr->key) {
			node_ptr->left = insert(node_ptr->left, x);
		} else if (x > node_ptr->key) {
			node_ptr->right = insert(node_ptr->right, x);
		}
		return node_ptr;
	}

	static node *max(node *node_ptr) {
		while (node_ptr->right != nullptr) {
			node_ptr = node_ptr->right;
		}
		return node_ptr;
	}

	node *del(node *node_ptr, int x) {
		if (node_ptr == nullptr) {
			return nullptr;
		}
		if (x < node_ptr->key) {
			node_ptr->left = del(node_ptr->left, x);
		} else if (x > node_ptr->key) {
			node_ptr->right = del(node_ptr->right, x);
		} else if (node_ptr->left == nullptr && node_ptr->right == nullptr) {
			delete node_ptr;
			node_ptr = nullptr;
		} else if (node_ptr->left == nullptr) {
			node *right_ = node_ptr->right;
			delete node_ptr;
			node_ptr = right_;
		} else if (node_ptr->right == nullptr) {
			node *left_ = node_ptr->left;
			delete node_ptr;
			node_ptr = left_;
		} else {
			node_ptr->key = max(node_ptr->left)->key;
			node_ptr->left = del(node_ptr->left, node_ptr->key);
		}
		return node_ptr;
	}

	std::string next(node *node_ptr, int x) {
		std::string res = "none";
		while (node_ptr != nullptr) {
			if (node_ptr->key <= x) {
				node_ptr = node_ptr->right;
			} else if (node_ptr->key > x) {
				res = std::to_string(node_ptr->key);
				node_ptr = node_ptr->left;
			}
		}
		return res;
	}

	std::string prev(node *v, int x) {
		std::string res = "none";
		while (v != nullptr) {
			if (v->key >= x) {
				v = v->left;
			} else if (v->key < x) {
				res = std::to_string(v->key);
				v = v->right;
			}
		}
		return res;
	}
};

int main() {

	std::string str;
	int value;
	bin_tree bts;

	bts = bin_tree();
	while (std::cin >> str) {
		std::cin >> value;
		if (str == "insert") {
			bts.insert(bts.root, value);
		} else if (str == "exists") {
			if (bts.search(bts.root, value) == nullptr) {
				std::cout << "false" << "\n";
			} else {
				std::cout << "true" << "\n";
			}
		} else if (str == "next") {
			std::cout << bts.next(bts.root, value) << "\n";
		} else if (str == "prev") {
			std::cout << bts.prev(bts.root, value) << "\n";
		} else if (str == "delete") {
			bts.del(bts.root, value);
		}
	}
	return 0;
}


