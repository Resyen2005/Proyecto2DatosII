#ifndef QUEUE_H
#define QUEUE_H

class Queue {
private:
    int* data;
    int capacity;
    int front;
    int rear;
    int size;

public:
    Queue(int capacity);
    ~Queue();

    void enqueue(int value);
    int dequeue();

    bool isEmpty();
    bool isFull();
};

#endif