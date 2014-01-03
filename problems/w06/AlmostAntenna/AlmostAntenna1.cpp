#include <set>
#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> MinCircleTraits;
typedef CGAL::Min_circle_2<MinCircleTraits> Min_circle;
typedef Min_circle::Support_point_iterator support_iter;

double ceil_to_double(const K::FT& x)
{
	double a = ceil(CGAL::to_double(x));
	while (a < x) a += 1;
	while (a-1 >= x) a -= 1;
	return a;
}

void testcase(int n) {
	vector<K::Point_2> points;
	for(int point = 0; point < n; ++point) {
		double x, y; cin >> x >> y;
		K::Point_2 p(x, y);
		points.push_back(p);
	}
	
	Min_circle min_circle(points.begin(), points.end(), true);
	MinCircleTraits::Circle c = min_circle.circle();
	K::FT old_radius = c.squared_radius();
	K::FT min_radius; bool min_radius_set = false;

	for(support_iter iter = min_circle.support_points_begin(); iter != min_circle.support_points_end(); ++iter) {
		// find supporting point in set. Delete it temporarily.
		vector<K::Point_2>::iterator temp_it = find(points.begin(), points.end(), *iter);
		K::Point_2 point = *temp_it;
		points.erase(temp_it);
		
		// create new min_circle, get squared radius.
		Min_circle temp_circle (points.begin(), points.end(), true);
		MinCircleTraits::Circle actual_circle = temp_circle.circle();
		K::FT new_radius = actual_circle.squared_radius();

		// compare radius of old min_circle with new one.
		if(new_radius == old_radius) { 
			min_radius = old_radius; break; 
		} else if(!min_radius_set || new_radius < min_radius) {
			min_radius = new_radius;
			min_radius_set = true;
		}

		// reinsert the point
		points.push_back(point);
	}

	double result = ceil_to_double(CGAL::sqrt(min_radius));
	cout << result << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
  	cout << std::setiosflags(std::ios::fixed) << std::setprecision(0); 
	while(true) {
		int n; cin >> n;
		if(n == 0) return 0;
		testcase(n);
	}
	return 0;
}