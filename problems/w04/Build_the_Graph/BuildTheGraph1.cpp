#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
using namespace std;
using namespace boost;

// create internal properties
typedef property<vertex_index_t, int> IndexProperty;
typedef property<edge_weight_t, int> WeightProperty;

// adjacency list with properties
typedef adjacency_list<vecS, vecS, undirectedS, no_property, WeightProperty, IndexProperty> Graph;

// Vertex and edge type
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator EdgeIterator;

// Property maps for accessing the properties
typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef property_map<Graph, vertex_index_t>::type IndexMap;

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	
	for(int i = 0; i < t; i++) {
		int m, n; cin >> n >> m;

		Graph G(n);
		WeightMap weightMap = get(edge_weight, G);

		for(int j = 0; j < m; j++) {
			int v1, v2, w;
			cin >> v1 >> v2 >> w;
			Edge e;
			tie(e, tuples::ignore) = add_edge(v1, v2, G);
			weightMap[e] = w;
		}

		vector<Edge> spanningTree;
		kruskal_minimum_spanning_tree(G, back_inserter(spanningTree));
		int sumOfWeights = 0;		
		
		Graph mstGraph(n);
		WeightMap mstWeightMap = get(edge_weight, mstGraph);
		for (vector<Edge>::iterator ei = spanningTree.begin(); ei != spanningTree.end(); ++ei) {
			sumOfWeights += weightMap[*ei];
		}
		
		vector<int> distances(n);
		vector<Vertex> p_map(num_vertices(G));

		Vertex startVertex = vertex(0, G);
		dijkstra_shortest_paths(G, startVertex, predecessor_map(&p_map[0]).distance_map(&distances[0]));

		int longestDistance = 0;
		for(int k = 0; k < n; k++) {
			int distance = distances[k];
			
			if(distance > longestDistance) {
				longestDistance = distance;
			}
		}

		cout << sumOfWeights << " " << longestDistance << endl;

		/* Playing around with backtracking shortest path.
		IndexMap index;
		int target = 3;
		while(target != p_map[index[vertex(target, G)]]) {
			cout << target << "-" << p_map[index[vertex(target, G)]] << "\n";
			target = p_map[index[vertex(target, G)]];
		}
		*/
	}
}
