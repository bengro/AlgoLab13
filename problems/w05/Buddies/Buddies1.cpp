#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
using namespace std;
using namespace boost;

typedef vector<int> vi;
typedef pair<int, int> ii;

typedef property<vertex_index_t, int> VertexProperties;
typedef property<edge_weight_t, int> EdgeProperties; 
typedef adjacency_list<vecS, vecS, undirectedS, VertexProperties, EdgeProperties> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, vertex_index_t>::type VIndexMap; 
typedef graph_traits<Graph>::edge_iterator EdgeIterator;

void testcase() {
	int n, c, f; cin >> n >> c >> f;
	map<string, vi> char_map;

	for(int student = 0; student < n; ++student) {
		for(int characteric = 0; characteric < c; ++characteric) {
			string input; cin >> input;
			if(char_map.count(input) == 0) { 
				vi students; students.push_back(student);
				char_map.insert(make_pair(input, students));  
			}
			else { char_map[input].push_back(student); }
		}
	}

	map<ii, int> edges;
	for(map<string, vi>::iterator iter = char_map.begin(); iter != char_map.end(); ++iter) {
		pair<string, vi> value_pair = *iter;
		vi& values = value_pair.second;
		for(int s1 = 0; s1 < values.size()-1; ++s1) {
			for(int s2 = s1+1; s2 < values.size(); ++s2) {
				ii edge = make_pair(values[s1], values[s2]);
				if(edges.count(edge) == 0) { edges.insert(make_pair(edge, 1)); }
				else { edges[edge]++; }
			}
		}
	}

	Graph g(n);
	for(map<ii, int>::iterator iter = edges.begin(); iter != edges.end(); ++iter) {
		pair<ii, int> edge_pair = *iter;
		//cout << "edge: " << edge_pair.first.first << "-" << edge_pair.first.second << " weight: " << edge_pair.second << "\n";
		if(edge_pair.second > f) {
			add_edge(edge_pair.first.first, edge_pair.first.second, g);
		}
	}

	vector<Vertex> mateMap (num_vertices(g));
	bool matching_success = checked_edmonds_maximum_cardinality_matching(g, &mateMap[0]);

	if(matching_success) {
		if(matching_size(g, &mateMap[0]) < n/2 )  cout << "optimal\n";
		else cout << "not optimal\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}