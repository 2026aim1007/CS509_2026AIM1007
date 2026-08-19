#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <unordered_set>
#include <algorithm>
#include <string>

using namespace std;

// Structure to hold edge data for generation and MST calculation
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// DSU structure for calculating the Expected MST weight natively
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

void generateTestCase(int V) {
    // 1. Calculate Target Edges (E = 3V for sparsity)
    long long max_possible_edges = (long long)V * (V - 1) / 2;
    long long target_E = min((long long)V * 3, max_possible_edges);

    vector<Edge> edges;
    unordered_set<long long> seen;
    mt19937 rng(42); // Deterministic seed so tests are reproducible

    auto get_key = [&](int u, int v) {
        if (u > v) swap(u, v);
        return (long long)u * V + v;
    };

    // 2. Build a random Spanning Tree to guarantee the graph is connected
    for (int i = 1; i < V; i++) {
        uniform_int_distribution<int> dist(0, i - 1);
        int u = i;
        int v = dist(rng);
        
        uniform_int_distribution<int> w_dist(1, 1000);
        int w = w_dist(rng);
        
        edges.push_back({u, v, w});
        seen.insert(get_key(u, v));
    }

    // 3. Add remaining random edges until we hit target E
    uniform_int_distribution<int> v_dist(0, V - 1);
    uniform_int_distribution<int> w_dist(1, 1000);
    
    while (edges.size() < target_E) {
        int u = v_dist(rng);
        int v = v_dist(rng);
        if (u == v) continue; // No self-loops
        
        long long key = get_key(u, v);
        if (seen.find(key) == seen.end()) {
            edges.push_back({u, v, w_dist(rng)});
            seen.insert(key);
        }
    }

    int E = edges.size();

    // 4. Populate undirected adjacency list
    vector<vector<pair<int, int>>> adj(V);
    for (auto& e : edges) {
        adj[e.u].push_back({e.v, e.weight});
        adj[e.v].push_back({e.u, e.weight});
    }

    // 5. Write Graph Text File
    string testFile = "tests/mst_" + to_string(V) + ".txt";
    ofstream tOut(testFile);
    tOut << V << " " << E << "\n";
    for (int i = 0; i < V; i++) {
        tOut << i << " " << adj[i].size();
        for (auto& neighbor : adj[i]) {
            tOut << " " << neighbor.first << " " << neighbor.second;
        }
        tOut << "\n";
    }
    tOut.close();
    cout << "Generated: " << testFile << " (V=" << V << ", E=" << E << ")\n";

    // 6. Compute Kruskal's to find Expected Output
    sort(edges.begin(), edges.end());
    DSU dsu(V);
    long long mst_weight = 0;
    vector<Edge> mst_edges;
    
    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst_edges.push_back(e);
            mst_weight += e.weight;
        }
    }

    // 7. Write Expected Output File
    string expFile = "outputs/expected_mst_" + to_string(V) + ".txt";
    ofstream eOut(expFile);
    bool printEdges = (V == 10 || V == 100);

    eOut << "Algorithm: Kruskal's MST\n";
    if (printEdges) {
        eOut << "MST edges:\n";
        for (auto& e : mst_edges) eOut << e.u << " " << e.v << " " << e.weight << "\n";
    } else {
        eOut << "(Edges hidden for large graph)\n";
    }
    eOut << "Total MST weight: " << mst_weight << "\n";

    eOut << "Algorithm: Prim's MST\n";
    if (printEdges) {
        eOut << "MST edges:\n";
        for (auto& e : mst_edges) eOut << e.u << " " << e.v << " " << e.weight << "\n";
    } else {
        eOut << "(Edges hidden for large graph)\n";
    }
    eOut << "Total MST weight: " << mst_weight << "\n";
    
    eOut.close();
    cout << "Generated: " << expFile << " (Weight=" << mst_weight << ")\n";
}

int main() {
    cout << "--- Starting MST Test Case Generator ---\n";
    
    // Required sizes per assignment specs
    vector<int> sizes = {10, 100, 10000, 50000, 100000};
    
    for (int V : sizes) {
        generateTestCase(V);
    }
    
    cout << "--- Generation Complete! ---\n";
    return 0;
}