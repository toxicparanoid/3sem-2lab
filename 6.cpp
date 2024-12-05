#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Определяем класс для представления узла дерева
class TreeNode {
public:
    string name;
    vector<TreeNode*> children;
    
    TreeNode(const string& name) : name(name) {}
};

// Рекурсивная функция для подсчета потомков
int countDescendants(TreeNode* node, map<string, int>& descendantsCount) {
    int count = 0;
    for (auto child : node->children) {
        count += 1 + countDescendants(child, descendantsCount);
    }
    descendantsCount[node->name] = count;
    return count;
}

int main() {
    int N;
    cin >> N; // Считываем количество элементов в древе
    
    string child, parent;
    map<string, TreeNode*> nodes;

    // Считываем родительские отношения
    for (int i = 0; i < N - 1; ++i) {
        cin >> child >> parent;

        if (nodes.find(parent) == nodes.end()) {
            nodes[parent] = new TreeNode(parent);
        }
        if (nodes.find(child) == nodes.end()) {
            nodes[child] = new TreeNode(child);
        }

        nodes[parent]->children.push_back(nodes[child]);
    }

    // Находим корень дерева (родоначальника)
    TreeNode* root = nullptr;
    for (const auto& pair : nodes) {
        bool isChild = false;
        for (const auto& otherPair : nodes) {
            for (auto childNode : otherPair.second->children) {
                if (childNode == pair.second) {
                    isChild = true;
                    break; // Если нашли, что это потомок, то выходим из цикла
                }
            }
            if (isChild) break; // Выходим если нашли
        }
        if (!isChild) { // Если не нашли, то это родоначальник
            root = pair.second;
            break;
        }
    }

    map<string, int> descendantsCount;
    countDescendants(root, descendantsCount); // Подсчитываем потомков

    // Сортируем и выводим элементы в лексикографическом порядке
    // Сначала собираем имена
    vector<string> names;
    for (const auto& pair : nodes) {
        names.push_back(pair.first);
    }

    // Бульбашковая сортировка для упрощения (поскольку не используем другие библиотеки)
    for (size_t i = 0; i < names.size(); ++i) {
        for (size_t j = i + 1; j < names.size(); ++j) {
            if (names[i] > names[j]) {
                swap(names[i], names[j]);
            }
        }
    }

    // Выводим имя и количество потомков
    for (const auto& name : names) {
        cout << name << " " << descendantsCount[name] << endl;
    }

    // Освобождаем память
    for (const auto& pair : nodes) {
        delete pair.second;
    }

    return 0;
}
