#include <iostream>
#include <string>

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRec(root, value);
    }

    int height() {
        return heightRec(root);
    }

private:
    Node* root;

    Node* insertRec(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->value) {
            node->left = insertRec(node->left, value);
        } else if (value > node->value) {
            node->right = insertRec(node->right, value);
        }
        return node; // возвращаем неизмененный указатель узла
    }

    int heightRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = heightRec(node->left);
        int rightHeight = heightRec(node->right);
        return std::max(leftHeight, rightHeight) + 1;
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    BinarySearchTree bst;
    std::string input;

    std::wcout << L"Введите числа: " << std::endl;

    while (true) {
        std::getline(std::cin, input);
        if (input.empty()) { // проверяем, если строка пустая, завершаем ввод
            break;
        }
        try {
            int value = std::stoi(input); // пробуем преобразовать строку в число
            bst.insert(value);
        } catch (std::invalid_argument& e) {
            std::wcout << L"Некорректный ввод, введите целое число." << std::endl;
        } catch (std::out_of_range& e) {
            std::wcout << L"Число вне диапазона." << std::endl;
        }
    }

    int treeHeight = bst.height();
    std::wcout << L"Высота дерева: " << treeHeight << std::endl;

    return 0;
}
