#include <iostream>
#include <vector>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
using namespace std;
using namespace boost;

const int MAX_LENGTH = 100000000;   // do not pick INT_MAX otherwise overflow resulting in -INT_MAX confusing min.

typedef vector<int> vi;
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;

int BFS(int start, int end, Graph& g) {
    if(start == end) return 0;
    vi distances(num_vertices(g), -1);
    std::queue<int> fifo;
    fifo.push(start);
    distances[start] = 0;
    while(!fifo.empty()) {
        int v = fifo.front(); fifo.pop();
        OutEdgeIterator ebegin, eend;
        for(tie(ebegin, eend) = out_edges(v, g); ebegin != eend; ++ebegin) {
            int u = target(*ebegin, g);
            if(distances[u] == -1) {
                distances[u] = distances[v] + 1;
                fifo.push(u);
                if(u == end) return distances[u];
            }
        }
    }
    return MAX_LENGTH;
}

void testcase() {
    int N, M, s, t; cin >> N >> M >> s >> t;
    --t; --s;

    Graph g(N);
    WeightMap weights = get(edge_weight, g);

    for(int m = 0; m < M; ++m) {
        int v1, v2; cin >> v1 >> v2;
        Edge edge;
        tie(edge, tuples::ignore) = add_edge(v1-1, v2-1, g);
        weights[edge] = 1;
    }
    
    vi d(N);
    vector<Vertex> p(N);
    dijkstra_shortest_paths(g, s, predecessor_map(&p[0]).distance_map(&d[0]));
    
    if(d[t] == INT_MAX) { cout << "no\n"; return; }     // there is no path from s to t.
    
    int sp = MAX_LENGTH;
    int b = t;
    int prev = t;
    while(true) {
        OutEdgeIterator ebegin, eend;
        for(tie(ebegin, eend) = out_edges(b, g); ebegin != eend; ++ebegin) {
            if(target(*ebegin, g) == prev && prev != s && b != t) continue; // do not pick the edge in P, start end end path are special states.
            sp = min(sp, d[source(*ebegin, g)] + 1 + BFS(target(*ebegin, g), t, g));
        }
        if(b == s || sp == d[t]) break;
        prev = b;
        b = p[b];
    }
    (sp == MAX_LENGTH) ? cout << "no\n" : cout << sp << "\n";    
}

int main() {
    ios_base::sync_with_stdio(false);
    int TC; cin >> TC;
    while(TC--) testcase();
}
