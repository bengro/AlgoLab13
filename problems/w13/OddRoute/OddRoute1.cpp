#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/tuple/tuple.hpp>
#include <climits>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;
typedef property_map<Graph, edge_weight_t>::type EdgeWeightMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

void add_edges(Graph& g, int u, int v, int w) {
    int uee = u*4;      int vee = v*4;
    int ueo = uee+1;     int veo = vee+1;
    int uoe = uee+2;     int voe = vee+2;
    int uoo = uee+3;     int voo = vee+3;
    
    EdgeWeightMap weights = get(edge_weight, g);

    Edge edge;
    if(w % 2 == 0) {
        tie(edge, tuples::ignore) = add_edge(uee, voe, g); weights[edge] = w;
        tie(edge, tuples::ignore) = add_edge(ueo, voo, g); weights[edge] = w;
        tie(edge, tuples::ignore) = add_edge(uoe, vee, g); weights[edge] = w;
        tie(edge, tuples::ignore) = add_edge(uoo, veo, g); weights[edge] = w;
    } else {
        tie(edge, tuples::ignore) = add_edge(uee, voo, g); weights[edge] = w;
        tie(edge, tuples::ignore) = add_edge(ueo, voe, g); weights[edge] = w;
        tie(edge, tuples::ignore) = add_edge(uoe, veo, g); weights[edge] = w;
        tie(edge, tuples::ignore) = add_edge(uoo, vee, g); weights[edge] = w;
    }
}

void testcase() {
    int N, M, s, t; cin >> N >> M >> s >> t;
    Graph g(N*4);

    for(int m = 0; m < M; ++m) {
        int u, v, w; cin >> u >> v >> w;
        add_edges(g, u, v, w);
    }
    
    vector<int> d(num_vertices(g), -1);
    dijkstra_shortest_paths(g, s*4, distance_map(&d[0]));
    (d[4*t+3] < INT_MAX) ? cout << d[4*t+3] : cout << "no";
    cout << "\n"; 
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
