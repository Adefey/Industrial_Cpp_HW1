/*Copyright 2022 Adefe*/

#include <cstdlib>
#include <iostream>
#include <string>

#include <calculator.hpp>

using CalculatorProject::Calculator;
using std::cerr;
using std::cout;
using std::exception;
using std::string;

int main(int argc, const char **argv) {
  if (argc != 2) {
    cerr << "Wrong number of parameters; Usage: ./Exe [expression]"
         << std::endl;
    return EXIT_FAILURE;
  }
  string expression = argv[1];
  Calculator calculator;
  double result = 0;
  try {
    result = calculator(expression);
  } catch (const exception &ex) {
    cerr << "Error occured: " << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
  cout.precision(17);
  cout << result << std::endl;
  return EXIT_SUCCESS;
}
