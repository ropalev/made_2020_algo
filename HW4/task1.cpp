#include <stdlib.h>
#include <iostream>

typedef struct s_node {
	int data;
	s_node *next;
} t_node;

typedef struct s_stack {
  t_node *begin;
  int min;
  t_node *end;
  int size;
} t_stack;

t_stack *create_stack() {
  t_stack *stack;

  if (!(stack = (t_stack *)malloc(sizeof(t_stack)))) {
    return NULL;
  }
  stack->begin = NULL;
  stack->end = NULL;
  stack->size = 0;
  return stack;
}

void node_create(t_stack *stack, int data) {
  t_node *node;

  if (!(node = (t_node *)malloc(sizeof(t_node)))) {
	return;
  }
  node->data = data;
  if (!stack->begin) {
    stack->begin = node;
    stack->min = node->data;
    stack->end = node;
	node->next = NULL;
  }
  else {
    node->next = stack->begin;
    stack->begin = node;
    if (stack->min > node->data) {
      stack->min = node->data;
    }
  }
  stack->size += 1;
};

void find_min(t_stack *stack) {
  t_node *ptr;

  ptr = stack->begin;
  while (ptr) {
    if (ptr->data < stack->min) {
      stack->min = ptr->data;
    }
    ptr = ptr->next;
  }
}

void node_delete(t_stack *stack) {
  t_node *ptr;
  ptr = stack->begin;
  if (stack->size == 1) {
	stack->begin = NULL;
	stack->end = NULL;
  }
  else {
    stack->begin = stack->begin->next;
    if (stack->begin->data != stack->min) {
      stack->min = stack->begin->data;
      find_min(stack);
    }
  }
  free(ptr);
  stack->size -= 1;
  return ;
}

void free_stack(t_stack *stack) {
  while (stack->size) {
    node_delete(stack);
  }

}


int main() {
  t_stack *stack;
  int n, c, data;
  stack = create_stack();
  if (!stack) {
    return (0);
  }
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    scanf("%d", &c);
    if (c == 1) {
	  scanf("%d", &data);
      node_create(stack, data);
    }
    else if (c == 2) {
      node_delete(stack);
    }
    else if (c == 3) {
      printf("%d\n", stack->min);
    }
  }
  free_stack(stack);
  return (0);
}