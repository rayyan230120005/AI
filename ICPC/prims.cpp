#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii; // {weight, node}

void prim(int n, vector<vector<pii>>& adj) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<bool> inMST(n, false);
    vector<int> key(n, 1e9); 
    int mst_weight = 0;

    // Start from node 0
    pq.push({0, 0});
    key[0] = 0;

    cout << "Prim's MST Construction:" << endl;
    while (!pq.empty()) {
        int w = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        mst_weight += w;
        if (w != 0) cout << "Added edge with weight: " << w << endl;

        for (auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }
    cout << "Total MST Weight: " << mst_weight << endl;
}