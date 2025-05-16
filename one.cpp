#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

// Загальний шаблон
template<typename T>
double average(T* array, int size) {
    if (size == 0) return 0;
    T sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }
    return static_cast<double>(sum) / size;
}

// Спеціалізація для char*
template<>
double average<char*>(char** array, int size) {
    if (size == 0) return 0;
    int totalLength = 0;
    for (int i = 0; i < size; ++i) {
        totalLength += std::strlen(array[i]);
    }
    return static_cast<double>(totalLength) / size;
}
// Введення з клавіатури
template<typename T>
void inputFromKeyboard(T* array, int size) {
    std::cout << "Введіть " << size << " елементів:\n";
    for (int i = 0; i < size; ++i) {
        std::cin >> array[i];
    }
}

// Введення з файлу
template<typename T>
bool inputFromFile(T* array, int size, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) return false;

    for (int i = 0; i < size && !inFile.eof(); ++i) {
        inFile >> array[i];
    }

    inFile.close();
    return true;
}

// Генерація випадкових чисел
template<typename T>
void inputRandom(T* array, int size, T min = 0, T max = 100) {
    for (int i = 0; i < size; ++i) {
        array[i] = static_cast<T>(min + rand() % (max - min + 1));
    }
}


int main() {
    system("chcp 65001");
    srand(static_cast<unsigned>(time(nullptr)));

    // Тест 1: int, з клавіатури
    const int size1 = 5;
    int arr1[size1];
    inputFromKeyboard(arr1, size1);
    std::cout << "Середнє (int): " << average(arr1, size1) << "\n";

    // Тест 2: double, з файлу
    const int size2 = 4;
    double arr2[size2];
    if (inputFromFile(arr2, size2, "input.txt")) {
        std::cout << "Середнє (double, з файлу): " << average(arr2, size2) << "\n";
    } else {
        std::cerr << "Помилка відкриття файлу.\n";
    }

    // Тест 3: int, випадкові значення
    const int size3 = 6.0;
    int arr3[size3];
    inputRandom(arr3, size3, 0, 10);
    std::cout << "Згенеровано int: ";
    for (float f : arr3) std::cout << f << " ";
    std::cout << "\nСереднє (int): " << average(arr3, size3) << "\n";

    // Тест 4: char*
    const int size4 = 3;
    char* arr4[size4] = {strdup("hello"), strdup("world"), strdup("GPT")};
    std::cout << "Середня довжина рядків (char*): " << average(arr4, size4) << "\n";

    // Звільнення пам’яті
    for (int i = 0; i < size4; ++i) delete[] arr4[i];

    return 0;
}
