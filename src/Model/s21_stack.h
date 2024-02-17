#ifndef S21_STACK_H
#define S21_STACK_H

#define MAX_SIZE 255

#include <iostream>

namespace s21 {
class Stack {
 private:
  double data[MAX_SIZE]{};
  int top;

 public:
  Stack();

  double getData(int index) const;

  int getTop() const;

  bool isEmpty() const;

  void push(char c);

  void push(double d);

  char popChar();

  double popDouble();
};
}  // namespace s21

#endif  // S21_STACK_H
