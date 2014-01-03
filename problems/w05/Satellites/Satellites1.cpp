#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/graph/bipartite.hpp>
#include <boost/graph/depth_first_search.hpp>
using namespace std;
using namespace boost;

#define UNVISITED 0
#define VISITED 1
#define LEFT 0
#define RIGHT 1

typedef vector<int> vi;
typedef property<vertex_index_t, int> VertexProperties;
typedef adjacency_list<vecS, vecS, undirectedS, VertexProperties, no_property> Graph;
typedef adjacency_list<vecS, vecS, directedS, VertexProperties, no_property> Digraph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_iterator VertexIterator;
typedef property_map<Graph, vertex_index_t>::type VIndexMap; 

vi visited;

struct mark_visited : public boost::dfs_visitor<> {
	template <class Vertex, class Digraph>
	void finish_vertex(Vertex u, const Digraph& g) {
		visited[u] = VISITED;
		//cout << u << " set to visited. \n";
	}
};

void testcase() {
	int groundstations, satellites, links; cin >> groundstations >> satellites >> links;
	
	Digraph g_final(groundstations + satellites);
	Graph g(groundstations + satellites);

	vi color(num_vertices(g));
	for(int edge = 0; edge < links; ++edge) {
		int v1, v2; cin >> v1 >> v2;
		v2 = v2 + groundstations;
		add_edge(v1, v2, g);
		add_edge(v1, v2, g_final);
		color[v1] = LEFT;
		color[v2] = RIGHT;
	}

	vector<Vertex> mateMap(num_vertices(g), UNVISITED);
	bool success = checked_edmonds_maximum_cardinality_matching(g, &mateMap[0]);
	

	visited.clear();
	visited.assign(num_vertices(g), UNVISITED);
	for(int matching = 0; matching < mateMap.size(); ++matching) {
		if(color[matching] == RIGHT && mateMap[matching] != graph_traits<Graph>::null_vertex()) 
            add_edge(matching, mateMap[matching], g_final);  // add an edge from R to L.
		if(mateMap[matching] == graph_traits<Graph>::null_vertex() && color[matching] == LEFT) 
            visited[matching] = VISITED;
	}

	mark_visited vis;
	for(int start = 0; start < visited.size(); ++start) {
		if((color[start] == LEFT) && (visited[start] == VISITED)) {
			//cout << "start dfs at " << start << " visited: " << visited[start] << "\n";
			//depth_first_search(g_final, root_vertex(vertex(start, g_final)).visitor(vis));
			vector<default_color_type> colors(num_vertices(g_final));
			depth_first_visit(g_final, vertex(start, g_final), vis, &colors[0]);
		}
	}

	vi solution_ground;
	vi solution_sat;
	for(int c = 0; c < color.size(); ++c) {
		if(color[c] == LEFT && visited[c] == UNVISITED) {
			solution_ground.push_back(c);
		}
		if(color[c] == RIGHT && visited[c] == VISITED) {
			solution_sat.push_back(c-groundstations);
		}
	}

	cout << solution_ground.size() << " " << solution_sat.size() << "\n";
	for(int sol = 0; sol < solution_ground.size(); ++sol) cout << solution_ground[sol] << " ";
	for(int sol = 0; sol < solution_sat.size(); ++sol) cout << solution_sat[sol] << " ";
	cout << "\n";
}

int main() {
	int TC; cin >> TC;
	while(TC--) testcase();
	return 0;
}
