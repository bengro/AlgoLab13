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
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor Edge;

void add_edge(int from, int to, int c, Graph& g) {
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap reverse = get(edge_reverse, g);
    ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);
    
    Edge there, back;
    tie(there, tuples::ignore) = add_edge(from, to, g);
    tie(back, tuples::ignore) = add_edge(to, from, g);
    capacity[there] = c;
    capacity[back] = 0;
    reverse[there] = back;
    reverse[back] = there;
}

void testcase() {
    int N, M; cin >> N >> M;
    Graph g(N+M+2);
    int source = N+M+1;
    int sink = source + 1;

    for(int m = N; m < N+M; ++m) {
        int p1, p2, outcome;
        cin >> p1 >> p2 >> outcome;
        add_edge(source, m, 1, g);

        if(outcome == 1) {
            add_edge(m, p1, 1, g);
        }
        if(outcome == 2) {
            add_edge(m, p2, 1, g);
        }
        if(outcome == 0) {
            add_edge(m, p1, 1, g);
            add_edge(m, p2, 1, g);
        }
    }
    
    int sum = 0;
    for(int p = 0; p < N; ++p) {
        int score;  cin >> score;
        sum += score;
        add_edge(p, sink, score, g);
    }

    int f_max = push_relabel_max_flow(g, source, sink);
    if(M == sum && f_max == sum) cout << "yes\n";
    else cout << "no\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
}
