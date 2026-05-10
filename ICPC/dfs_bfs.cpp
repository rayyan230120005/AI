#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>

using namespace std;

class Graph {
    // Using a map to handle non-integer or disjoint vertex IDs easily
    map<int, vector<int>> adj;

public:
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    // --- Breadth First Search ---
    void BFS(int startNode) {
        map<int, bool> visited;
        queue<int> q;

        visited[startNode] = true;
        q.push(startNode);

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int curr = q.front();
            cout << curr << " ";
            q.pop();

            for (int neighbor : adj[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // --- Recursive Depth First Search ---
    void DFS(int curr, map<int, bool>& visited) {
        visited[curr] = true;
        cout << curr << " ";

        for (int neighbor : adj[curr]) {
            if (!visited[neighbor]) {
                DFS(neighbor, visited);
            }
        }
    }

    // Wrapper for DFS to initialize the visited map
    void startDFS(int startNode) {
        map<int, bool> visited;
        cout << "DFS Traversal: ";
        DFS(startNode, visited);
        cout << endl;
    }
};

int main() {
    Graph g;
    // Constructing a sample graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    g.BFS(0);
    g.startDFS(0);

    return 0;
}