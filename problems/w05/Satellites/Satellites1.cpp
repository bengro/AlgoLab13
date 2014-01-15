#include <iostream>
#include <vector>
#include <stack>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::out_edge_iterator OEI;

void testcase() {
    int G, S, L; cin >> G >> S >> L;
    
    Graph g(G+S);
    for(int l = 0; l < L; ++l) {
        int u, v; cin >> u >> v;
        add_edge(u, G+v, g);
    }
    
    vector<Vertex> mateMap(G+S, 0);
	checked_edmonds_maximum_cardinality_matching(g, &mateMap[0]);
    matching_size(g, &mateMap[0]);
    
    stack<int> fifo;
    vector<int> visited(G+S, 0);
    for(int v = 0; v < G; ++v) {
        if(mateMap[v] == graph_traits<Graph>::null_vertex()) {
            visited[v] = 1;
            fifo.push(v);
        }
    }
    
    while(!fifo.empty()) {
        int u = fifo.top(); fifo.pop();
        OEI ebegin, eend;
        for(tie(ebegin, eend) = out_edges(u, g); ebegin != eend; ++ebegin) {
            int v = boost::target(*ebegin, g);
            if(visited[v] == 1) continue;
            if(u < G) {
                if(mateMap[u] != v) {
                    visited[v] = 1;
                    fifo.push(v);
                }
            } else {
                if(mateMap[u] == v) {
                    visited[v] = 1;
                    fifo.push(v);
                }
            }
        }
    }
    
    vector<int> sat;
    vector<int> ground;
    for(int v = 0; v < G; ++v)
        if(visited[v] == 0) ground.push_back(v);
    for(int v = G; v < G+S; ++v) 
        if(visited[v] == 1) sat.push_back(v);

    cout << ground.size() << " " << sat.size() << "\n";
    for(int i = 0; i < ground.size(); ++i) cout << ground[i] << " ";
    for(int i = 0; i < sat.size(); ++i) cout << sat[i]-G << " ";
    cout << "\n";
}

int main() {
    int TC; cin >> TC;
    while (TC--) testcase();
    return 0;
}
