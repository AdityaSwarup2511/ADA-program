#include <stdio.h>
#include <limits.h>

struct Edge {
    int src, dest, weight;
};

void bellmanFord(int vertices, int edges, struct Edge edge[], int start) {
    int dist[vertices];

    
    for (int i = 0; i < vertices; i++)
        dist[i] = INT_MAX;
    dist[start] = 0;

    
    for (int i = 1; i <= vertices - 1; i++) {
        for (int j = 0; j < edges; j++) {
            int u = edge[j].src;
            int v = edge[j].dest;
            int w = edge[j].weight;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    
    for (int j = 0; j < edges; j++) {
        int u = edge[j].src;
        int v = edge[j].dest;
        int w = edge[j].weight;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("Graph contains a NEGATIVE weight cycle!\n");
            return;
        }
    }

  
    printf("Vertex \t Distance from Source %d\n", start);
    for (int i = 0; i < vertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

int main() {
    int vertices = 5;  
    int edges = 8;     

    struct Edge edge[] = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };

    bellmanFord(vertices, edges, edge, 0); 

    return 0;
}
