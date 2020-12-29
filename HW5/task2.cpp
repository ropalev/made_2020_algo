#include <iostream>
#include <string>

int SIZE = 1000;
int A = 7;
int PRIME = 1009;

struct Node {
	std::string key;
	std::string value;
	int empty = 1;
	Node *next = NULL;
};

class Map {
private:
	Node *arr = new Node[SIZE];

public:
	void put(std::string key, std::string value) {
		int i;
		Node *ptr;

		i = hash(key);
		ptr = &(this->arr[i]);
		while (ptr) {
			if (ptr->empty || ptr->key == key) {
				ptr->value = value;
				ptr->key = key;
				ptr->empty = 0;
				return ;
			}
			else {
				if (!ptr->next) {
					break;
				}
				ptr = ptr->next;
			}
		}
		Node *new_node = new Node;

		new_node->empty = 0;
		new_node->key = key;
		new_node->value = value;
		ptr->next = new_node;

	}


	void del(std::string key) {
		int i;
		Node *ptr;
		Node *next;
		Node *prev;
		Node *ss;

		i = hash(key);
		ss = prev = ptr = &(this->arr[i]);
		next = ptr->next;
		if (ptr->key == key) {
			if (ptr->next) {
				ptr = next;
				this->arr[i] = *ptr;
				return ;
			}
			else {
				this->arr[i].empty = 1;
				ptr = next;
			}
		}
		while (ptr) {
			if (ptr->key == key) {
				prev->next = next;
				delete ptr;
				return ;
			}
			prev = ptr;
			ptr = next;
			if (ptr) {
				next = ptr->next;
			}
		}
	}

	std::string get(std::string key) {
		int i;
		Node *ptr;

		i = hash(key);
		ptr = &(this->arr[i]);
		while (ptr) {
			if (ptr->key == key && ptr->empty == 0) {
				return ptr->value;
			}
			ptr = ptr->next;
		}
		return "none";
	}

	int hash(std::string key) {
		int res;

		res = 0;
		for (int i = 0; i < key.length(); i++) {
			res = (res * A + (key[i] - '0')) % PRIME;
		}
		res = res % SIZE;
		return (res);
	}
};


int main() {
	Map my_map;

	std::string command, key, value;
	while (std::cin >> command) {
		if (command == "put") {
			std::cin >> key >> value;
			my_map.put(key, value);
		}
		else if (command == "get") {
			std::cin >> key;
			std::cout << my_map.get(key) << "\n";
		}
		else if (command == "delete") {
			std::cin >> key;
			my_map.del(key);
		}
	}
	return (0);
}