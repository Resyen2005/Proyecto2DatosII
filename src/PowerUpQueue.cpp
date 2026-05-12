#include "../include/PowerUpQueue.h"

PowerUpQueue::PowerUpQueue(int capacity) {
    this->capacity = capacity;
    data = new PowerUpType[capacity];
    front = 0;
    rear = -1;
    size = 0;
}

PowerUpQueue::~PowerUpQueue() {
    delete[] data;
}

void PowerUpQueue::enqueue(PowerUpType powerUp) {
    if (!isFull()) {
        rear = (rear + 1) % capacity;
        data[rear] = powerUp;
        size++;
    }
}

PowerUpType PowerUpQueue::dequeue() {
    if (!isEmpty()) {
        PowerUpType powerUp = data[front];
        front = (front + 1) % capacity;
        size--;
        return powerUp;
    }

    return DOUBLE_TURN;
}

bool PowerUpQueue::isEmpty() {
    return size == 0;
}

bool PowerUpQueue::isFull() {
    return size == capacity;
}