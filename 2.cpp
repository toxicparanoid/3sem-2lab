#include <iostream> 
#include <fstream>  
#include <string>   

using namespace std; 

// Структура для представления узла в связном списке
struct Node {
    int data;
    Node* next;
};

// Структура для представления множества с использованием хеш-таблицы
struct Set {
    Node** table;
    int size;

    // Конструктор, инициализирующий таблицу нулевыми указателями
    Set(int tableSize) : size(tableSize) {
        table = new Node*[size](); // Выделение памяти для столов и инициализация их нулями
    }
    // Хеш-функция для вычисления индекса в таблице по значению
    int hash(int value) const {
        return value % size;
    }

    // Метод для добавления значения в множество
    void add(int value) {
        // Проверка, содержится ли уже значение в множестве
        if (contains(value)) {
            cout << "Уже есть значение в set:" << value << endl;
            return; 
        }
        
        int index = hash(value); // Вычисление индекса для хранения
        Node* newNode = new Node{value, nullptr}; // Создание нового узла

        // Если по индексу еще нет узла, добавляем его
        if (table[index] == nullptr) {
            table[index] = newNode; 
        } 
        // Если уже есть узел, добавляем новый узел в начало связного списка
        else {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    // Метод для удаления значения из множества
    void remove(int value) {
        int index = hash(value); // Получение индекса
        Node** current = &table[index]; // Указатель на текущий узел
        // Проходим по связанному списку
        while (*current!=nullptr) {
            if ((*current)->data == value) { // Если значение найдено
                Node* toDelete = *current; // Сохраняем узел для удаления
                *current = (*current)->next; // Переносим указатель на следующий узел
                delete toDelete; // Освобождаем память
                return; // Выход из функции
            }
            current = &((*current)->next); // Переход к следующему узлу
        }
    }

    // Метод для проверки наличия значения в множестве
    bool contains(int value) const {
        int index = hash(value); // Получение индекса
        Node* current = table[index]; // Указатель на первый узел
        // Проходим по связанному списку
        while (current) {
            if (current->data == value) { // Если значение найдено
                return true; // Возвращаем true
            }
            current = current->next; // Переход к следующему узлу
        }
        return false; // Если значение не найдено, возвращаем false
    }

    // Деструктор для освобождения памяти
    ~Set() {
        for (int i = 0; i < size; ++i) { // Проход по всем индексам
            Node* current = table[i]; // Указатель на текущий узел
            while (current) { // Пока есть узлы
                Node* toDelete = current; // Сохраняем узел для удаления
                current = current->next; // Сохраняем следующий узел
                delete toDelete; // Освобождаем память
            }
        }
        delete[] table; // Освобождение памяти для массива указателей
    }

    // Метод для сохранения элементов множества в файл
    void saveToFile(const char* filename) const {
        ofstream file(filename); // Открытие файла для записи
        for (int i = 0; i < size; ++i) { // Проход по всем индексам
            Node* current = table[i]; // Указатель на текущий узел
            while (current) { // Пока есть узлы
                file << current->data << endl; // Запись значения в файл
                current = current->next; // Переход к следующему узлу
            }

        }
        file.close(); 
    }

// Метод для загрузки значений из файла в множество
    void loadFromFile(const char* filename) {
        ifstream file(filename); // Открытие файла для чтения
        int value; // Переменная для хранения считанного значения
        while (file >> value) { // Чтение значений из файла до конца
            add(value); // Добавление считанного значения в множество
        }
        file.close(); 
    }
};

// Функция для выполнения команд над множеством
void executeCommand(Set& set, const string& command, int value) {
    if (command == "SETADD") { // Проверка на команду добавления
        set.add(value); // Вызов метода добавления
    } else if (command == "SETDEL") { // Проверка на команду удаления
        set.remove(value); // Вызов метода удаления
    } else if (command == "SET_AT") { // Проверка на команду проверки наличия
        cout << (set.contains(value) ? "YES" : "NO") << endl; 
    }
}

int main(int argc, char* argv[]) {
    // Проверка количества аргументов командной строки
    if (argc != 6) {
        cerr << "Usage: " << argv[0] << " --file <path to file> --query <command>" << endl; // Сообщение об ошибке
        return 1; // Выход с ошибкой
    }

    const char* filename = argv[2]; // Получение имени файла из аргументов
    const string command = argv[4]; // Получение команды из аргументов
    int value = stoi(argv[5]); // Преобразование аргумента в целое число

    Set set(100); // Создание множества с размером хеш-таблицы 100
    set.loadFromFile(filename); // Загрузка данных из файла в множество

    // Выполнение команды над множеством
    executeCommand(set, command, value);

    set.saveToFile(filename); // Сохранение изменений в файл

    return 0; // Успешный выход из программы
}