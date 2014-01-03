#include <iostream>
#include <vector>
#include <cmath>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

double ceil_to_double(const K::FT& x)
{
  double a = ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void testcase(int n) {
	vector<K::Point_2> citizens;
	for(int coord = 0; coord < n; ++coord) {
		double x, y; cin >> x >> y;
		K::Point_2 citizen(x, y);
		citizens.push_back(citizen);
	}

	Min_circle mc(citizens.begin(), citizens.end(), true);	// true important for speed.
	Traits::Circle c = mc.circle();
 	K::FT radius = sqrt(c.squared_radius());

 	cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);	// scientific notation will be used otherwise!
	cout << ceil_to_double(radius) << "\n";
}

int main() {
	while(true) {
		int n; cin >> n;
		if(n == 0) return 0;
		testcase(n);
	}
	return 0;
}