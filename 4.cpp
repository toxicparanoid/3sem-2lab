#include <iostream>

using namespace std;

class DynamicArray {
private:
    string* arr;
    int capacity;
    int size;

public:
    DynamicArray(int cap) {
        capacity = cap;
        size = 0;
        arr = new string[capacity];
    }

    ~DynamicArray() {
        delete[] arr;
    }

    void add(const string& element) {
        if (size < capacity) {
            arr[size++] = element;
        }
        else {
            wcout << L"Массив достиг максимальной ёмкости." << endl;
        }
    }

    int getSize() const {
        return size;
    }

    string getElement(int index) const {
        if (index < size) {
            return arr[index];
        }
        return "";
    }
};

void generateSubarrays(DynamicArray& inputArray, int start, int end, string current) {
    if (start > end) {
        cout << "{" << current << "}" << endl;
        return;
    }

    // включаем элемент массива
    generateSubarrays(inputArray, start + 1, end, current.empty() ? inputArray.getElement(start) : current + ", " + inputArray.getElement(start));
    // Исключаем элемент массива
    generateSubarrays(inputArray, start + 1, end, current);
}

int main() {
    setlocale(LC_ALL, "rus");
    int n;

    wcout << L"Введите количество элементов в массиве: ";
    cin >> n;

    DynamicArray array(n);
    wcout << L"Введите элементы массива: " << endl;

    for (int i = 0; i < n; ++i) {
        string element;
        cin >> element;
        array.add(element);
    }

    wcout << L"Все различные подмассивы:" << endl;
    generateSubarrays(array, 0, array.getSize() - 1, "");

    return 0;
}
