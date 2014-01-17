#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

int N;
vii adj;
vii dp_table;

int MVC(int vertex, int parent, bool taken) {
    if(dp_table[vertex][taken] != -1) return dp_table[vertex][taken];

    int ans = 0;
    if(adj[vertex].size() == 1 && vertex != 0) {
        ans = taken;
    }
    else if(taken == 1) {
        ans = 1;
        for(int i = 0; i < (int)adj[vertex].size(); ++i) {
            int child = adj[vertex][i];
            if(child == parent) continue;
            ans += min(MVC(child, vertex, false), MVC(child, vertex, true));
        }
    }
    else if(taken == 0) {
        ans = 0;
        for(int i = 0; i < (int) adj[vertex].size(); ++i) {
            int child = adj[vertex][i];
            if(child == parent) continue;
            ans += MVC(child, vertex, true); 
        }
    }
    
    dp_table[vertex][taken] = ans;
    return ans;
}

void testcase() {
    cin >> N;
    adj.clear(); adj.assign(N, vi(0));
    dp_table.clear(); dp_table.assign(N, vi(2 , -1));

    for(int n = 0; n < N-1; ++n) {
        int v1, v2; cin >> v1 >> v2;
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }

    cout << min(MVC(0, 0, true), MVC(0, 0, false)) << "\n";
    
    // print vertex cover. V - MVC = MIS, because tree = bipartite graph (Königstheorem).
    for(int i = 0; i < N; ++i) {
        if(dp_table[i][1] <= dp_table[i][0]) cout << i << " ";
    }
    cout << "\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
