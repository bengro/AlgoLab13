#include <iostream>
#include <vector>
#include <set>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel	 	K;
typedef CGAL::Delaunay_triangulation_2<K> 						D_Triangulation;
typedef D_Triangulation::Finite_edges_iterator                  FEI;
typedef set<D_Triangulation::Vertex_handle>                      vertex_set;

void testcase() {
	int n, d; cin >> n >> d;
    
    vector<K::Point_2> points;
	for(int i = 0; i < n; ++i) {
		int x, y; cin >> x >> y;
        points.push_back(K::Point_2(x, y));
	}
	
	D_Triangulation t;
	t.insert(points.begin(), points.end());
    vertex_set in_danger;
    for(FEI e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        D_Triangulation::Vertex_handle v1 = e->first->vertex((e->second + 1) % 3);
        D_Triangulation::Vertex_handle v2 = e->first->vertex((e->second + 2) % 3);
        K::FT squared_d = CGAL::squared_distance(v1->point(), v2->point());
        double distance = CGAL::sqrt(squared_d);
        
        if(distance < d) {
           in_danger.insert(v1); in_danger.insert(v2);
        }
    }
    cout << in_danger.size() << "\n";

}

int main() {
	int TC; std::cin >> TC;
	while(TC--) testcase();
}
