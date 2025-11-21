#include "expression_calculator.h"
#include <iostream>

bool ExpressionCalculator::isOperator(const std::string& token) const {
    return token == "+" || token == "-" ||  token == "*" ||
        token == "/" || token == "^";
}

bool ExpressionCalculator::isFunction(const std::string& token) const {
    return token == "sin" || token == "cos";
}

int ExpressionCalculator::getPriority(const std::string& op) const {
    if (op == "sin" || op == "cos") return 4;
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

DynamicArray<std::string> ExpressionCalculator::tokenize(const std::string& expression) const {
    DynamicArray<std::string> tokens;
    std::stringstream ss(expression);
    std::string token;

    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

DynamicArray<std::string> ExpressionCalculator::infixToPostfix(const DynamicArray<std::string>& infixTokens) const {
    DynamicArray<std::string> postfix;
    Stack<std::string> operators;

    for (int i = 0; i < infixTokens.getSize(); i++) {
        const std::string& token = infixTokens[i];

        // Проверка на унарный минус
        bool isUnaryMinus = false;
        if (token == "-") {
            if (i == 0 || infixTokens[i - 1] == "(" || isOperator(infixTokens[i - 1])) {
                isUnaryMinus = true;
            }
        }

        if (isdigit(token[0]) || (isUnaryMinus && i + 1 < infixTokens.getSize() && isdigit(infixTokens[i + 1][0]))) {
            if (isUnaryMinus) {
                std::string number = "-" + infixTokens[i + 1];
                postfix.push_back(number);
                i++;
            }
            else {
                postfix.push_back(token);
            }
        }
        else if (isFunction(token)) {
            operators.push(token);
        }
        else if (token == "(") {
            operators.push(token);
        }
        else if (token == ")") {
            while (!operators.isEmpty() && operators.peek() != "(") {
                postfix.push_back(operators.pop());
            }
            if (!operators.isEmpty() && operators.peek() == "(") {
                operators.pop();
            }
            if (!operators.isEmpty() && isFunction(operators.peek())) {
                postfix.push_back(operators.pop());
            }
        }
        else if (isOperator(token)) {
            if (isUnaryMinus) {
                operators.push("~"); // Специальный символ для унарного минуса
            }
            else {
                while (!operators.isEmpty() &&
                    getPriority(operators.peek()) >= getPriority(token) &&
                    operators.peek() != "(") {
                    postfix.push_back(operators.pop());
                }
                operators.push(token);
            }
        }
    }

    while (!operators.isEmpty()) {
        postfix.push_back(operators.pop());
    }

    return postfix;
}

double ExpressionCalculator::evaluatePostfix(const DynamicArray<std::string>& postfixTokens) const {
    Stack<double> values;

    for (int i = 0; i < postfixTokens.getSize(); i++) {
        const std::string& token = postfixTokens[i];

        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
            values.push(std::stod(token));
        }
        else if (token == "~") {
            if (values.isEmpty()) throw std::runtime_error("Not enough operands for unary minus");
            double operand = values.pop();
            values.push(-operand);
        }
        else if (isFunction(token)) {
            if (values.isEmpty()) throw std::runtime_error("Not enough operands");
            double operand = values.pop();
            if (token == "sin") values.push(sin(operand));
            else if (token == "cos") values.push(cos(operand));
        }
        else {
            if (values.size() < 2) throw std::runtime_error("Not enough operands");
            double b = values.pop();
            double a = values.pop();

            if (token == "+") values.push(a + b);
            else if (token == "-") values.push(a - b);
            else if (token == "*") values.push(a * b);
            else if (token == "/") {
                if (b == 0) throw std::runtime_error("Division by zero");
                values.push(a / b);
            }
            else if (token == "^") values.push(pow(a, b));
        }
    }

    if (values.size() != 1) throw std::runtime_error("Invalid expression");
    return values.pop();
}

double ExpressionCalculator::calculate(const std::string& expression) {
    DynamicArray<std::string> tokens = tokenize(expression);
    DynamicArray<std::string> postfix = infixToPostfix(tokens);
    return evaluatePostfix(postfix);
}

std::string ExpressionCalculator::getPostfixNotation(const std::string& expression) {
    DynamicArray<std::string> tokens = tokenize(expression);
    DynamicArray<std::string> postfix = infixToPostfix(tokens);

    std::string result;
    for (int i = 0; i < postfix.getSize(); i++) {
        if (postfix[i] == "~") {
            result += "-";
        }
        else {
            result += postfix[i];
        }
        if (i < postfix.getSize() - 1) {
            result += " ";
        }
    }
    return result;
}