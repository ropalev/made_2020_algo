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
		  if (ptr->empty || (ptr->key == key && ptr->value == value)) {
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

  void delall(std::string key) {
	  int i;
	  Node *ptr;

	  i = this->hash(key);
	  ptr = &(this->arr[i]);
	  while (this->del(key,"none", true)) {
	  }
  }
  bool del(std::string key, std::string value , bool flag_all) {
	  int i;
	  Node *ptr;
	  Node *next;
	  Node *prev;
	  Node *ss;

	  i = hash(key);
	  ss = prev = ptr = &(this->arr[i]);
	  next = ptr->next;
	  if (ptr->key == key && (ptr->value == value || flag_all)) {
		  if (ptr->next) {
			  ptr = next;
			  this->arr[i] = *ptr;
			  prev = ptr;
			  if (!flag_all) {
				  return true;
			  }
		  }
		  else {
			  this->arr[i].empty = 1;
			  ptr = next;
		  }
	  }
	  while (ptr) {
		  if (ptr->key == key && (ptr->value == value || flag_all)) {
			  prev->next = next;
			  if (!flag_all) {
				  return true;
			  }
		  }
		  prev = ptr;
		  ptr = next;
		  if (ptr) {
			  next = ptr->next;
		  }
	  }
	  if (flag_all) {
	  	this->arr[i].empty = 1;
	  }
	  return false;
  }

  std::string get(std::string key) {
	  int i, n;
	  Node *ptr;
	  std::string res;

	  res = "";
	  i = hash(key);
	  n = 0;
	  ptr = &(this->arr[i]);
	  while (ptr) {
		  if (ptr->key == key && ptr->empty == 0) {
			  if (res == "") {
			  	res = ptr->value;
			  }
			  else {
			  	res.append(" " + ptr->value);
			  }
			  n++;
		  }
		  ptr = ptr->next;
	  }
	  if (n) {
	  	return std::to_string(n).append(" ").append(res);
	  }
	  return "0";
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

	my_map = Map();
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
			std::cin >> key >> value;
			my_map.del(key, value, false);
		}
		else if (command == "deleteall") {
			std::cin >> key;
			my_map.delall(key);
		}
	}
	return (0);
}

/*
 * put 1 a
put 1 a
put 1 b
put 1 c
deleteall 1
 */