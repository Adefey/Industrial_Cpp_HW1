/*Copyright 2022 Adefe*/

#include <gtest/gtest.h>

#include <cmath>
#include <string>

#include <calculator.hpp>

#define EPS 1e-8

using CalculatorProject::Calculator;
using std::string;

TEST(CalculatorTest, TestSubstract) {
  Calculator calculator;
  string expression = "1-2";
  double result = calculator(expression);
  EXPECT_TRUE(abs(result - (-1.0)) < EPS);
}

TEST(CalculatorTest, TestMultiply) {
  Calculator calculator;
  string expression = "256*1024";
  double result = calculator(expression);
  EXPECT_TRUE(abs(result - 262144.0) < EPS);
}

TEST(CalculatorTest, TestPower) {
  Calculator calculator;
  string expression = "2^8";
  double result = calculator(expression);
  EXPECT_TRUE(abs(result - 256.0) < EPS);
}

TEST(CalculatorTest, TestFailure) {
  Calculator calculator;
  string expression = "1a1";
  EXPECT_ANY_THROW(calculator(expression));
  expression = "1--1";
  EXPECT_ANY_THROW(calculator(expression));
  expression = "a";
  EXPECT_ANY_THROW(calculator(expression));
  expression = "123/-1";
  EXPECT_ANY_THROW(calculator(expression));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
