#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

vii adj;
vii dp_table;
vi values;

int MWIS(int v, bool taken) {
    int ans;
    if(adj[v].size() == 1 && v != 0) {
        if(taken) return values[v];
        else return 0;
    } 
    else if(taken) {
        ans = values[v];
        for(int i = 0; i < (int) adj[v].size(); ++i) {
            if(adj[v][i] == vertex) continue;
            ans += values[adj[v][i]][false];
        }
    }
    else if(!taken) {
        for(int i = 0; i < (int) adj[v].size(); ++i) {
            if(adj[v][i] == vertex) continue;
            ans += max(values[adj[v][i]][true], values[adj[v][i]][false]);
        }
    }

    dp_table[v][taken] = ans;
    return ans;
}

void testcase() {
    int N; cin >> N;
    adj.clear(); adj.assign(N, vi(0);
    dp_table.clear(); dp_table.assign(N, vi(2, -1));
    values.clear(); values.assign(N, 0);

    for(int n = 0; n < N-1; ++n) {
        int v1, v2; cin >> v1 >> v2; 
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);ssssss
    }

    for(int n = 0; n < N; ++n) {
        int val; cin >> val;
        values[n] = val;
    }

    cout << max(MWIS(0, true), MWIS(0, false)) << "\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
