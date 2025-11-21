#include <iostream>
#include <string>
#include "doubly_linked_list.h"
#include "dynamic_array.h"
#include "stack.h"
#include "expression_calculator.h"

void demonstrateStructures() {
    std::cout << "Двусвязный список" << std::endl;
    DoublyLinkedList<int> list;
    list.push_back(23);
    list.push_back(89);
    list.push_back(36);
    std::cout << "Исходный список: ";
    list.print();

    list.insert(1, 65);
    std::cout << "После вставки элемента: ";
    list.print();

    list.remove(3);
    std::cout << "После удаления элемента: ";
    list.print();

    std::cout << "\nДинамический массив" << std::endl;
    DynamicArray<int> array;
    array.push_back(10);
    array.push_back(24);
    array.push_back(36);
    std::cout << "Исходный массив: ";
    array.print();

    array.insert(2, 57);
    std::cout << "После вставки элемента: ";
    array.print();

    array.remove(0);
    std::cout << "После удаления элемента: ";
    array.print();

    std::cout << "\nСтек" << std::endl;
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    std::cout << "Все элементы стека: ";
    stack.print();
    std::cout << "Размер стека: " << stack.size() << std::endl;
    std::cout << "Верхний элемент: " << stack.peek() << std::endl;
}



int main() {
    setlocale(LC_ALL, "Russian");

    demonstrateStructures();

    std::cout << "\nСортировочная станция" << std::endl;
    std::cout << "Введите выражение (разделяйте все символы пробелами):" << std::endl;
    std::cout << "Для выхода введите 'exit'" << std::endl;

    ExpressionCalculator interactiveCalc;
    std::string input;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit") break;
        if (input.empty()) continue;

        try {
            std::string postfix = interactiveCalc.getPostfixNotation(input);
            double result = interactiveCalc.calculate(input);
            std::cout << "Постфиксная запись: " << postfix << std::endl;
            std::cout << "Результат: " << result << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }

    return 0;
}