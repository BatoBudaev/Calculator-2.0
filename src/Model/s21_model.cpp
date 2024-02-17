#include "s21_model.h"

#include "s21_stack.h"

namespace s21 {
Model::Model() : result(0), noError(true) {}

Model::~Model() = default;

double Model::getResult() const { return result; }

[[maybe_unused]] bool Model::isNoError() const { return noError; }

int Model::isOperator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

int Model::getPriority(char c) {
  int priority = -1;

  if (c == '(') {
    priority = 0;
  } else if (c == '+' || c == '-') {
    priority = 1;
  } else if (c == '*' || c == '/' || c == '%') {
    priority = 2;
  } else if (c == '^') {
    priority = 3;
  } else if (c == 'c' || c == 's' || c == 't' || c == 'C' || c == 'S' ||
             c == 'T' || c == 'Q' || c == 'L' || c == 'l') {
    priority = 4;
  }

  return priority;
}

bool Model::convertToPostfix(const char *expression, char *postfix) {
  s21::Stack stack;

  int i = 0, j = 0;

  char prevChar = '\0';
  int prevIsOperand = 0;

  while (expression[i] != '\0') {
    char current = expression[i];

    if (isspace(current)) {
      i++;
      continue;
    }

    if (isdigit(current) || current == '.' || current == 'x') {
      if (prevIsOperand == 1 || (!isdigit(prevChar) && current == '.')) {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неправильное выражение\n");

        return false;
      }

      while (isdigit(expression[i]) || expression[i] == '.' ||
             expression[i] == 'x') {
        postfix[j++] = expression[i++];
      }

      postfix[j++] = ' ';
      i--;
      prevIsOperand = 1;
    } else if (isalpha(current)) {
      if (prevIsOperand == 1) {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неправильное выражение\n");

        return false;
      }

      char function[5] = {'\0'};
      int k = 0;

      while (isalpha(expression[i])) {
        function[k++] = expression[i++];
      }

      i--;

      if (strcmp(function, "cos") == 0) {
        stack.push('c');
      } else if (strcmp(function, "sin") == 0) {
        stack.push('s');
      } else if (strcmp(function, "tan") == 0) {
        stack.push('t');
      } else if (strcmp(function, "acos") == 0) {
        stack.push('C');
      } else if (strcmp(function, "asin") == 0) {
        stack.push('S');
      } else if (strcmp(function, "atan") == 0) {
        stack.push('T');
      } else if (strcmp(function, "sqrt") == 0) {
        stack.push('Q');
      } else if (strcmp(function, "ln") == 0) {
        stack.push('L');
      } else if (strcmp(function, "log") == 0) {
        stack.push('l');
      } else {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неизвестная функция \n");

        return false;
      }

      prevIsOperand = 1;
    } else if (isOperator(current)) {
      if ((current == '-' || current == '+') &&
          (i == 0 || expression[i - 1] == '(' || expression[i - 1] == '^')) {
        if (current == '-') {
          if (i == 0) {
            stack.push('-');
          } else {
            stack.push('_');
          }
        } else {
          stack.push('#');
        }
      } else if (isOperator(prevChar) || prevIsOperand == 0 ||
                 (isalpha(prevChar) && prevChar != 'x')) {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неправильное выражение\n");

        return false;
      } else {
        while (!stack.isEmpty() && stack.getData(stack.getTop()) != '(' &&
               getPriority(stack.getData(stack.getTop())) >=
                   getPriority(current)) {
          if ((current == '^' && stack.getData(stack.getTop()) == '^')) {
            break;
          } else {
            postfix[j++] = stack.popChar();
            postfix[j++] = ' ';
          }
        }

        stack.push(current);
      }

      prevIsOperand = 0;
    } else if (current == '(') {
      if (prevIsOperand == 1 && (!isalpha(prevChar) || prevChar == 'x')) {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неправильное выражение\n");

        return false;
      }

      stack.push(current);
      prevIsOperand = 0;
    } else if (current == ')') {
      if (prevChar == '(' || prevIsOperand == 0) {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неправильное выражение\n");

        return false;
      }

      while (!stack.isEmpty() && stack.getData(stack.getTop()) != '(') {
        postfix[j++] = stack.popChar();
        postfix[j++] = ' ';
      }

      if (!stack.isEmpty() && stack.getData(stack.getTop()) == '(') {
        stack.popChar();
      } else {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неправильное выражение\n");

        return false;
      }

      prevIsOperand = 1;
    }

    prevChar = current;
    i++;
  }

  while (!stack.isEmpty()) {
    if (stack.getData(stack.getTop()) == '(') {
      memset(postfix, 0, MAX_SIZE);
      printf("Ошибка: неправильное выражение\n");

      return false;
    }

    postfix[j++] = stack.popChar();
    postfix[j++] = ' ';
  }

  postfix[j] = '\0';
  std::cout << "Postfix: " << postfix << std::endl;

  return true;
}

double Model::calculatePostfix(char *postfix, double x) {
  if (strlen(postfix) == 0) {
    return 0;
  }

  s21::Stack stack;
  int i = 0;

  while (postfix[i] != '\0') {
    if (postfix[i] == 'x') {
      stack.push(x);
      i++;
    } else if (isdigit(postfix[i])) {
      char *endPtr;
      double number = strtod(&postfix[i], &endPtr);
      stack.push(number);
      i = endPtr - postfix;
    } else if (postfix[i] == ' ') {
      i++;
    } else {
      double operand1 = 0, operand2;

      switch (postfix[i]) {
        case '+':
          operand2 = stack.popDouble();
          if (!stack.isEmpty()) {
            operand1 = stack.popDouble();
          }
          stack.push(operand1 + operand2);
          break;
        case '-':
          operand2 = stack.popDouble();
          if (!stack.isEmpty()) {
            operand1 = stack.popDouble();
          }
          stack.push(operand1 - operand2);
          break;
        case '_':
          operand2 = stack.popDouble();
          stack.push(-1 * operand2);
          break;
        case '#':
          break;
        case '*':
          operand2 = stack.popDouble();
          if (!stack.isEmpty()) {
            operand1 = stack.popDouble();
          }
          stack.push(operand1 * operand2);
          break;
        case '/':
          operand2 = stack.popDouble();
          if (!stack.isEmpty()) {
            operand1 = stack.popDouble();
          }
          stack.push(operand1 / operand2);
          break;
        case '%':
          operand2 = stack.popDouble();
          if (!stack.isEmpty()) {
            operand1 = stack.popDouble();
          }
          stack.push(fmod(operand1, operand2));
          break;
        case '^':
          operand2 = stack.popDouble();
          if (!stack.isEmpty()) {
            operand1 = stack.popDouble();
          }
          stack.push(pow(operand1, operand2));
          break;
        case 'c':
          operand2 = stack.popDouble();
          stack.push(cos(operand2));
          break;
        case 's':
          operand2 = stack.popDouble();
          stack.push(sin(operand2));
          break;
        case 't':
          operand2 = stack.popDouble();
          stack.push(tan(operand2));
          break;
        case 'C':
          operand2 = stack.popDouble();
          stack.push(acos(operand2));
          break;
        case 'S':
          operand2 = stack.popDouble();
          stack.push(asin(operand2));
          break;
        case 'T':
          operand2 = stack.popDouble();
          stack.push(atan(operand2));
          break;
        case 'Q':
          operand2 = stack.popDouble();
          stack.push(sqrt(operand2));
          break;
        case 'L':
          operand2 = stack.popDouble();
          stack.push(log(operand2));
          break;
        case 'l':
          operand2 = stack.popDouble();
          stack.push(log10(operand2));
          break;
        default:
          std::cout << "Ошибка: неизвестный оператор: " << postfix[i]
                    << std::endl;
      }
      i++;
    }
  }

  return stack.popDouble();
}

void Model::processExpression(const char *infixExpression, double x) {
  char postfixExpression[MAX_SIZE];
  noError = convertToPostfix(infixExpression, postfixExpression);

  std::cout << "Postfix Expression: " << postfixExpression << std::endl;
  result = calculatePostfix(postfixExpression, x);
}
}  // namespace s21
