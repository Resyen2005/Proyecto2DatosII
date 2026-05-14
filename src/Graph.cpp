#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>

#include "../include/Graph.h"
#include "../include/Queue.h"
#include "../include/PriorityQueue.h"

using namespace std;

Graph::Graph(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;

    totalNodes = rows * columns;

    adjacencyMatrix = new int*[totalNodes];

    for (int i = 0; i < totalNodes; i++) {
        adjacencyMatrix[i] = new int[totalNodes];

        for (int j = 0; j < totalNodes; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }

    mapGrid = new int*[rows];

    for (int i = 0; i < rows; i++) {
        mapGrid[i] = new int[columns];

        for (int j = 0; j < columns; j++) {
            mapGrid[i][j] = 0;
        }
    }

    srand(time(0));
}

Graph::~Graph() {
    for (int i = 0; i < totalNodes; i++) {
        delete[] adjacencyMatrix[i];
    }

    delete[] adjacencyMatrix;

    for (int i = 0; i < rows; i++) {
        delete[] mapGrid[i];
    }

    delete[] mapGrid;
}

int Graph::getIndex(int row, int column) {
    return row * columns + column;
}

int Graph::getRow(int node) {
    return node / columns;
}

int Graph::getColumn(int node) {
    return node % columns;
}

void Graph::clearAdjacencyMatrix() {
    for (int i = 0; i < totalNodes; i++) {
        for (int j = 0; j < totalNodes; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }
}

void Graph::connectNodes(int firstNode, int secondNode) {
    adjacencyMatrix[firstNode][secondNode] = 1;
    adjacencyMatrix[secondNode][firstNode] = 1;
}

void Graph::buildGraph() {
    clearAdjacencyMatrix();

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {

            if (mapGrid[row][column] == 1) {
                continue;
            }

            int currentNode = getIndex(row, column);

            if (row > 0 && mapGrid[row - 1][column] == 0) {
                int up = getIndex(row - 1, column);
                connectNodes(currentNode, up);
            }

            if (row < rows - 1 && mapGrid[row + 1][column] == 0) {
                int down = getIndex(row + 1, column);
                connectNodes(currentNode, down);
            }

            if (column > 0 && mapGrid[row][column - 1] == 0) {
                int left = getIndex(row, column - 1);
                connectNodes(currentNode, left);
            }

            if (column < columns - 1 && mapGrid[row][column + 1] == 0) {
                int right = getIndex(row, column + 1);
                connectNodes(currentNode, right);
            }
        }
    }
}

void Graph::generateObstacles(int amount) {
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            mapGrid[row][column] = 0;
        }
    }

    int created = 0;
    int attempts = 0;
    int maxAttempts = amount * 100;

    while (created < amount && attempts < maxAttempts) {
        attempts++;

        int row = rand() % rows;
        int column = rand() % columns;

        int node = getIndex(row, column);

        if (node == 0 || node == totalNodes - 1) {
            continue;
        }

        if (mapGrid[row][column] == 0) {
            mapGrid[row][column] = 1;

            buildGraph();

            if (isConnected()) {
                created++;
            }
            else {
                mapGrid[row][column] = 0;
                buildGraph();
            }
        }
    }

    buildGraph();
}

bool Graph::isConnected() {
    bool* visited = new bool[totalNodes];

    for (int i = 0; i < totalNodes; i++) {
        visited[i] = false;
    }

    int startNode = -1;
    int freeNodes = 0;

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            if (mapGrid[row][column] == 0) {
                int node = getIndex(row, column);
                freeNodes++;

                if (startNode == -1) {
                    startNode = node;
                }
            }
        }
    }

    if (startNode == -1) {
        delete[] visited;
        return false;
    }

    Queue queue(totalNodes);
    queue.enqueue(startNode);
    visited[startNode] = true;

    int visitedCount = 0;

    while (!queue.isEmpty()) {
        int currentNode = queue.dequeue();
        visitedCount++;

        for (int neighbor = 0; neighbor < totalNodes; neighbor++) {
            if (adjacencyMatrix[currentNode][neighbor] == 1 && !visited[neighbor]) {
                visited[neighbor] = true;
                queue.enqueue(neighbor);
            }
        }
    }

    delete[] visited;

    return visitedCount == freeNodes;
}

bool Graph::bfs(int startNode, int endNode, int*& path, int& pathSize) {
    path = nullptr;
    pathSize = 0;

    bool* visited = new bool[totalNodes];
    int* previous = new int[totalNodes];

    for (int i = 0; i < totalNodes; i++) {
        visited[i] = false;
        previous[i] = -1;
    }

    Queue queue(totalNodes);

    visited[startNode] = true;
    queue.enqueue(startNode);

    while (!queue.isEmpty()) {
        int currentNode = queue.dequeue();

        if (currentNode == endNode) {
            break;
        }

        for (int neighbor = 0; neighbor < totalNodes; neighbor++) {
            if (adjacencyMatrix[currentNode][neighbor] == 1 && !visited[neighbor]) {
                visited[neighbor] = true;
                previous[neighbor] = currentNode;
                queue.enqueue(neighbor);
            }
        }
    }

    if (!visited[endNode]) {
        delete[] visited;
        delete[] previous;
        return false;
    }

    path = new int[totalNodes];

    int current = endNode;

    while (current != -1) {
        path[pathSize] = current;
        pathSize++;
        current = previous[current];
    }

    for (int i = 0; i < pathSize / 2; i++) {
        int temp = path[i];
        path[i] = path[pathSize - 1 - i];
        path[pathSize - 1 - i] = temp;
    }

    delete[] visited;
    delete[] previous;

    return true;
}

bool Graph::dijkstra(int startNode, int endNode, int*& path, int& pathSize) {
    path = nullptr;
    pathSize = 0;

    int* distance = new int[totalNodes];
    int* previous = new int[totalNodes];
    bool* visited = new bool[totalNodes];

    for (int i = 0; i < totalNodes; i++) {
        distance[i] = INT_MAX;
        previous[i] = -1;
        visited[i] = false;
    }

    PriorityQueue priorityQueue(totalNodes * totalNodes);

    distance[startNode] = 0;
    priorityQueue.push(startNode, 0);

    while (!priorityQueue.isEmpty()) {
        PriorityNode current = priorityQueue.pop();
        int currentNode = current.node;

        if (visited[currentNode]) {
            continue;
        }

        visited[currentNode] = true;

        if (currentNode == endNode) {
            break;
        }

        for (int neighbor = 0; neighbor < totalNodes; neighbor++) {
            if (adjacencyMatrix[currentNode][neighbor] == 1 && !visited[neighbor]) {
                int newDistance = distance[currentNode] + adjacencyMatrix[currentNode][neighbor];

                if (newDistance < distance[neighbor]) {
                    distance[neighbor] = newDistance;
                    previous[neighbor] = currentNode;
                    priorityQueue.push(neighbor, newDistance);
                }
            }
        }
    }

    if (distance[endNode] == INT_MAX) {
        delete[] distance;
        delete[] previous;
        delete[] visited;
        return false;
    }

    path = new int[totalNodes];

    int current = endNode;

    while (current != -1) {
        path[pathSize] = current;
        pathSize++;
        current = previous[current];
    }

    for (int i = 0; i < pathSize / 2; i++) {
        int temp = path[i];
        path[i] = path[pathSize - 1 - i];
        path[pathSize - 1 - i] = temp;
    }

    delete[] distance;
    delete[] previous;
    delete[] visited;

    return true;
}

int Graph::getRandomReachableNode(int startNode, int radius) {
    int startRow = getRow(startNode);
    int startColumn = getColumn(startNode);

    int possibleNodesCount = 0;
    int* possibleNodes = new int[totalNodes];

    for (int row = startRow - radius; row <= startRow + radius; row++) {
        for (int column = startColumn - radius; column <= startColumn + radius; column++) {

            if (row >= 0 && row < rows && column >= 0 && column < columns) {

                if (mapGrid[row][column] == 0) {
                    int node = getIndex(row, column);

                    int* path = nullptr;
                    int pathSize = 0;

                    if (bfs(startNode, node, path, pathSize)) {
                        possibleNodes[possibleNodesCount] = node;
                        possibleNodesCount++;
                        delete[] path;
                    }
                }
            }
        }
    }

    if (possibleNodesCount == 0) {
        delete[] possibleNodes;
        return startNode;
    }

    int randomIndex = rand() % possibleNodesCount;
    int selectedNode = possibleNodes[randomIndex];

    delete[] possibleNodes;

    return selectedNode;
}
//Dibujar el mapa y el camino encontrado en la terminal
void Graph::printMap() {
    cout << "\nMAP\n\n";

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            if (mapGrid[row][column] == 1) {
                cout << "X ";
            }
            else {
                cout << ". ";
            }
        }

        cout << endl;
    }
}

void Graph::printPath(int* path, int pathSize) {
    for (int i = 0; i < pathSize; i++) {
        cout << path[i];

        if (i < pathSize - 1) {
            cout << " -> ";
        }
    }

    cout << endl;
}

// --- FUNCIONES PARA LA INTERFAZ GRÁFICA ---
bool Graph::isObstacle(int row, int column) {
    if (row < 0 || row >= rows || column < 0 || column >= columns) {
        return true; // Si sale de los límites, tratarlo como obstáculo (pared)
    }
    return mapGrid[row][column] == 1; // 1 significa obstáculo en tu código
}

int Graph::getRows() {
    return rows;
}

int Graph::getColumns() {
    return columns;
}