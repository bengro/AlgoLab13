#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

int k;

void testcase() {
    int n, m, k;
    cin >> n >> m >> k;
    
    vii adj(n);
    vii groups(k);
    vi col(n, -1);

    for(int e = 0; e < m; ++e) {
        int v1, v2; cin >> v1 >> v2;
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }
    
    queue<int> q; // lifo
    int c = 0;
    q.push(0);
    col[0] = c;
    groups[c].push_back(0);

    while(!q.empty()) {
        const int v = q.front(); q.pop();
        for(int child = 0; child < adj[v].size(); ++child) {
            const int u = adj[v][child];
            if(col[u] != -1) continue;
            
            c = (c == k-1) ? 0 : ++c;
            if(col[v] == c) { c = (c == k-1) ? 0 : ++c; }
            col[u] = c;
            groups[c].push_back(u);
            q.push(u);
        }
    }

    if(n >= k && find(col.begin(), col.end(), -1) == col.end()) {
        cout << "yes\n";
        for(int g = 0; g < k; ++g) {
            cout << groups[g].size();
            for(int i = 0; i < groups[g].size(); ++i) {
                cout << " " << groups[g][i];
            }
            cout << "\n";
        }
    } else {
        cout << "no\n";
    }
    col.clear();
    adj.clear();
    groups.clear();
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
}
