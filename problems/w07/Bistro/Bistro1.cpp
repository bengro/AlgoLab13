#include <vector>
#include <iostream>
#include <cmath>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator faces_iterator;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase(int n) {
	vector<K::Point_2> delaunay_vertices;
	for(int i = 0; i < n; ++i) {
		K::Point_2 p; cin >> p;
		delaunay_vertices.push_back(p);
	}

	Triangulation t;
	t.insert(delaunay_vertices.begin(), delaunay_vertices.end());

	int points; cin >> points;
	for(int i = 0; i < points; ++i) {
		K::Point_2 p; cin >> p;
		Triangulation::Vertex_handle v = t.nearest_vertex(p);
		K::Point_2 vp = v->point();
		K::FT distance = CGAL::squared_distance(p, vp);
		cout << floor_to_double(distance) << "\n";
	}
}

int main() {
	cin.sync_with_stdio(false);
  	cout << std::setiosflags(std::ios::fixed) << std::setprecision(0); 
	while(true) {
		int n; cin >> n;
		if(n == 0) return 0;
		testcase(n);
	}
	return 0;
}