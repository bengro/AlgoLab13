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

void testcase() {
    int W, H; cin >> W >> H;
    
    vii matrix(H);
    int blocked = 0;
    int vcounter = 0;
    for(int h = 0; h < H; ++h) {
        for(int w = 0; w < W; ++w) {
            char input; cin >> input;
            blocked += (input == 'x');
            matrix[h].push_back((input == '.') ? vcounter++ : -1);
        }
    }
    
    int V = (W*H - blocked);
    if(V % 2 == 1) {
        cout << "no\n";
        return;
    }

    Graph g(V);
    for(int h = 0; h < H; ++h) {
        for(int w = 0; w < W; ++w) {
            if(matrix[h][w] == -1) continue;
            if(w+1 < W && matrix[h][w+1] != -1) add_edge(matrix[h][w], matrix[h][w+1], g);
            if(h+1 < H && matrix[h+1][w] != -1) add_edge(matrix[h][w], matrix[h+1][w], g);
        }
    }
    
    vector<Vertex> mateMap(num_vertices(g), 0);
	checked_edmonds_maximum_cardinality_matching(g, &mateMap[0]);
    int matching = matching_size(g, &mateMap[0]); 

    if(matching * 2 == V) cout << "yes\n";
    else cout << "no\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
