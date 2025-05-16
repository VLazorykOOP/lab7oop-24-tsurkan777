#include <iostream>

template <typename T>
class CircularQueue {
private:
    T* data;
    int capacity;
    int front;
    int rear;
    int count;

public:
    CircularQueue(int size) {
        capacity = size;
        data = new T[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~CircularQueue() {
        delete[] data;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == capacity;
    }

    void enqueue(T value) {
        if (isFull()) {
            std::cerr << "Черга переповнена!\n";
            return;
        }
        rear = (rear + 1) % capacity;
        data[rear] = value;
        ++count;
    }

    T dequeue() {
        if (isEmpty()) {
            std::cerr << "Черга порожня!\n";
            return T(); // Значення за замовчуванням
        }
        T value = data[front];
        front = (front + 1) % capacity;
        --count;
        return value;
    }

    T peek() const {
        if (isEmpty()) {
            std::cerr << "Черга порожня!\n";
            return T();
        }
        return data[front];
    }

    void display() const {
        if (isEmpty()) {
            std::cout << "Черга порожня\n";
            return;
        }
        std::cout << "Черга: ";
        for (int i = 0; i < count; ++i) {
            int index = (front + i) % capacity;
            std::cout << data[index] << " ";
        }
        std::cout << "\n";
    }
};
int main() {
    system("chcp 65001");
    CircularQueue<int> q(5);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.display();

    std::cout << "Видалено: " << q.dequeue() << "\n";
    q.display();

    q.enqueue(50);
    q.enqueue(60);
    q.display();

    std::cout << "Поточний перший елемент: " << q.peek() << "\n";

    return 0;
}
