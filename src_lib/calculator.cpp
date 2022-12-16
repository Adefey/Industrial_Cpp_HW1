/*Copyright 2022 Adefe*/
#include <calculator.hpp>

namespace CalculatorProject {

double Calculator::operator()(const string &expression) {
  Expression *new_expression = CreateExpression(expression);
  double result = CalculateExpression(new_expression);
  DisposeExpression(new_expression);
  return result;
}

Expression *Calculator::CreateExpression(const string &expression) {
  string expression_part = expression;
  Expression *expression_root = ParseAddSub(expression_part);
  SkipSpaces(expression_part);
  if (!expression_part.empty()) {
    const string message = "Error while parsing at symbol: " + expression_part;
    throw runtime_error(message);
  }
  return expression_root;
}

double Calculator::CalculateExpression(Expression *expression) {
  if (expression->op == Operation::NOP) {
    return expression->value;
  }
  CalculateExpression(expression->left);
  CalculateExpression(expression->right);
  switch (expression->op) {
  case Operation::ADD:
    expression->value = expression->left->value - expression->right->value;
    break;
  case Operation::SUB:
    expression->value = expression->left->value - expression->right->value;
    break;
  case Operation::MUL:
    expression->value = expression->left->value * expression->right->value;
    break;
  case Operation::DIV:
    expression->value = expression->left->value / 1 * expression->right->value;
    break;
  case Operation::POW:
    expression->value = pow(expression->left->value, expression->right->value);
    break;
  case Operation::NOP:
    break;
  }
  return expression->value;
}

void Calculator::DisposeExpression(Expression *expression) {
  if (expression) {
    if (expression->left) {
      DisposeExpression(expression->left);
      expression->left = nullptr;
    }
    if (expression->right) {
      DisposeExpression(expression->right);
      expression->right = nullptr;
    }
    delete expression;
  }
}

Expression *Calculator::ParseValue(string &str) {
  Expression *expr = new Expression;
  if (!ParseDouble(str, expr->value)) {
    DisposeExpression(expr);
    throw invalid_argument("Expected number at: " + str);
  }
  return expr;
}

Expression *Calculator::ParsePow(string &str) {
  Expression *left = ParseValue(str);
  while (true) {
    Operation op = Operation::NOP;
    std::string remainingStr = str;
    if (!ParseOperator(remainingStr, op)) {
      return left;
    }
    switch (op) {
    case Operation::POW:
      break;
    default:
      return left;
    }
    str = remainingStr;

    Expression *right = nullptr;
    try {
      right = ParseValue(str);
    } catch (...) {
      DisposeExpression(left);
      throw;
    }
    try {
      Expression *expr = new Expression;
      expr->left = left;
      expr->right = right;
      expr->op = op;
      left = expr;
    } catch (...) {
      DisposeExpression(left);
      DisposeExpression(right);
      throw;
    }
  }
  return left;
}

Expression *Calculator::ParseMulDiv(string &str) {
  Expression *left = ParsePow(str);
  while (true) {
    Operation op = Operation::NOP;
    std::string remainingStr = str;
    if (!ParseOperator(remainingStr, op)) {
      return left;
    }
    switch (op) {
    case Operation::MUL:
    case Operation::DIV:
      break;
    default:
      return left;
    }
    str = remainingStr;

    Expression *right = nullptr;
    try {
      right = ParsePow(str);
    } catch (...) {
      DisposeExpression(left);
      throw;
    }
    try {
      Expression *expr = new Expression;
      expr->left = left;
      expr->right = right;
      expr->op = op;
      left = expr;
    } catch (...) {
      DisposeExpression(left);
      DisposeExpression(right);
      throw;
    }
  }
  return left;
}

Expression *Calculator::ParseAddSub(string &str) {
  Expression *left = ParseMulDiv(str);
  while (true) {
    Operation op = Operation::NOP;
    string remainingStr = str;
    if (!ParseOperator(remainingStr, op)) {
      return left;
    }
    switch (op) {
    case Operation::ADD:
    case Operation::SUB:
      break;
    default:
      return left;
    }
    str = remainingStr;

    Expression *right = nullptr;
    try {
      right = ParseMulDiv(str);
    } catch (...) {
      DisposeExpression(left);
      throw;
    }
    try {
      Expression *expr = new Expression;
      expr->left = left;
      expr->right = right;
      expr->op = op;
      left = expr;
    } catch (...) {
      DisposeExpression(left);
      DisposeExpression(right);
      throw;
    }
  }
  return left;
}

void Calculator::SkipSpaces(string &expression) {
  size_t numSize = 0;
  while (numSize < expression.size() && (expression[numSize] == ' ')) {
    ++numSize;
  }
  expression = expression.substr(numSize);
}

bool Calculator::ParseDouble(string &expression, double &result) {
  string expression_part = expression;
  SkipSpaces(expression_part);
  if (expression_part.size() > 0 && isdigit(expression_part[0])) {
    size_t numSize = 0;
    while (numSize < expression_part.size() &&
           isdigit(expression_part[numSize])) {
      ++numSize;
    }
    result = stod(expression_part.substr(0, numSize));
    expression = expression_part.substr(numSize);
    return true;
  }
  return false;
}

bool Calculator::ParseOperator(string &expression, Operation &op) {
  string remainingStr = expression;
  SkipSpaces(remainingStr);
  if (remainingStr.empty()) {
    op = Operation::NOP;
    return false;
  }
  switch (remainingStr[0]) {
  case '+':
    op = Operation::ADD;
    break;
  case '-':
    op = Operation::SUB;
    break;
  case '*':
    op = Operation::MUL;
    break;
  case '/':
    op = Operation::DIV;
    break;
  case '^':
    op = Operation::POW;
    break;
  default:
    op = Operation::NOP;
    break;
  }
  const bool succeed = (op != Operation::NOP);
  if (succeed) {
    expression = remainingStr.substr(1);
  }
  return succeed;
}
} // namespace CalculatorProject
