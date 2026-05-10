#ifndef GRAPH_H
#define GRAPH_H

class Graph {
private:
    int rows;
    int columns;
    int totalNodes;

    int** adjacencyMatrix;
    int** mapGrid;

public:
    Graph(int rows, int columns);
    ~Graph();

    int getIndex(int row, int column);

    void buildGraph();
    void printMatrix();
    void bfs(int startNode, int endNode);

    void generateObstacles(int amount);
    void printMap();
};

#endif