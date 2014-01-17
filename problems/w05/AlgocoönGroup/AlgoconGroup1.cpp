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
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
Graph g;
EdgeCapacityMap capacity = get(edge_capacity , g);
ReverseEdgeMap reverseMap = get(edge_reverse, g);
ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);

void add_edge(int from, int to, int cap, Graph& g) {    
    Edge there, back;
    tie(there, tuples::ignore) = add_edge(from, to, g);
    tie(back, tuples::ignore) = add_edge(to, from, g);
    capacity[there] = cap;
    capacity[back] = 0;
    reverseMap[there] = back;
    reverseMap[back] = there;
}

void testcase() {
    int N, M; cin >> N >> M;
    g = Graph(N);

    for(int m = 0; m < M; ++m) {
        int v1, v2, cost; cin >> v1 >> v2 >> cost;
        add_edge(v1, v2, cost, g);
    }
    
    int max_flow = INT_MAX;
    int source = -1;
    int sink = -1;
    
    for(int n = 1; n < N; ++n) {
        int f1 = push_relabel_max_flow(g, 0, n);
        if(f1 < max_flow) {
            source = 0;
            sink = n;
            max_flow = f1;
        }
        int f2 = push_relabel_max_flow(g, n, 0);
        if(f2 < max_flow) {
            source = n;
            sink = 0;
            max_flow = f2;
        }
    }

    int f = push_relabel_max_flow(g, source, sink);
    vector<int> result;
    vector<int> visited (N, 0);
    visited[source] = 1;
    queue<int> Q;
    Q.push(source);
    while(!Q.empty()) {
        int v = Q.front(); Q.pop();
        result.push_back(v);
        OutEdgeIterator ebegin, eend;
        for(tie(ebegin, eend) = out_edges(v, g); ebegin != eend; ++ebegin) {
            if(res_capacity[*ebegin] != 0 && visited[target(*ebegin, g)] == 0) {
                Q.push(target(*ebegin, g));
                visited[target(*ebegin, g)] = 1;
            }
        }
    }

    cout << f << "\n";
    cout << result.size() << " ";
    for(int r = 0; r < result.size(); ++r) 
        cout << result[r] << " ";
    cout << "\n";
}

int main() {
    int TC; cin >> TC;
    while (TC--) testcase();
}
