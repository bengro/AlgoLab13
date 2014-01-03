#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
int N; 

pair<int, int> DFS(int start, vii& adj, vi& dist, vi& visited) {
    queue<int> fifo;
    fifo.push(start);
    visited[start] = 1;

    while(!fifo.empty()) {
        int parent_id = fifo.front(); fifo.pop();
        for(int child = 0; child < adj[parent_id].size(); ++child) {
            int child_id = adj[parent_id][child];
            if(visited[child_id] == 0) {
                fifo.push(child_id);
                visited[child_id] = 1;
                dist[child_id] = dist[parent_id] + 1;
            }
        }
    }
    vi::iterator it = max_element(dist.begin(), dist.end());
    pair<int, int> val;
    val.first = it - dist.begin();
    val.second = *it;
    return val;
}

void testcase() {
    cin >> N;    // N vertices, by definition N-1 edges.
    vii adj(N);
    vi dist(N, 0);
    vi visited(N, 0);

    for(int n = 0; n < N-1; ++n) {
        int v1, v2; cin >> v1 >> v2;
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }
    if(N == 1) { cout << 0 << "\n"; return; }

    pair<int, int> pass1 = DFS(0, adj, dist, visited);
    dist.assign(N, 0); visited.assign(N, 0);
    pair<int, int> pass2 = DFS(pass1.first, adj, dist, visited);
    cout << pass2.second+1 << "\n";
}

int main() {
    cin.sync_with_stdio(false);
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
