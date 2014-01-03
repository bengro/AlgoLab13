#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;

void testcase() {
    int N, M; cin >> N >> M;
    Graph g(N+1);
    vector<int> processed(N, 0);
    for(int m = 0; m < M; ++m) {
        int a, b; cin >> a >> b;
        add_edge(a, b, g);
        if(!processed[a]) { add_edge(a, N+1, g); processed[a] = 1; }
        if(!processed[b]) { add_edge(b, N+1, g); processed[b] = 1; }
    }

    if(boyer_myrvold_planarity_test(g)) 
        cout << "yes\n";
    else
        cout << "no\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
