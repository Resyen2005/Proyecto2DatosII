#include <iostream>
#include "../include/Graph.h"
#include "../include/Queue.h"
#include <cstdlib>
#include <ctime>
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

void Graph::buildGraph() {

    for (int row = 0; row < rows; row++) {

        for (int column = 0; column < columns; column++) {

            int currentNode = getIndex(row, column);

            // UP
            if (row > 0) {

                int up = getIndex(row - 1, column);

                adjacencyMatrix[currentNode][up] = 1;
            }

            // DOWN
            if (row < rows - 1) {

                int down = getIndex(row + 1, column);

                adjacencyMatrix[currentNode][down] = 1;
            }

            // LEFT
            if (column > 0) {

                int left = getIndex(row, column - 1);

                adjacencyMatrix[currentNode][left] = 1;
            }

            // RIGHT
            if (column < columns - 1) {

                int right = getIndex(row, column + 1);

                adjacencyMatrix[currentNode][right] = 1;
            }
        }
    }
}

void Graph::bfs(int startNode, int endNode) {

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

            if (adjacencyMatrix[currentNode][neighbor] == 1 &&
                !visited[neighbor]) {

                visited[neighbor] = true;

                previous[neighbor] = currentNode;

                queue.enqueue(neighbor);
            }
        }
    }

    if (!visited[endNode]) {

        cout << "No path found.\n";
    }
    else {

        cout << "Path found with BFS: ";

        int* path = new int[totalNodes];

        int pathSize = 0;

        int current = endNode;

        while (current != -1) {

            path[pathSize] = current;

            pathSize++;

            current = previous[current];
        }

        for (int i = pathSize - 1; i >= 0; i--) {

            cout << path[i];

            if (i > 0) {
                cout << " -> ";
            }
        }

        cout << endl;

        delete[] path;
    }

    delete[] visited;
    delete[] previous;
}
void Graph::generateObstacles(int amount) {

    srand(time(0));

    int created = 0;

    while (created < amount) {

        int row = rand() % rows;
        int column = rand() % columns;

        if (mapGrid[row][column] == 0) {

            mapGrid[row][column] = 1;

            int obstacleNode = getIndex(row, column);

            for (int i = 0; i < totalNodes; i++) {
                adjacencyMatrix[obstacleNode][i] = 0;
                adjacencyMatrix[i][obstacleNode] = 0;
            }

            created++;
        }
    }
}

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