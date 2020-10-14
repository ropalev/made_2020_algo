#include <stdlib.h>
#include <iostream>
#include <vector>

struct Node {
  int data;
  Node *next;
  int min;
};

class Stack {
  Node *begin;
  int size = 0;
 public:
  void push(int data) {
	Node *node;
	node = new Node;
	node->data = data;
	if (!size) {
	  this->begin = node;
	  this->begin->min = data;
	  node->next = NULL;
	}
	else {
	  node->next = this->begin;
	  if (node->data < this->begin->min) {
	    node->min = node->data;
	  }
	  else {
	    node->min = this->begin->min;
	  }
	  this->begin = node;
	}
	this->size += 1;
  }

  void pop() {
	Node *ptr;
	ptr = this->begin;
	if (this->size == 1) {
	  this->begin = NULL;
	}
	else {
	  this->begin = this->begin->next;
	}
	free(ptr);
	this->size -= 1;
	return;
  }

  int get_min() {
    return this->begin->min;
  }

  void free_stack() {
	while (this->size) {
	  this->pop();
	}
  }
  
  int get_size() {
	return size;
  }
};

int main() {
  int n, c, data;
  Stack stack;
  std::cin >> n;
  std::vector <int> v_res;
  for (int i = 0; i < n; i++) {
    scanf("%d", &c);
    if (c == 1) {
	  scanf("%d", &data);
      stack.push(data);
    }
    else if (c == 2) {
      stack.pop();
    }
    else if (c == 3) {
	  printf("%d\n", stack.get_min());
    }
  }
  stack.free_stack();
  return (0);
}
