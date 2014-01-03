#include <vector>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
using namespace std;
using namespace boost;

typedef property<edge_weight_t, int, property<edge_index_t, int> > EdgeProperties;
typedef property<vertex_index_t, int> VertexProperties;
typedef adjacency_list<vecS, vecS, undirectedS, VertexProperties, EdgeProperties> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef property_map<Graph, edge_index_t>::type EIndexMap;
typedef property_map<Graph, vertex_index_t>::type VIndexMap;
typedef graph_traits<Graph>::edge_iterator EdgeIterator;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<Edge> ve;

void testcase() {
	int N, M, S, a, b; cin >> N >> M >> S >> a >> b;
	
	Graph g;
	WeightMap weightMap = get(edge_weight, g);
	EIndexMap eIndexMap = get(edge_index, g);
	vii weights(M);

	for(int e = 0; e < M; ++e) {
		int t1, t2; cin >> t1 >> t2;
		for(int s = 0; s < S; ++s) {
			int s_weight; cin >> s_weight;
			weights[e].push_back(s_weight);
		}

		Edge edge; bool success;
		tie(edge, success) = add_edge(t1, t2, g);
		eIndexMap[edge] = e;
	}

	Graph final;
	WeightMap weightMapFinal = get(edge_weight, final);

	for(int s = 0; s < S; ++s) {
		int hive; cin >> hive;

		EdgeIterator eit, eend;
		for(tie(eit, eend) = edges(g); eit != eend; ++eit) weightMap[*eit] = weights[eIndexMap[*eit]][s]; 

		ve mst(num_vertices(g)-1);
		kruskal_minimum_spanning_tree(g, mst.begin());
		for(ve::iterator edge = mst.begin(); edge != mst.end(); ++edge) {
			Edge newEdge; bool success;
			tie(newEdge, success) = add_edge(source(*edge, g), target(*edge, g), final);
			weightMapFinal[newEdge] = weightMap[*edge];
		}
	}

	vi d(num_vertices(final));
	dijkstra_shortest_paths(final, vertex(a, final), distance_map(&d[0]));
	cout << d[b] << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}