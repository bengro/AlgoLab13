#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
using namespace std;
using namespace boost;

typedef vector<int> vi;
typedef vector<vi> vii;
typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

int N; 

int co_to_index(int i, int j) {
    return i*N + j;
}

void add_valid_edges(int i, int j, vii& holes, Graph& g) {
    int y = 1;
    for(int x = -2; x <= 2; x = x + 4) {
        if(i+y >= 0 && i+y < N && j+x >= 0 && j+x <= N && holes[i+y][j+x] == 1) {
            add_edge(co_to_index(i, j), co_to_index(i+y, j+x), g);        
        }
    }
    y = 2;
    for(int x = -1; x <= 1; x = x + 2) {
        if(i+y >= 0 && i+y < N && j+x >= 0 && j+x <= N && holes[i+y][j+x] == 1) {
            add_edge(co_to_index(i, j), co_to_index(i+y, j+x), g);        
        }
    }
}

void testcase() {
    cin >> N;
    Graph g(N*N); 
    vii holes(N, vi(N));
    int sum_holes = 0;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            int hole; cin >> hole;
            holes[i][j] = hole;
            if(holes[i][j] == 0) ++sum_holes;
        }
    }

    for(int i = 0; i < N-1; ++i) {
        for(int j = 0; j < N; ++j) {
            if(holes[i][j] == 1) add_valid_edges(i, j, holes, g);
        }
    }

    vector<Vertex> mateMap(num_vertices(g), 0);
	checked_edmonds_maximum_cardinality_matching(g, &mateMap[0]);
    // mistake: forgot to substract the holes. 
    cout << num_vertices(g)- sum_holes - matching_size(g, &mateMap[0]) << "\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
