#include <iostream>

class SetOperations {
public:
    // Функция для объединения двух множеств
    static void unionSets(int set1[], int size1, int set2[], int size2) {
        int result[100]; // Массив для хранения результата 
        int index = 0;

        // Добавляем элементы из первого множества
        for (int i = 0; i < size1; i++) {
            result[index++] = set1[i];
        }

        // Добавляем элементы из второго множества, если их нет в первом
        for (int i = 0; i < size2; i++) {
            bool found = false;
            for (int j = 0; j < size1; j++) {
                if (set2[i] == set1[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                result[index++] = set2[i];
            }
        }

        // Вывод результата
        std::cout << "Объединение множеств: ";
        for (int i = 0; i < index; i++) {
            std::cout << result[i] << " ";
        }
        std::cout << std::endl;
    }

    // Функция для пересечения двух множеств
    static void intersectionSets(int set1[], int size1, int set2[], int size2) {
        int result[100]; // Массив для хранения результата
        int index = 0;

        // Ищем пересечение
        for (int i = 0; i < size1; i++) {
            for (int j = 0; j < size2; j++) {
                if (set1[i] == set2[j]) {
                    result[index++] = set1[i];
                    break; // Выходим из внутреннего цикла, если нашли совпадение
                }
            }
        }

        // Вывод результата
        std::cout << "Пересечение множеств: ";
        for (int i = 0; i < index; i++) {
            std::cout << result[i] << " ";
        }
        std::cout << std::endl;
    }

    // Функция для разности множеств set1 - set2
    static void differenceSets(int set1[], int size1, int set2[], int size2) {
        int result[100]; // Массив для хранения результата
        int index = 0;

        // Ищем элементы, которых нет во втором множестве
        for (int i = 0; i < size1; i++) {
            bool found = false;
            for (int j = 0; j < size2; j++) {
                if (set1[i] == set2[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                result[index++] = set1[i];
            }
        }

        // Вывод результата
        std::cout << "Разность множеств (set1 - set2): ";
        for (int i = 0; i < index; i++) {
            std::cout << result[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    int set1[100], set2[100]; // Массивы для хранения множеств
    int size1, size2;

    // Ввод первого множества
    std::cout << "Введите количество элементов первого множества: ";
    std::cin >> size1;
    std::cout << "Введите элементы первого множества: ";
    for (int i = 0; i < size1; i++) {
        std::cin >> set1[i];
    }

    // Ввод второго множества
    std::cout << "Введите количество элементов второго множества: ";
    std::cin >> size2;
    std::cout << "Введите элементы второго множества: ";
    for (int i = 0; i < size2; i++) {
        std::cin >> set2[i];
    }

    // Выполнение операций
    SetOperations::unionSets(set1, size1, set2, size2);
    SetOperations::intersectionSets(set1, size1, set2, size2);
    SetOperations::differenceSets(set1, size1, set2, size2);

    return 0;
}
