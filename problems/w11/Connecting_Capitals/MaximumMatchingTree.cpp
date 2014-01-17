#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

int matching(int vertex, int parent, vii& adj, vi& M) {
    if(M[vertex] != -1) return M[vertex];
    
    int total = 0;
    for(int c = 0; c < adj[vertex].size(); ++c) {
        if(adj[vertex][c] == parent) continue;
        int child = adj[vertex][c];
        total += matching(child, vertex, adj, M);
    }
    int Mprime = total; // crucial, otherwise I increment M[vertex] everytime I iterate over a.
    M[vertex] = total;

    for(int c = 0; c < adj[vertex].size(); ++c) {
        if(adj[vertex][c] == parent) continue;
        int a = adj[vertex][c];
        total = 1 + Mprime - M[a];
        for(int w = 0; w < adj[a].size(); ++w){
            if(adj[a][w] == vertex) continue;
            total += matching(adj[a][w], a, adj, M);
        }
        M[vertex] = max(total, M[vertex]);  
    }

    return M[vertex];
}

void testcase() {
    int N; cin >> N;
    vii adj(N);
    vi M(N, -1);

    for(int n = 0; n < N-1; ++n) {
        int v1, v2; cin >> v1 >> v2;
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }

    int match = matching(0, 0, adj, M);
    cout << match << "\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
