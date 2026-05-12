#include "../include/PriorityQueue.h"

PriorityQueue::PriorityQueue(int capacity) {
    this->capacity = capacity;
    size = 0;
    heap = new PriorityNode[capacity];
}

PriorityQueue::~PriorityQueue() {
    delete[] heap;
}

void PriorityQueue::swapNodes(int firstIndex, int secondIndex) {
    PriorityNode temp = heap[firstIndex];
    heap[firstIndex] = heap[secondIndex];
    heap[secondIndex] = temp;
}

void PriorityQueue::moveUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (heap[index].priority < heap[parent].priority) {
            swapNodes(index, parent);
            index = parent;
        }
        else {
            break;
        }
    }
}

void PriorityQueue::moveDown(int index) {
    while (true) {
        int leftChild = index * 2 + 1;
        int rightChild = index * 2 + 2;
        int smallest = index;

        if (leftChild < size && heap[leftChild].priority < heap[smallest].priority) {
            smallest = leftChild;
        }

        if (rightChild < size && heap[rightChild].priority < heap[smallest].priority) {
            smallest = rightChild;
        }

        if (smallest != index) {
            swapNodes(index, smallest);
            index = smallest;
        }
        else {
            break;
        }
    }
}

void PriorityQueue::push(int node, int priority) {
    if (size < capacity) {
        heap[size].node = node;
        heap[size].priority = priority;
        moveUp(size);
        size++;
    }
}

PriorityNode PriorityQueue::pop() {
    PriorityNode result;

    if (isEmpty()) {
        result.node = -1;
        result.priority = -1;
        return result;
    }

    result = heap[0];

    heap[0] = heap[size - 1];
    size--;

    moveDown(0);

    return result;
}

bool PriorityQueue::isEmpty() {
    return size == 0;
}