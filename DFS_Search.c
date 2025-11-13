#include <stdio.h>

void DFS_Util(int node, int visited[], int n, int adj[n][n]) {
    visited[node] = 1;
    printf("%d ", node);

    for (int i = 0; i < n; i++) {
        if (adj[node][i] == 1 && visited[i] == 0) {
            DFS_Util(i, visited, n, adj);
        }
    }
}

void DFS(int start, int n, int adj[n][n]) {
    int visited[n];

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("DFS Traversal: ");
    DFS_Util(start, visited, n, adj);
}

int main() {
    int n = 5;

    // Adjacency matrix
    int adj[5][5] = {
        {0,1,1,0,0},
        {1,0,1,1,0},
        {1,1,0,0,1},
        {0,1,0,0,1},
        {0,0,1,1,0}
    };

    int start = 0;

    DFS(start, n, adj);

    return 0;
}
