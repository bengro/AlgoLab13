#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/enum.h>
#include <climits>
using namespace std;
 
typedef CGAL::Exact_predicates_exact_constructions_kernel K;

double floor_to_double(const K::FT& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase(int n) {
	K::Ray_2 ray;
	double x1, y1, x2, y2; cin >> ray;
 	
 	bool min_exists = false;
 	K::FT current_dist;
 	K::Point_2 current_point; 

 	for(size_t o = 0; o < n; ++o) {
 		double r, s, t, u; cin >> r >> s >> t >> u;
		K::Point_2 p1(r, s);
		K::Point_2 p2(t, u);
		K::Segment_2 obstacle (p1, p2);

		if(CGAL::do_intersect(ray, obstacle)) {
	 		K::Point_2 intersection_point;
			CGAL::Object o = CGAL::intersection(ray, obstacle);
			if(const K::Point_2* p = CGAL::object_cast<K::Point_2>(&o)) 
				intersection_point = *p;
			else if (const K::Segment_2* s = CGAL::object_cast<K::Segment_2>(&o))
	   			intersection_point = 
	   					CGAL::has_smaller_distance_to_point(ray.source(), s->source(), s->target()) ? 
	   					s->source() : s->target();
			else throw runtime_error("strange segment intersection");
			K::FT intersection_dist = CGAL::squared_distance(intersection_point, ray.source());
			if(!min_exists || current_dist > intersection_dist) {
				current_dist = intersection_dist;
				current_point = intersection_point;
				min_exists = true;
			}
		}
	}

	if(min_exists) cout << floor_to_double(current_point.x()) << " " << floor_to_double(current_point.y()) << "\n";
	else cout << "no\n";
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