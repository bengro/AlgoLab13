#include <vector>
#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h> // use inexact because Input points == output points.
#include <CGAL/Delaunay_triangulation_2.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_edges_iterator FEI;

double ceil_to_double(const K::FT& x)
{
	double a = ceil(CGAL::to_double(x));
	while (a < x) a += 1;
	while (a-1 >= x) a -= 1;
	return a;
}

void testcase(int n) {
	vector<K::Point_2> points;
	for(int i = 0; i < n; ++i) {
		K::Point_2 p; cin >> p;
		points.push_back(p);
	}

	Triangulation t;
	t.insert(points.begin(), points.end());
	K::FT min_length;
	bool min_set = false;
 	for (FEI e = t.finite_edges_begin(); e != t.finite_edges_end(); e++) {
 		// REMEMBER bad idea: K::Segment_2 seg = t.segment(edge); seg.squared_length().
 		Triangulation::Vertex_handle v1 = e->first->vertex((e->second + 1) % 3);
		Triangulation::Vertex_handle v2 = e->first->vertex((e->second + 2) % 3);

		K::FT length = CGAL::squared_distance(v1->point(), v2->point());
  		if(!min_set || min_length > length) {
 			min_length = length;
 			min_set = true;
 		}
 	}

	double seconds = ceil_to_double(CGAL::sqrt(min_length)*50); 	
 	cout << seconds << "\n";
}

int main() {
	cin.sync_with_stdio(false);
  	cout << std::setiosflags(std::ios::fixed) << std::setprecision(0); 
	while(true) {
		int n; cin >> n;
		if(n == 0) return 0;
		testcase(n);
	}
}