#include <stdio.h>
#include <stdlib.h>

int comparator(const void *p1, const void *p2) {
    const int *a = (const int *)p1;
    const int *b = (const int *)p2;
    return a[2] - b[2];  
}

void makeset(int parent[], int rank[], int vertices) {
    for (int i = 0; i < vertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findparent(int parent[], int component) {
    if (parent[component] == component)
        return component;

    return parent[component] = findparent(parent, parent[component]);
}

void unionset(int u, int v, int parent[], int rank[]) {
    u = findparent(parent, u);
    v = findparent(parent, v);

    if (u != v) {
        if (rank[u] < rank[v]) {
            parent[u] = v;
        } else if (rank[v] < rank[u]) {
            parent[v] = u;
        } else {
            parent[v] = u;
            rank[u]++;
        }
    }
}

int kruskal(int vertices, int edges_count, int edge[][3]) {
    qsort(edge, edges_count, sizeof(edge[0]), comparator);

    int parent[vertices];
    int rank[vertices];

    makeset(parent, rank, vertices);

    int mincost = 0;

    for (int i = 0; i < edges_count; i++) {
        int u = edge[i][0];
        int v = edge[i][1];
        int wt = edge[i][2];

        if (findparent(parent, u) != findparent(parent, v)) {
            unionset(u, v, parent, rank);
            mincost += wt;
        }
    }

    return mincost;
}

int main() {
    int edges[5][3] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    int vertices = 4;
    int edges_count = 5;

    printf("Minimum Cost = %d\n", kruskal(vertices, edges_count, edges));
    return 0;
}
