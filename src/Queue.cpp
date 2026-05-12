#include "../include/Queue.h"

Queue::Queue(int capacity) {
    this->capacity = capacity;
    data = new int[capacity];
    front = 0;
    rear = -1;
    size = 0;
}

Queue::~Queue() {
    delete[] data;
}

void Queue::enqueue(int value) {
    if (!isFull()) {
        rear = (rear + 1) % capacity;
        data[rear] = value;
        size++;
    }
}

int Queue::dequeue() {
    if (!isEmpty()) {
        int value = data[front];
        front = (front + 1) % capacity;
        size--;
        return value;
    }

    return -1;
}

bool Queue::isEmpty() {
    return size == 0;
}

bool Queue::isFull() {
    return size == capacity;
}