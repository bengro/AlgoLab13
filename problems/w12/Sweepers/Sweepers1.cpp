#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/strong_components.hpp>
using namespace std;
using namespace boost;

typedef vector<int> vi;
typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
  property<edge_capacity_t, long,
  property<edge_residual_capacity_t, long,
  property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

int N, M, S;

void add_edge(int from, int to, int cap, Graph& g) {
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
    cin >> N >> M >> S;
    int source = N;
    int sink = N+1;
    Graph g(N+2);
    vi starts(N, 0), exits(N, 0);

    for(int s = 0; s < S; ++s) {
        int room; cin >> room;
        ++starts[room];
    }

    for(int s = 0; s < S; ++s) {
        int room; cin >> room;
        ++exits[room];
    }
    
    for(int m = 0; m < M; ++m) {
        int v1, v2; cin >> v1 >> v2;
        add_edge(v1, v2, 1, g);
        add_edge(v2, v1, 1, g);
    }
    
    for(int n = 0; n < N; ++n) {
        if(starts[n] > 0) add_edge(source, n, starts[n], g);
        if(exits[n] > 0) add_edge(n, sink, exits[n], g);
    }
    
    bool isEulerian = true;
    bool isConnected = false;
    graph_traits<Graph>::vertex_iterator viter, vend;
    for (tie(viter, vend) = vertices(g); viter != vend; ++viter) {
        if(*viter == source || *viter == sink) continue;
        int count = out_degree(*viter, g);
        if(starts[*viter] > 0) ++count;
        if(exits[*viter] > 0) ++count;
        count = count/2;
        if(count % 2 == 1) {
            isEulerian = false;
            break;
        }
    }
    
    if(!isEulerian) { 
        cout << "no\n";
        return;
    }

    int maxflow = push_relabel_max_flow(g, source, sink);
    if(maxflow != S) 
        cout << "no\n"; 
    else 
        cout << "yes\n";
}

int main() {
    int TC; cin >> TC; 
    while(TC--) testcase();
}
