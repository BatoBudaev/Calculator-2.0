#ifndef S21_MODEL_H
#define S21_MODEL_H

#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>

namespace s21 {
class Model {
 public:
  Model();

  ~Model();

  void processExpression(const char *infixExpression, double x);

  [[nodiscard]] double getResult() const;

  [[nodiscard]] bool isNoError() const;

 private:
  double result;
  bool noError{};

  static int isOperator(char c);

  static int getPriority(char c);

  static bool convertToPostfix(const char *expression, char *postfix);

  static double calculatePostfix(char *postfix, double x);
};
}  // namespace s21
#endif  // S21_MODEL_H
