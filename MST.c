#include <stdio.h>

#define MAX 100
#define INF 9999

struct Edge {
    int u, v, weight;
};

int parent[MAX];

int find(int x) {
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

void unionSet(int a, int b) {
    a = find(a);
    b = find(b);
    parent[b] = a;
}

void prims(int n, int cost[MAX][MAX]) {
    int selected[MAX] = {0};
    int edges = 0, min, x, y, total = 0;
    int i, j;

    selected[0] = 1;

    printf("\nPrim's MST:\n");

    while (edges < n - 1) {
        min = INF;
        x = y = -1;

        for (i = 0; i < n; i++) {
            if (selected[i]) {
                for (j = 0; j < n; j++) {
                    if (!selected[j] && cost[i][j] < min) {
                        min = cost[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }

        if (x == -1)
            break;

        printf("%d - %d : %d\n", x, y, min);
        total += min;
        selected[y] = 1;
        edges++;
    }

    printf("Minimum Cost = %d\n", total);
}

void kruskals(int n, int e, struct Edge edges[]) {
    int i, j, count = 0, total = 0;
    struct Edge temp;

    for (i = 0; i < n; i++)
        parent[i] = i;

    for (i = 0; i < e - 1; i++) {
        for (j = 0; j < e - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    printf("\nKruskal's MST:\n");

    for (i = 0; i < e && count < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (find(u) != find(v)) {
            printf("%d - %d : %d\n", u, v, edges[i].weight);
            total += edges[i].weight;
            unionSet(u, v);
            count++;
        }
    }

    printf("Minimum Cost = %d\n", total);
}

int main() {
    int n, e, choice;
    int cost[MAX][MAX];
    struct Edge edges[MAX];
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);

            if (cost[i][j] == 0)
                cost[i][j] = INF;
        }
    }

    e = 0;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (cost[i][j] != INF) {
                edges[e].u = i;
                edges[e].v = j;
                edges[e].weight = cost[i][j];
                e++;
            }
        }
    }

    printf("\n1. Prim's Algorithm");
    printf("\n2. Kruskal's Algorithm");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
        prims(n, cost);
    else if (choice == 2)
        kruskals(n, e, edges);
    else
        printf("Invalid choice\n");

    return 0;
}
