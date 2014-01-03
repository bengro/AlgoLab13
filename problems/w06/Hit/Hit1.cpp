#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

void testcase(int n) {
	double x1, y1, x2, y2; 
	cin >> x1 >> y1 >> x2 >> y2;
	K::Point_2 p1(x1, y1);
	K::Point_2 p2(x2, y2);
	K::Ray_2 ray(p1, p2);

	vector<K::Segment_2> obstacles;
	for(int o = 0; o < n; ++o) {
		double r, s, t, u; 
		cin >> r >> s >> t >> u;
		K::Point_2 p1(r, s);
		K::Point_2 p2(t, u);
		K::Segment_2 obstacle(p1, p2);
		obstacles.push_back(obstacle);
	}

	bool intersect = false;
	for(int obstacle = 0; obstacle < obstacles.size(); ++obstacle) {
		if(CGAL::do_intersect(obstacles[obstacle], ray)) {
			intersect = true;
			break;
		}
	}

	(intersect) ? cout << "yes\n" : cout << "no\n";
}

int main() {
	while(true) {
		int n; cin >> n;
		if(n == 0) return 0;
		testcase(n);	
	}
}