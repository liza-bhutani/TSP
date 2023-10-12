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
