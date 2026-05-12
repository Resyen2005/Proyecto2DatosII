#ifndef POWER_UP_QUEUE_H
#define POWER_UP_QUEUE_H

enum PowerUpType {
    DOUBLE_TURN,
    MOVEMENT_PRECISION,
};

class PowerUpQueue {
private:
    PowerUpType* data;
    int capacity;
    int front;
    int rear;
    int size;

public:
    PowerUpQueue(int capacity);
    ~PowerUpQueue();

    void enqueue(PowerUpType powerUp);
    PowerUpType dequeue();

    bool isEmpty();
    bool isFull();
};

#endif