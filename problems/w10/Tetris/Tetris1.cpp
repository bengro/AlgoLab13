#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
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

void add_edge(int from, int to, int cap, Graph& g) {
    //cout << "adding edge: " << from << " " << to << " " << cap << "\n";
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap reverse = get(edge_reverse, g);
    
    Edge there, back;
    tie(there, tuples::ignore) = add_edge(from, to, g);
    tie(back, tuples::ignore) = add_edge(to, from, g);
    capacity[there] = cap;
    capacity[back] = 0;
    reverse[there] = back;
    reverse[back] = there;
}

void testcase() {
    int W, N; cin >> W >> N;
    
    int source = 0;
    int sink = W;
    Graph g(2*W);
    
    for(int v = 1; v < W; ++v) {
        add_edge(v, W+v, 1, g);
    }

    for(int n = 0; n < N; ++n) {
        int v1, v2; cin >> v1 >> v2;
        int from = (min(v1, v2) == 0) ? 0 : min(v1, v2) + W;
        int to = max(v1, v2);
        add_edge(from, to, 1, g);
    }

    int maxflow = push_relabel_max_flow(g, source, sink);
    cout << maxflow << "\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
}
