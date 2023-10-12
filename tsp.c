#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CITIES 10

// Structure to represent an edge with a weight
struct Edge {
    int src, dest, weight;
};

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
// Function to find the shortest path using Dijkstra's algorithm (unchanged)
void tspDijkstra(int start, int limit, int matrix[MAX_CITIES][MAX_CITIES]) {
    int dist[MAX_CITIES];    // To store the minimum distance from the starting vertex
    int visited[MAX_CITIES]; // To track whether a vertex has been visited
    int parent[MAX_CITIES];  // To store the parent vertices in the shortest path

    // Initialize dist and visited arrays
    for (int i = 0; i < limit; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0; // Initially, no vertices have been visited
    }

    // The distance from the starting vertex to itself is always 0
    dist[start] = 0;

    // Initialize the parent of the starting vertex
    parent[start] = -1;

    // Dijkstra's algorithm
    for (int count = 0; count < limit - 1; count++) {
        // Find the vertex with the minimum distance that has not been visited
        int minDist = INT_MAX;
        int minIndex = -1;

        for (int v = 0; v < limit; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        // Mark the selected vertex as visited
        visited[minIndex] = 1;

        // Update distances of adjacent vertices
        for (int v = 0; v < limit; v++) {
            if (!visited[v] && matrix[minIndex][v] && dist[minIndex] != INT_MAX && dist[minIndex] + matrix[minIndex][v] < dist[v]) {
                dist[v] = dist[minIndex] + matrix[minIndex][v];
                parent[v] = minIndex;
            }
        }
    }

    // Print the shortest path and its cost
    printf("Shortest Path (Dijkstra's Algorithm) from %c:\n", 'A' + start);
    for (int i = 0; i < limit; i++) {
        if (i != start) {
            printf("Path to %c: ", 'A' + i);
            int currentNode = i;
            while (currentNode != start) {
                printf("%c <- ", 'A' + currentNode);
                currentNode = parent[currentNode];
            }
            printf("%c", 'A' + start);
            printf("  Cost: %d\n", dist[i]);
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

    // Print the MST edges and calculate the minimum cost
    int cost = 0;
    printf("Minimum Spanning Tree (Prim's Algorithm):\n");
    for (int i = 0; i < limit; i++) {
        if (parent[i] != -1) {
            printf("%c - %c\n", 'A' + parent[i], 'A' + i);
            cost += matrix[i][parent[i]];
        }
    }
    printf("Minimum Cost: %d\n", cost);
}



int main() {
    int limit;
    printf("Enter Total Number of Cities (maximum %d):\t", MAX_CITIES);
    scanf("%d", &limit);

    if (limit < 2 || limit > MAX_CITIES) {
        printf("Invalid number of cities. Please enter a valid number between 2 and %d.\n", MAX_CITIES);
        return 1;
    }

    int matrix[MAX_CITIES][MAX_CITIES];

    printf("\nEnter Cost Matrix (enter 0 for self to self, -1 for unreachable cities):\n");
    for (int i = 0; i < limit; i++) {
        for (int j = 0; j < limit; j++) {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] < -1) {
                printf("Invalid cost. Please enter a non-negative cost or -1 for unreachable cities.\n");
                return 1;
            }
        }
    }

    printf("\nChoose an algorithm:\n");
    printf("1. Dijkstra's Algorithm\n");
    printf("2. Prim's Algorithm\n");
    printf("3. Kruskal's Algorithm\n");

    int choice;
    scanf("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("Invalid choice. Please select a valid algorithm (1, 2, or 3).\n");
        return 1;
    }

    printf("Enter the starting city (A, B, C, ...):\t");
    char startCity;
    scanf(" %c", &startCity);

    if (startCity < 'A' || startCity >= 'A' + limit) {
        printf("Invalid starting city. Please enter a valid city label.\n");
        return 1;
    }

    int start = startCity - 'A';

    switch (choice) {
        case 1:
            tspDijkstra(start, limit, matrix);
            break;
        case 2:
            tspPrim(start, limit, matrix);
            break;
        case 3:
            tspKruskal(start, limit, matrix);
            break;
    }

    return 0;

}
