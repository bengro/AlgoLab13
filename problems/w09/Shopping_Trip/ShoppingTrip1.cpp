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
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor Edge;

void testcase() {
    int n, m, s; cin >> n >> m >> s;
    Graph g(n);
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap rev_edge = get(edge_reverse, g);
    ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);
    
    for(int store = 0; store < s; ++store){
        int store_vertex; cin >> store_vertex;
        Edge edge;
        tie(edge, tuples::ignore) = add_edge(store_vertex, n, g);
        Edge reverse_edge;
        tie(reverse_edge, tuples::ignore) = add_edge(n, store_vertex, g);
        capacity[edge] = 1;
        rev_edge[edge] = reverse_edge;
        capacity[reverse_edge] = 0;
        rev_edge[reverse_edge] = edge;
    }

    for(int e = 0; e < m; ++e) {
        int v1, v2; cin >> v1 >> v2;
        Edge edge; 
        tie(edge, tuples::ignore) = add_edge(v1, v2, g);
        Edge reverse_edge;
        tie(reverse_edge, tuples::ignore) = add_edge(v2, v1, g);
        capacity[edge] = 1;
        rev_edge[edge] = reverse_edge;
        capacity[reverse_edge] = 0;
        rev_edge[reverse_edge] = edge;
        Edge edge2;
        tie(edge2, tuples::ignore) = add_edge(v2, v1, g);
        Edge reverse_edge2;
        tie(reverse_edge2, tuples::ignore) = add_edge(v1, v2, g);
        capacity[edge2] = 1;
        rev_edge[edge2] = reverse_edge2;
        capacity[reverse_edge2] = 0;
        rev_edge[reverse_edge2] = edge2;
    }
    
    long max_flow = push_relabel_max_flow(g, 0, n);
    if(max_flow == s) cout << "yes\n"; else cout << "no\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
