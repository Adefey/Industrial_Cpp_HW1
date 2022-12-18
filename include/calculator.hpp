/*Copyright 2022 Adefe*/
#include <cmath>
#include <stdexcept>
#include <string>

#ifndef INCLUDE_CALCULATOR_HPP_
#define INCLUDE_CALCULATOR_HPP_

namespace CalculatorProject {

using std::invalid_argument;
using std::runtime_error;
using std::stod;
using std::string;

enum class Operation {
  ADD, // +
  SUB, // -
  MUL, // *
  DIV, // /
  POW, // ^
  NOP, // value
};

struct Expression {
  double value = 0;
  Operation op = Operation::NOP;
  Expression *left = nullptr;
  Expression *right = nullptr;
};

class Calculator {
private:
  Expression *CreateExpression(const string &expression);
  double CalculateExpression(Expression *expression);
  void DisposeExpression(Expression *expression);
  Expression *ParseValue(string &str);
  Expression *ParsePow(string &str);
  Expression *ParseMulDiv(string &str);
  Expression *ParseAddSub(string &str);
  void SkipSpaces(string &expression);
  bool ParseDouble(string &expression, double &result);
  bool ParseOperator(string &expression, Operation &op);

public:
  double operator()(const string &expression);
};
} // namespace CalculatorProject
#endif // INCLUDE_CALCULATOR_HPP_
