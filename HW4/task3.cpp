#include <iostream>
#include <vector>
#include <cmath>

class Vector {
 private:
  int size = 0;
  int length = 2;
  int start = 0;
  int end = 0;
  int *arr = new int[length];

 public:
  void push_back(int data) {
	if (this->size < this->length) {
	  this->arr[this->size] = data;
	  this->size += 1;
	}
	else {
	  change_length(2);
	  this->arr[this->size] = data;
	  this->size += 1;
	}
	end = (end + 1) % length;
  }

  int pop() {
	if (this->size == floor(this->length / 4)) {
	  change_length(0.5);
	}
	this->size -= 1;
	start = (start + 1) % length;
	return this->arr[this->size];
  }

  void change_length(float mult) {
	this->length *= mult;
	int *arr_new = new int[this->length];
	for (int i = 0; i < this->size; i++) {
	  arr_new[i] = this->arr[i];
	}
	delete [] this->arr;
	this->arr = arr_new;
  }

  int get_size() {
	return this->size;
  }
};


int main() {
  char c;
  int d;
  Vector stack;

  while (std::cin >> c) {
	if (c == '*') {
	  stack.push_back(stack.pop() * stack.pop());
	}
	else if (c == '-') {
	  d = stack.pop() - stack.pop();
	  d *= -1;
	  stack.push_back(d);
	}
	else if (c == '+') {
	  stack.push_back(stack.pop() + stack.pop());
	}
	else {
	  stack.push_back(c - '0');
	}
	if (std::cin.peek() == '\n') {
	  break;
	}
  }
  d = stack.pop();
  std::cout << d << std::endl;
  return (0);
}
