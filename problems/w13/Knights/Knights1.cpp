#include <iostream>
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

int M; 
int N;
int K;

int index(int x, int y) { 
    return y*M + x;
}

void add_edges(int from, int to, Graph& g) {
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap reverse = get(edge_reverse, g);

    Edge there, back;
    tie(there, tuples::ignore) = add_edge(from, to, g);
    tie(back, tuples::ignore) = add_edge(to, from, g);
    capacity[there] = 1;
    capacity[back] = 0;
    reverse[there] = back;
    reverse[back] = there;
}

void testcase() {
    cin >> M >> N >> K;    // M: cols, N: rows, K: #knights

    int graph_size = 2*(M*N)+2;     // M*N for each coordinate, 2*(M*N) because we need vertex-disjoint paths only.
    Graph g(graph_size);
    int source = graph_size-2;
    int sink = graph_size-1;
    for(int y = 0; y < N; ++y) {
        for(int x = 0; x < M; ++x) {
            int v_in = index(x, y);
            int v_out = index(x, y) + M*N;
            
            add_edges(v_in, v_out, g);

            if(x+1 < M) {
                add_edges(v_out, index(x+1, y), g);
                add_edges(index(x+1, y)+(M*N), v_in, g);
            }
            if(y+1 < N) {
                add_edges(v_out, index(x, y+1), g);
                add_edges(index(x, y+1)+(M*N), v_in, g);
            }
            if(x-1 < 0 || x+1 >= M || y-1 < 0 || y+1 >= N) {
                add_edges(v_out, sink, g);
            }
        }
    }

    for(int k = 0; k < K; ++k) {
        int x, y; cin >> x >> y;
        add_edges(source, index(x, y), g);
    }
    
    int maxflow = push_relabel_max_flow(g, source, sink);
    cout << maxflow << "\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
}
