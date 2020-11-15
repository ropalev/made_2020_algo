#include <iostream>
#include <vector>
#include <string>


struct Node {
	int y;
	int sz;
	int val;
	bool reverse;
	Node *l, *r;
};

Node *new_node(int val) {
	Node *result = new Node;
	result->y = std::rand();
	result->sz = 1;
	result->val = val;
	result->l = result->r = nullptr;
	result->reverse = false;
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
		t->sz = 1 + this->get_sz(t->l) + this->get_sz(t->r);
	}

	void push(Node *it) {
		if (it && it->reverse) {
			it->reverse = false;
			std::swap(it->l, it->r);
			if (it->l) {
			    it->l->reverse ^= true;
			}
			if (it->r) {
			    it->r->reverse ^= true;}
		}
	}

	Node *merge(Node *t1, Node *t2) {

		if (t1 == nullptr) {
		    return t2;
		 }
		if (t2 == nullptr) {
		    return t1;
		    }
		this->push(t1);
		this->push(t2);
		if (t1->y > t2->y) {
			t1->r = this->merge(t1->r, t2);
			this->upd_sz(t1);
			return t1;
		} else {
			t2->l = this->merge(t1, t2->l);
			this->upd_sz(t2);
			return t2;
		}
	}

	void split(Node *t, int x, Node *&t1, Node *&t2) {
		if (t == nullptr) {
			t1 = t2 = nullptr;
			return;
		}
		this->push(t);
		if (get_sz(t->l) < x) {
			this->split(t->r, x - this->get_sz(t->l) - 1, t->r, t2);
			t1 = t;
		} else {
			this->split(t->l, x, t1, t->l);
			t2 = t;
		}
		this->upd_sz(t);
	}

	Node *add(Node *t, int pos, int val) {
		Node *t1, *t2;
		this->split(t, pos, t1, t2);
		Node *new_tree = new_node(val);
		t1 = this->merge(t1, new_tree);
		return this->merge(t1, t2);
	}

	Node *remove(Node *t, int pos) {
		Node *t1, *t2, *t3, *t4;
		this->split(t, pos, t1, t2);
		this->split(t2, 1, t3, t4);
		t = this->merge(t1, t4);
		delete t3;
		return t;
	}

	int get_value(Node *t, int pos) {
		int my_idx = this->get_sz(t->l);
		if (pos < my_idx) {
			return this->get_value(t->l, pos);
		} else if (pos == my_idx) {
			return t->val;
		} else {
			return this->get_value(t->r, pos - my_idx - 1);
		}
	}

	Node *to_front(Node *t, int l, int r) {
		Node *t1, *t2, *t3, *t4;
		this->split(t, r + 1, t1, t2);
		this->split(t1, l, t3, t4);
		return this->merge(this->merge(t4, t3), t2);
	}

	void print_tree(Node *t) {
		if (t == nullptr) {
		    return;
		}
		this->push(t);
		this->print_tree(t->l);
		std::cout << t->val << " ";
		this->print_tree(t->r);
	}

	Node *reverse(Node *t, int l, int r) {
		Node *t1, *t2, *t3;
		this->split(t, l, t1, t2);
		this->split(t2, r - l + 1, t2, t3);
		t2->reverse ^= true;
		return this->merge(this->merge(t1, t2), t3);
	}

public:
	Treap() { root = nullptr; }

	void from_vector(const std::vector<int> &v) {
		Node *result = nullptr;
		for (int i : v) {
			result = this->merge(result, new_node(i));
		}
		this->root = result;
	}

	void add(int pos, int val) {
		this->root = this->add(this->root, pos, val);
	}

	void remove(int pos) {
		this->root = this->remove(this->root, pos);
	}

	void print_tree() {
		this->print_tree(this->root);
	}

	int get_sz() {
		return this->get_sz(this->root);
	}

	void to_front(int l, int r) {
		this->root = this->to_front(this->root, l, r);
	}

	void reverse(int l, int r) {
		this->root = this->reverse(this->root, l, r);
	}
};

int main() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> v_arr(n);
	for (int i = 0; i < n; i++) {
		std::cin >> v_arr[i];
	}
	Treap treap = Treap();
	treap.from_vector(v_arr);
	std::string command;
	int pos, value;
	while (m--) {
		std::cin >> command;
		if (command == "add") {
			std::cin >> pos >> value;
			treap.add(pos, value);
		} else if (command == "del") {
			std::cin >> value;
			treap.remove(value - 1);
		}
	}
	std::cout << treap.get_sz() << "\n";
	treap.print_tree();
	return 0;
}