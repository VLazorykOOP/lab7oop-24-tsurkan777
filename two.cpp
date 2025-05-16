#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

template <typename T>
void insertionSort(T* array, int size) {
    for (int i = 1; i < size; ++i) {
        T key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            --j;
        }

        array[j + 1] = key;
    }
}


template <>
void insertionSort<char*>(char** array, int size) {
    for (int i = 1; i < size; ++i) {
        char* key = array[i];
        int j = i - 1;

        // Порівнюємо C-рядки лексикографічно
        while (j >= 0 && std::strcmp(array[j], key) > 0) {
            array[j + 1] = array[j];
            --j;
        }

        array[j + 1] = key;
    }
}

// З клавіатури
template <typename T>
void inputFromKeyboard(T* array, int size) {
    std::cout << "Введіть " << size << " елементів:\n";
    for (int i = 0; i < size; ++i) {
        std::cin >> array[i];
    }
}

// З файлу
template <typename T>
bool inputFromFile(T* array, int size, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) return false;

    for (int i = 0; i < size && !inFile.eof(); ++i) {
        inFile >> array[i];
    }

    inFile.close();
    return true;
}

// Випадкові значення
template <typename T>
void inputRandom(T* array, int size, T min = 0, T max = 100) {
    for (int i = 0; i < size; ++i) {
        array[i] = static_cast<T>(min + rand() % int(max - min + 1));
    }
}

// Введення для char* з клавіатури
void inputCharStarKeyboard(char** array, int size) {
    std::cout << "Введіть " << size << " слів:\n";
    char buffer[256];
    for (int i = 0; i < size; ++i) {
        std::cin >> buffer;
        array[i] = strdup(buffer);
    }
}

// Введення для char* з файлу
bool inputCharStarFile(char** array, int size, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) return false;
    char buffer[256];
    int i = 0;
    while (i < size && inFile >> buffer) {
        array[i++] = strdup(buffer);
    }
    inFile.close();
    return true;
}

// Випадкові char* (з фіксованого списку)
void inputCharStarRandom(char** array, int size) {
    const char* sampleWords[] = {"apple", "banana", "orange", "grape", "kiwi", "melon", "peach"};
    int sampleSize = sizeof(sampleWords) / sizeof(sampleWords[0]);
    for (int i = 0; i < size; ++i) {
        array[i] = strdup(sampleWords[rand() % sampleSize]);
    }
}


int main() {
    system("chcp 65001");
    srand(static_cast<unsigned>(time(nullptr)));

    const int size = 5;

    // Тест: int з клавіатури
    int arr1[size];
    inputFromKeyboard(arr1, size);
    insertionSort(arr1, size);
    std::cout << "Відсортований int: ";
    for (int i = 0; i < size; ++i) std::cout << arr1[i] << " ";
    std::cout << "\n";

    // Тест: float з файлу
    float arr2[size];
    if (inputFromFile(arr2, size, "input.txt")) {
        insertionSort(arr2, size);
        std::cout << "Відсортований float (з файлу): ";
        for (int i = 0; i < size; ++i) std::cout << arr2[i] << " ";
        std::cout << "\n";
    } else {
        std::cerr << "Не вдалося відкрити файл input.txt\n";
    }

    // Тест: double випадкові числа
    double arr3[5];
    inputRandom(arr3, 5);
    insertionSort(arr3, size);
    std::cout << "Відсортований double (random): ";
    for (int i = 0; i < size; ++i) std::cout << arr3[i] << " ";
    std::cout << "\n";

    // Тест: char* з випадковими словами
    char* arr4[size];
    inputCharStarRandom(arr4, size);
    insertionSort(arr4, size);
    std::cout << "Відсортовані char* (random): ";
    for (int i = 0; i < size; ++i) std::cout << arr4[i] << " ";
    std::cout << "\n";

    // Звільнення пам’яті
    for (int i = 0; i < size; ++i) delete[] arr4[i];

    return 0;
}
