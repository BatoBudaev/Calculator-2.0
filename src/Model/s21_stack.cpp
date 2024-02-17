#include "s21_stack.h"

namespace s21 {
Stack::Stack() : top(-1) {}

double Stack::getData(int index) const {
  if (index >= 0 && index <= MAX_SIZE - 1) {
    return data[index];
  } else {
    return 0.0;
  }
}

bool Stack::isEmpty() const { return top == -1; }

void Stack::push(char c) {
  if (top == MAX_SIZE - 1) {
    return;
  }

  top++;
  data[top] = c;
}

void Stack::push(double d) {
  if (top >= MAX_SIZE - 1) {
    return;
  }

  top++;
  data[top] = d;
}

char Stack::popChar() {
  if (isEmpty()) {
    return 0;
  }

  return data[top--];
}

double Stack::popDouble() {
  if (isEmpty()) {
    return 0;
  }

  return data[top--];
}

int Stack::getTop() const { return top; }
}  // namespace s21