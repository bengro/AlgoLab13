#include <vector>
#include <iostream>
#include <climits>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
using namespace std;
using namespace boost;

typedef vector<int> vi;
typedef adjacency_list<vecS, vecS, directedS, no_property, no_property> Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator EdgeIterator;

void testcase() {
    int N, M; cin >> N >> M;
    
    Graph g(N);
    for(int e = 0; e < M; ++e) {
        int v1, v2;
        cin >> v1 >> v2;
        add_edge(v1-1, v2-1, g);
    }

    vi costs(N);
    for(int n = 0; n < N; ++n) {
        int cost; cin >> cost;
        costs[n] = cost;
    }

    vector<int> scc(N);
    int nscc = strong_components(g, &scc[0]);
    
    vi incoming_comp(nscc, 0);
    EdgeIterator ebeg, eend;
    for(tie(ebeg, eend) = edges(g); ebeg != eend; ++ebeg) {
        int u = source(*ebeg, g);
        int v = target(*ebeg, g);
        if(scc[u] != scc[v]) incoming_comp[scc[v]] = 1;
    }
    
    int total = 0;
    for(int comp = 0; comp < nscc; ++comp) {
        if(incoming_comp[comp] == 1) continue;
        int min_cost = INT_MAX;
        for(int v = 0; v < N; ++v) {
            if(scc[v] == comp) min_cost = min(min_cost, costs[v]);
        }
        total += min_cost;
    }

    cout << total << "\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
