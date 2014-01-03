#include <iostream>
#include <stack>
#include <set>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
using namespace std;
using namespace boost;

typedef vector<pair<int, int> > vpi;
typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::vertex_iterator VI;
typedef graph_traits<Graph>::out_edge_iterator EI;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

void printEulerGraph(int v, Graph& g) {
    WeightMap weight = get(edge_weight, g);
    stack<int> fifo;
    fifo.push(v);
    vector<int> sol;
    while(!fifo.empty()) {
        int v = fifo.top(); 
        EI ebegin, eend;
        bool hasFreeEdge = false;
        for(tie(ebegin, eend) = out_edges(v, g); ebegin != eend; ++ebegin) {
            if(weight[*ebegin] == 0) {
                hasFreeEdge = true;
                weight[*ebegin] = 1;
                fifo.push(boost::target(*ebegin, g));
                break;
            }
        }
        if(!hasFreeEdge) {
            sol.push_back(v);
            fifo.pop();
        }
    }
    for(int s = 0; s < sol.size()-1; ++s) {
        cout << sol[s] << " " << sol[s+1] << "\n";
    }
    cout << "\n";
}

void testcase(int TC) {
    cout << "Case #" << ++TC << "\n";
    int N; cin >> N;
    
    Graph g(50);
    WeightMap weight = get(edge_weight, g);
    set<int> colors;

    for(int n = 0; n < N; ++n) {
        int v1, v2; cin >> v1 >> v2;
        colors.insert(v1); colors.insert(v2);
        Edge e;
        tie(e, tuples::ignore) = add_edge(v1, v2, g);
        weight[e] = 0;
    }
    
    vector<int> component(num_vertices(g));
    int num = connected_components(g, &component[0]) - (51 - colors.size());
    int start = -1;
    VI vbegin, vend;
    for(tie(vbegin, vend) = vertices(g); vbegin != vend; ++vbegin) {
        int deg = out_degree(*vbegin, g);
        if(deg % 2 == 1 || num > 1) {
            cout << "some beads may be lost\n\n";
            return;
        }
        if(deg > 0) start = *vbegin; 
    }
    
    printEulerGraph(start, g); 
}

int main() {
    int TC; cin >> TC;
    for(int t = 0; t < TC; ++t) testcase(t);
}
