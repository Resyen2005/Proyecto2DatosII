#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

struct PriorityNode {
    int node;
    int priority;
};

class PriorityQueue {
private:
    PriorityNode* heap;
    int capacity;
    int size;

    void swapNodes(int firstIndex, int secondIndex);
    void moveUp(int index);
    void moveDown(int index);

public:
    PriorityQueue(int capacity);
    ~PriorityQueue();

    void push(int node, int priority);
    PriorityNode pop();

    bool isEmpty();
};

#endif