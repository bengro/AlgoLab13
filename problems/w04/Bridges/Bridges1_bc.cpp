#include <iostream>
#include <vector>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property <edge_index_t, int> > Graph;
typedef property_map<Graph, edge_index_t>::type EdgeComponent;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator EI;

void testcase() {
    int N, M; cin >> N >> M;
    Graph g(N);
    EdgeComponent edgeMap = get(edge_index, g);
    
    for(int m = 0; m < M; ++m) {
        int u, v; cin >> u >> v;
        add_edge(u, v, g);
    }
    int c = biconnected_components(g, edgeMap);

    EI ebegin, eend;
    vector<vector<pair<int, int> > > components(c);
    for(tie(ebegin, eend) = edges(g); ebegin != eend; ++ebegin) {
        int comp = edgeMap[*ebegin];
        int u = boost::source(*ebegin, g);
        int v = boost::target(*ebegin, g);
        components[comp].push_back(make_pair(min(u, v), max(u, v)));
    }
    
    vector<pair<int, int> > bridges;
    for(int comp = 0; comp < c; ++comp) {
        if(components[comp].size() == 1) {
            bridges.push_back(components[comp][0]);
        }
    }
    sort(bridges.begin(), bridges.end());

    cout << bridges.size() << "\n";
    for(int b = 0; b < bridges.size(); ++b) {
        cout << bridges[b].first << " " << bridges[b].second << "\n";
    }
}

int main() {
    int TC; cin >> TC;
    while (TC--) testcase();
    return 0;
}
