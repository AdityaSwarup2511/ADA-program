#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adjMat[MAX][MAX];        
int visited[MAX];            


void BFS(int start, int n, int adjList[MAX][MAX], int listSize[MAX]) {
    int queue[MAX], front = 0, rear = 0;
    
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("BFS Traversal: ");
    while (front < rear) {
        int node = queue[front++];

        printf("%d ", node);

        for (int i = 0; i < listSize[node]; i++) {
            int next = adjList[node][i];
            if (!visited[next]) {
                visited[next] = 1;
                queue[rear++] = next;
            }
        }
    }
    printf("\n");
}


void DFS(int node, int adjList[MAX][MAX], int listSize[MAX]) {
    visited[node] = 1;
    printf("%d ", node);

    for (int i = 0; i < listSize[node]; i++) {
        int next = adjList[node][i];
        if (!visited[next])
            DFS(next, adjList, listSize);
    }
}

int main() {
    int V, E;
    int adjList[MAX][MAX], listSize[MAX] = {0};

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

  
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adjMat[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        
        adjMat[u][v] = 1;
        adjMat[v][u] = 1;

       
        adjList[u][listSize[u]++] = v;
        adjList[v][listSize[v]++] = u;
    }

    
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            printf("%d ", adjMat[i][j]);
        printf("\n");
    }

   
    printf("\nAdjacency List:\n");
    for (int i = 0; i < V; i++) {
        printf("%d -> ", i);
        for (int j = 0; j < listSize[i]; j++)
            printf("%d ", adjList[i][j]);
        printf("\n");
    }

    
    int start;
    printf("\nEnter starting node for BFS: ");
    scanf("%d", &start);
    BFS(start, V, adjList, listSize);

    
    for (int i = 0; i < V; i++) visited[i] = 0;

    printf("\nEnter starting node for DFS: ");
    scanf("%d", &start);

    printf("DFS Traversal: ");
    DFS(start, adjList, listSize);
    printf("\n");

    return 0;
}
