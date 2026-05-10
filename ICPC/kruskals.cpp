#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight; // Greedy: Sort by smallest weight
    }
};

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); // Path compression
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) parent[root_i] = root_j;
    }
};

void kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end()); // Step 1: Sort edges (Greedy Choice)
    DSU dsu(n);
    vector<Edge> mst;
    int mst_weight = 0;

    for (Edge& e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) { // Step 2: If no cycle, pick it
            dsu.unite(e.u, e.v);
            mst.push_back(e);
            mst_weight += e.weight;
        }
    }

    cout << "Kruskal's MST Weight: " << mst_weight << endl;
}

int main() {
    int n = 4; // Nodes: 0, 1, 2, 3
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}
    };
    kruskal(n, edges);
    return 0;
}