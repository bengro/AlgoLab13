#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
  property<edge_capacity_t, long,
  property<edge_residual_capacity_t, long,
  property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor Edge;

void add_edge(int f, int t, int cap, Graph& g) {
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap rev_edge = get(edge_reverse, g);
    
    Edge edge;
    tie(edge, tuples::ignore) = add_edge(f, t, g);
    Edge reverse_edge;
    tie(reverse_edge, tuples::ignore) = add_edge(t, f, g);
    capacity[edge] = cap;
    rev_edge[edge] = reverse_edge;
    capacity[reverse_edge] = 0;
    rev_edge[reverse_edge] = edge;
}

void testcase() {
    int V, E; cin >> V >> E;
    Graph g(V+2);
    int source = V;
    int sink = V+1;

    vector<int> vertices;
    for(int v = 0; v < V; ++v) {
        int g, d; cin >> g >> d;
        vertices.push_back(d - g);
    }

    for(int e = 0; e < E; ++e) {
        int f, t, lb, ub; cin >> f >> t >> lb >> ub;
        add_edge(f, t, ub-lb, g);
        vertices[f] += lb;
        vertices[t] -= lb; 
    }
    
    int flow_out = 0;
    bool all_pos = true;
    for(int v = 0; v < V; ++v) {
        if(vertices[v] < 0) {
            add_edge(source, v, abs(vertices[v]), g);
        } else if(vertices[v] > 0) {
            all_pos = false;
            add_edge(v, sink, vertices[v], g);
            flow_out += abs(vertices[v]);
        }
    }
    
    int max_flow = push_relabel_max_flow(g, source, sink);
    (max_flow == flow_out || all_pos) ? cout << "yes\n" : cout << "no\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
}
