#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

void testcase() {
    int N, C, F; cin >> N >> C >> F;
    int counter = 0;
    map<string, int> stringMap;
    vector<set<int> > chars(N);
    for(int i = 0; i < N; ++i) {
        for(int c = 0; c < C; ++c) {
            string input; cin >> input;
            if(stringMap.count(input) == 0) stringMap[input] = counter++;
            chars[i].insert(stringMap[input]);
        }
    }

    Graph g(N);
    for(int i = 0; i < N; ++i) {
        for(int j = i+1; j < N; ++j) {
            int matchings = 0;   
            for(set<int>::iterator it = chars[i].begin(); it != chars[i].end(); ++it) {
                if(chars[j].count(*it) == 1) {
                    ++matchings;
                    if(matchings > F) {
                        add_edge(i, j, g);
                        break;  // could be the culprit.
                    }
                } 
            }
        }
    }

    vector<Vertex> mateMap(N, 0);
	checked_edmonds_maximum_cardinality_matching(g, &mateMap[0]);
    int matched = matching_size(g, &mateMap[0]);
    if(matched*2 == N) cout << "not optimal\n";
    else cout << "optimal\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
