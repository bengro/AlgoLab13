#include <iostream>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel           K;
typedef CGAL::Delaunay_triangulation_2<K>                           Delaunay;
typedef Delaunay::Finite_faces_iterator                             FFI;
typedef Delaunay::Finite_edges_iterator                             FEI;

double ceil_to_double(const K::FT& x) {
	double a = ceil(CGAL::to_double(x));
	while (a < x) a += 1;
	while (a-1 >= x) a -= 1;
	return a;
}

template<typename T>
K::FT check_intersection(const T* obj, const K::Point_2 p1, const vector<K::Segment_2>& rectangle) {
    for (int i = 0; i < 4; ++i) {
        if(!do_intersect(rectangle[i], *obj)) continue;
        CGAL::Object o = intersection(rectangle[i], *obj);
        const K::Point_2* p2 = CGAL::object_cast<K::Point_2>(&o);
        K::FT sqrd = CGAL::squared_distance(p1, *p2);
        return sqrd;
    }
    return 0;
}

void testcase(int N) {
    vector<K::Point_2> points;
    vector<K::Segment_2> rectangle;

    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    K::Point_2 sw (x1, y1); 
    K::Point_2 nw(x1, y2); 
    K::Point_2 se(x2, y1); 
    K::Point_2 ne(x2, y2);
    rectangle.push_back(K::Segment_2(sw, nw));
    rectangle.push_back(K::Segment_2(se, ne));
    rectangle.push_back(K::Segment_2(sw, se));
    rectangle.push_back(K::Segment_2(nw, ne));

    for(int n = 0; n < N; ++n) {
        double x, y; cin >> x >> y;
        points.push_back(K::Point_2(x, y));
    }
    
    // O(n log n)
	Delaunay t;
    t.insert(points.begin(), points.end());
    K::FT min_rad;
    
    // check corners
    min_rad = CGAL::squared_distance(sw, t.nearest_vertex(sw)->point());
    min_rad = max(min_rad, CGAL::squared_distance(se, t.nearest_vertex(se)->point()));
    min_rad = max(min_rad, CGAL::squared_distance(nw, t.nearest_vertex(nw)->point()));
    min_rad = max(min_rad, CGAL::squared_distance(ne, t.nearest_vertex(ne)->point()));

    // iterate over all faces to find largest circle - O(N)
    for(FFI f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f) {
        K::Point_2 cc = t.circumcenter(f);
        if(cc.x() >= x1 && cc.x() <= x2 && cc.y() >= y1 && cc.y() <= y2) {
            K::Point_2 point = f->vertex(1)->point();
            K::FT dist = CGAL::squared_distance(point, cc);
            min_rad = max(min_rad, dist);
        }
    }
    
    // check for intersection with rectangle boundary - O(n*4)
    for(FEI e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        CGAL::Object o = t.dual(e);
        if(const K::Ray_2* r = CGAL::object_cast<K::Ray_2>(&o)) 
            min_rad = max(min_rad, check_intersection(r, t.segment(e).source(), rectangle));
        else if(const K::Segment_2* s = CGAL::object_cast<K::Segment_2>(&o))
            min_rad = max(min_rad, check_intersection(s, t.segment(e).source(), rectangle));
    }

    cout << ceil(CGAL::sqrt(to_double(min_rad))) << "\n";
}

int main() {
    cin.sync_with_stdio(false);
  	cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    while(true) {
        int N; cin >> N;
        if(N == 0) return 0;
        testcase(N);
    }
}
