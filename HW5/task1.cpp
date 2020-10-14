#include <iostream>
#include <string>

int SIZE = 10e6;
int A = 7;
int PRIME = 1046527;
struct Node {
  int value;
  int empty = 1;
  int rip = 0;
};

class Set {
 private:
  Node *arr = new Node[SIZE];

  bool exists(int value, int &i) {

	  i = this->hash(value);
	  while (!this->arr[i % SIZE].empty) {
		  if (this->arr[i % SIZE].value == value && this->arr[i % SIZE].rip == 0) {
			  return (true);
		  }
		  i++;
	  }
	  return (false);
  }

 public:
  void insert (int value) {
	  int i;


	  if (exists(value, (int &) i)) {
		  return;
	  }
	  this->arr[i % SIZE].value = value;
	  this->arr[i % SIZE].empty = 0;
  }
  void del (int value) {
  	int i;

	  if (!exists(value, (int &) i)) {
		  return;
	  }
	  this->arr[i % SIZE].rip = 1;
  }

  bool exists(int value) {
	  int i;

	  return exists(value, (int &) i);
  }

  int hash (int value) {
	return (A * value % PRIME) % SIZE;
  }

};


int main() {
	Set my_set;
	int value;

	std::string str;
	while (std::cin >> str >> value) {
		if (str == "insert") {
			my_set.insert(value);
		}
		else if (str == "exists") {
			if (my_set.exists(value)) {
				std::cout << "true" << "\n";
			}
			else {
				std::cout << "false" << "\n";
			}
		}
		else if (str == "delete") {
			my_set.del(value);
		}
		if (std::cin.peek() == EOF) {
			break;
		}
	}
	return (0);
}
