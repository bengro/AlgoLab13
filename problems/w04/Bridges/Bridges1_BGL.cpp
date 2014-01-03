#include <vector>
#include <iostream>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>
using namespace std;
using namespace boost;

typedef property<vertex_index_t, int> VertexProperties;
typedef adjacency_list< vecS, vecS, undirectedS, VertexProperties, no_property> Graph;
typedef property_map<Graph, vertex_index_t>::type VIndexMap; 
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::adjacency_iterator AIter;
typedef vector<int> vi;
typedef vector<Vertex> vv;
typedef pair<int, int> pi;

void testcase() {
	int N, M; cin >> N >> M;
	
	if(N == 0 || M == 0) { cout << "0\n"; return; }

	Graph g(N);
	VIndexMap index = get(vertex_index, g);

	for(int m = 0; m < M; ++m) {
		int v1, v2; cin >> v1 >> v2;
		add_edge(v1, v2, g);
	}

	vv art_points;
	vi discover_time(num_vertices(g));
	vi low_point(num_vertices(g));
	vector<pi> bridges;
	articulation_points(g, 
						back_inserter(art_points), 
						discover_time_map(&discover_time[0]).lowpoint_map(&low_point[0]));

	// workaround for "root not chosen as articulation point if only one child".
	if(out_degree(vertex(1, g), g) == 1) {
		Vertex root = vertex(1, g);
		art_points.insert(art_points.begin(), root);
	}
	for(int v = 0; v < art_points.size(); ++v) {
		Vertex art_point = art_points[v];
		AIter neighbour, neighbour_end;
		for(tie(neighbour, neighbour_end) = adjacent_vertices(art_point, g); neighbour != neighbour_end; ++neighbour) {
			if(low_point[*neighbour] > discover_time[art_point]) {
				//cout << "bridge found between: " << index[art_point] << "-" << index[*neighbour] << "\n";
				bridges.push_back(make_pair(min(index[art_point], index[*neighbour]), max(index[art_point], index[*neighbour])));
			}
		}
	}

	sort(bridges.begin(), bridges.end());
	cout << bridges.size() << "\n";
	for(int b = 0; b < bridges.size(); ++b) {
		cout << bridges[b].first << " " << bridges[b].second << "\n";
	}
}

int main() {
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}