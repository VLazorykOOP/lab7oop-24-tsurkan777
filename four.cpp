
// Клас масиву
template <typename T>
class MyArray {
private:
    T* data;
    int size;

public:
    // Ітератор оголошено як friend
    class MyIterator;

    MyArray(int n) : size(n) {
        data = new T[size];
    }

    ~MyArray() {
        delete[] data;
    }

    T& operator[](int index) {
        return data[index];
    }

    int getSize() const {
        return size;
    }

    // Ітератор: початок
    MyIterator begin() {
        return MyIterator(data);
    }

    // Ітератор: кінець (один елемент після останнього)
    MyIterator end() {
        return MyIterator(data + size);
    }

    // Клас ітератора
    class MyIterator {
    private:
        T* ptr;

    public:
        MyIterator(T* p = nullptr) : ptr(p) {}

        T& operator*() const {
            return *ptr;
        }

        MyIterator& operator++() {
            ++ptr;
            return *this;
        }

        bool operator!=(const MyIterator& other) const {
            return ptr != other.ptr;
        }
    };
};



int main() {
    system("chcp 65001");
    std::cout << "Тест 1: int масив\n";
    const int N1 = 5;
    MyArray<int> arr1(N1);
    for (int i = 0; i < N1; ++i) {
        arr1[i] = (i + 1) * 10;
    }

    std::cout << "Через індексацію: ";
    for (int i = 0; i < N1; ++i) {
        std::cout << arr1[i] << " ";
    }
    std::cout << "\nЧерез ітератор: ";
    MyArray<int>::MyIterator it1 = arr1.begin();
    while (it1 != arr1.end()) {
        std::cout << *it1 << " ";
        ++it1;
    }
    std::cout << "\n\n";

    std::cout << "Тест 2: float масив\n";
    const int N2 = 4;
    MyArray<float> arr2(N2);
    for (int i = 0; i < N2; ++i) {
        arr2[i] = 0.5f * i;
    }

    std::cout << "Через ітератор: ";
    MyArray<float>::MyIterator it2 = arr2.begin();
    while (it2 != arr2.end()) {
        std::cout << *it2 << " ";
        ++it2;
    }
    std::cout << "\n\n";

    std::cout << "Тест 3: char масив\n";
    const int N3 = 6;
    MyArray<char> arr3(N3);
    for (int i = 0; i < N3; ++i) {
        arr3[i] = 'A' + i;
    }

    std::cout << "Через ітератор: ";
    MyArray<char>::MyIterator it3 = arr3.begin();
    while (it3 != arr3.end()) {
        std::cout << *it3 << " ";
        ++it3;
    }
    std::cout << "\n\n";

    std::cout << "Тест 4: порожній масив\n";
    MyArray<int> arr4(0);
    std::cout << "Через ітератор: ";
    MyArray<int>::MyIterator it4 = arr4.begin();
    while (it4 != arr4.end()) {
        std::cout << *it4 << " ";
        ++it4;
    }


    return 0;
}
