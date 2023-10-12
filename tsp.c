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

void tspKruskal(int start, int limit, int matrix[MAX_CITIES][MAX_CITIES]) {
    struct Edge edges[MAX_CITIES * MAX_CITIES];
    int edgeCount = 0; // Count of edges in the graph

    // Populate the 'edges' array with edges from the graph
    for (int i = 0; i < limit; i++) {
        for (int j = i + 1; j < limit; j++) {
            if (matrix[i][j] != 0) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = matrix[i][j];
                edgeCount++;
            }
        }
    }

    // Sort the edges based on their weights (using bubble sort for simplicity)
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                // Swap the edges
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Create a data structure to represent sets of vertices (disjoint-set)
    int parent[MAX_CITIES];

    for (int i = 0; i < limit; i++) {
        parent[i] = i; // Initialize each vertex as its own parent
    }

    int mstEdges = 0; // Count of edges in the MST
    int cost = 0;     // Total cost of the MST

    printf("Minimum Spanning Tree (Kruskal's Algorithm):\n");

    for (int i = 0; i < edgeCount; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;

        // Find the parent of the source and destination vertices
        int srcParent = src;
        while (parent[srcParent] != srcParent) {
            srcParent = parent[srcParent];
        }
        int destParent = dest;
        while (parent[destParent] != destParent) {
            destParent = parent[destParent];
        }

        // Check if adding this edge creates a cycle
        if (srcParent != destParent) {
            // Add the edge to the MST
            printf("%c - %c\n", 'A' + src, 'A' + dest);
            cost += edges[i].weight;

            // Union the sets of source and destination vertices
            parent[srcParent] = destParent;

            mstEdges++;
            if (mstEdges == limit - 1) {
                break; // MST is complete
            }
        }
    }

    printf("Minimum Cost: %d\n", cost);
}
