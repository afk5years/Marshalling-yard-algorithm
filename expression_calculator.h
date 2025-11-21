#ifndef EXPRESSION_CALCULATOR_H
#define EXPRESSION_CALCULATOR_H

#include "stack.h"
#include "dynamic_array.h"
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <cctype>

class ExpressionCalculator {
private:
    bool isOperator(const std::string& token) const;
    bool isFunction(const std::string& token) const;
    int getPriority(const std::string& op) const;
    DynamicArray<std::string> tokenize(const std::string& expression) const;
    DynamicArray<std::string> infixToPostfix(const DynamicArray<std::string>& infixTokens) const;
    double evaluatePostfix(const DynamicArray<std::string>& postfixTokens) const;

public:
    double calculate(const std::string& expression);
    std::string getPostfixNotation(const std::string& expression);
};

#endif
