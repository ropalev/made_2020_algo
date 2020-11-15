#include <iostream>
#include <vector>

struct Node {
	int y;
	int sz;
	int val;
	int prior;
	Node *l, *r;
};

Node *new_node(int val) {
	Node *result = new Node;
	result->y = std::rand();
	result->sz = 1;
	result->val = val;
	result->l = result->r = nullptr;
	return result;
}

class Treap {
private:
	Node *root;
	int get_sz(Node *t) {
		if (t == nullptr) {
			return 0;
		}
		return t->sz;
	}

	void upd_sz(Node *t) {
		if (t == nullptr) {
			return;
		}
		t->sz = 1 + get_sz(t->l) + get_sz(t->r);
	}

	Node *merge(Node *t1, Node *t2) {
		if (t1 == nullptr) {
			return t2;
		}
		if (t2 == nullptr) {
			return t1;
		}
		if (t1->y > t2->y) {
			t1->r = merge(t1->r, t2);
			upd_sz(t1);
			return t1;
		} else {
			t2->l = merge(t1, t2->l);
			upd_sz(t2);
			return t2;
		}
	}

	void split(Node *t, int x, Node *&t1, Node *&t2) {
		if (t == nullptr) {
			t1 = t2 = nullptr;
			return;
		}
		if (get_sz(t->l) < x) {
			split(t->r, x - get_sz(t->l) - 1, t->r, t2);
			t1 = t;
		} else {
			split(t->l, x, t1, t->l);
			t2 = t;
		}
		upd_sz(t);
	}

	Node *add(Node *t, int pos, int val) {
		Node *t1, *t2;
		split(t, pos, t1, t2);
		Node *new_tree = new_node(val);
		t1 = merge(t1, new_tree);
		return merge(t1, t2);
	}

	Node *remove(Node *t, int pos) {
		Node *t1, *t2, *t3, *t4;
		split(t, pos, t1, t2);
		split(t2, 1, t3, t4);
		t = merge(t1, t4);
		delete t3;
		return t;
	}

	int get_value(Node *t, int pos) {
		int my_idx = get_sz(t->l);
		if (pos < my_idx) {
			return get_value(t->l, pos);
		} else if (pos == my_idx) {
			return t->val;
		} else {
			return get_value(t->r, pos - my_idx - 1);
		}
	}

	Node *to_front(Node *t, int l, int r) {
		Node *t1, *t2, *t3, *t4;
		split(t, r + 1, t1, t2);
		split(t1, l, t3, t4);
		return merge(merge(t4, t3), t2);
	}

	void print_tree(Node *t) {
		if (t == nullptr) {
			return;
		}
		print_tree(t->l);
		std::cout << t->val << " ";
		print_tree(t->r);
	}

	void insert(Node *& t, Node *it) {
		if (!t)
			t = it;
		else if (it->prior > t->prior)
			split (t, it->val, it->l, it->r),  t = it;
		else
			insert (it->val < t->val ? t->l : t->r, it);
	}

	void erase (Node *& t, int key) {
		if (t->val == key) {
			t = merge( t->l, t->r);
		}
		else {
			erase (key < t->val ? t->l : t->r, key);
		}
	}

	std::string next(Node *t, int key) {
		std::string res = "none";
		while (t != nullptr) {
			if (t->val <= key) {
				t = t->r;
			} else if (t->val > key) {
				res = std::to_string(t->val);
				t = t->l;
			}
		}
		return res;
	}

	std::string prev(Node *t, int key) {
		std::string res = "none";
		while (t != nullptr) {
			if (t->val >= key) {
				t = t->l;
			} else if (t->val < key) {
				res = std::to_string(t->val);
				t = t->r;
			}
		}
		return res;
	}

	std::string search(Node *t, int key) {
		if (t == nullptr) {
			return "false";
		}
		if (t->val == key) {
			return "true";
		} else if (key < t->val) {
			return search(t->l, key);
		} else {
			return search(t->r, key);
		}
	}

public:
	Treap() { root = nullptr; }

	void from_vector(const std::vector<int> &v) {
		Node *result = nullptr;
		for (int i : v) {
			result = merge(result, new_node(i));
		}
		this->root = result;
	}

	void add(int pos, int val) {
		this->root = add(this->root, pos, val);
	}

	void remove(int pos) {
		this->root = remove(this->root, pos);
	}

	void print_tree() {
		print_tree(this->root);
	}

	int get_sz() {
		return get_sz(this->root);
	}

	void to_front(int l, int r) {
		this->root = to_front(this->root, l, r);
	}

	void insert(Node *it) {
		if (this->search(this->root, it->val) == "none") {
			insert(this->root, it);
		}
	}

	void erase(int key) {
		erase(this->root, key);
	}

	std::string next(int key) {
		return next(this->root, key);
	}

	std::string prev(int key) {
		return prev(this->root, key);
	}

	std::string search(int key) {
		return search(this->root, key);
	}
};


int main() {
	std::string str;
	int value;


	Treap treap = Treap();

	while (std::cin >> str) {
		std::cin >> value;
		if (str == "insert") {
			treap.insert(new_node(value));
		} else if (str == "exists") {
			std::cout << treap.search(value) << "\n";
		} else if (str == "next") {
			std::cout << treap.next(value) << "\n";
		} else if (str == "prev") {
			std::cout << treap.prev(value) << "\n";
		} else if (str == "delete") {
			treap.erase(value);
		}
		treap.print_tree();
		std::cout << "\n";
	}

	return 0;
}