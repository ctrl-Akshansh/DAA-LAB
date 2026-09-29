#include <stdio.h>
#include <limits.h>

struct Edge {
    int src;
    int dest;
    int weight;
};

void bellmanFord(struct Edge edges[], int V, int E, int source) {
    int dist[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }

    dist[source] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INT_MAX &&
                dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dist[u] != INT_MAX &&
            dist[u] + w < dist[v]) {
            printf("Graph contains a negative-weight cycle.\n");
            return;
        }
    }

    printf("Shortest distances from source %d:\n", source);

    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("Vertex %d: INF\n", i);
        else
            printf("Vertex %d: %d\n", i, dist[i]);
    }
}

int main() {
    int V = 5;
    int E = 8;

    struct Edge edges[] = {
        {0, 1, 6},
        {0, 2, 7},
        {1, 2, 8},
        {1, 3, 5},
        {1, 4, -4},
        {2, 3, -3},
        {3, 1, -2},
        {4, 3, 7}
    };

    int source = 0;

    bellmanFord(edges, V, E, source);

    return 0;
}
