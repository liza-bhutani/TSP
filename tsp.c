#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CITIES 10

// Structure to represent an edge with a weight
struct Edge {
    int src, dest, weight;
};

// Function to find the shortest path using Dijkstra's algorithm (unchanged)
void tspDijkstra(int start, int limit, int matrix[MAX_CITIES][MAX_CITIES]) {
    // ...
}

// Function to find the shortest path using Prim's algorithm
void tspPrim(int start, int limit, int matrix[MAX_CITIES][MAX_CITIES]) {
    int parent[MAX_CITIES]; // To store the parent vertices in the MST
    int key[MAX_CITIES];    // To store the key values used for selecting vertices

    // Initialize key values and parent array
    for (int i = 0; i < limit; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }

 // Key value of the starting vertex is always 0
    key[start] = 0;

    for (int count = 0; count < limit - 1; count++) {
        int minKey = INT_MAX;
        int minIndex = -1;

        // Find the vertex with the minimum key value
        for (int v = 0; v < limit; v++) {
            if (key[v] < minKey && parent[v] == -1) {
                minKey = key[v];
                minIndex = v;
            }
        }

        // Mark the selected vertex as part of the MST
        parent[minIndex] = parent[minIndex];

        // Update key values of adjacent vertices
        for (int v = 0; v < limit; v++) {
            if (matrix[minIndex][v] && parent[v] == -1 && matrix[minIndex][v] < key[v]) {
                parent[v] = minIndex;
                key[v] = matrix[minIndex][v];
            }
        }
    }

