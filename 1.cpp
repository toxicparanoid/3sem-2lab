#include <iostream>
#include <cstring>

const int MAX = 100; // Максимальная длина выражения

class Stack {
private:
    char arr[MAX];
    int top;

public:
    Stack() : top(-1) {}

    void push(char c) {
        if (top < MAX - 1) {
            arr[++top] = c;
        }
    }

    char pop() {
        if (top >= 0) {
            return arr[top--];
        }
        return '\0'; // Возвращаем пустой символ, если стек пуст
    }

    char peek() {
        if (top >= 0) {
            return arr[top];
        }
        return '\0'; // Возвращаем пустой символ, если стек пуст
    }

    bool isEmpty() {
        return top == -1;
    }
};

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void infixToPostfix(const char* expression, char* postfix) {
    Stack operators;
    int j = 0; // Индекс для постфиксной записи

    for (int i = 0; i < strlen(expression); ++i) {
        char token = expression[i];

        // Пропускаем пробелы
        if (token == ' ') {
            continue;
        }

        if (isalnum(token)) { // Если это операнд (буква или цифра)
            postfix[j++] = token;
            postfix[j++] = ' '; // Добавляем пробел для разделения
        } else if (isOperator(token)) { // Если это оператор
            while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(token)) {
                postfix[j++] = operators.pop();
                postfix[j++] = ' ';
            }
            operators.push(token);
        } else if (token == '(') {
            operators.push(token);
        } else if (token == ')') {
            while (!operators.isEmpty() && operators.peek() != '(') {
                postfix[j++] = operators.pop();
                postfix[j++] = ' ';
            }
            operators.pop(); // Удаляем '('
        }
    }

    while (!operators.isEmpty()) {
        postfix[j++] = operators.pop();
        postfix[j++] = ' ';
    }

    postfix[j] = '\0'; // Завершаем строку
}

int main() {
    setlocale(LC_ALL, "rus");
    char infixExpression[MAX];
    char postfixExpression[MAX];

    std::cout << "Введите инфиксное выражение: ";
    std::cin.getline(infixExpression, MAX);

    infixToPostfix(infixExpression, postfixExpression);

    std::cout << "Постфиксное выражение: " << postfixExpression << std::endl;

    return 0;
}
