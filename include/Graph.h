#ifndef GRAPH_H
#define GRAPH_H

class Graph {
private:
    int rows;
    int columns;
    int totalNodes;

    int** adjacencyMatrix;
    int** mapGrid;

    void clearAdjacencyMatrix();
    void connectNodes(int firstNode, int secondNode);

public:
    Graph(int rows, int columns);
    ~Graph();

    int getIndex(int row, int column);
    int getRow(int node);
    int getColumn(int node);

    void buildGraph();

    void generateObstacles(int amount);
    bool isConnected();

    bool bfs(int startNode, int endNode, int*& path, int& pathSize);
    bool dijkstra(int startNode, int endNode, int*& path, int& pathSize);

    int getRandomReachableNode(int startNode, int radius);

    void printMap();
    void printPath(int* path, int pathSize);
};

#endif