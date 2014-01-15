#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}

void testcase(int N) {
    vector<K::Point_2> points;
    for(int n = 0; n < N; ++n) {
        double x, y; cin >> x >> y;
        points.push_back(K::Point_2(x, y));
    }
    Min_circle mc(points.begin(), points.end(), true);
    
    K::FT min_rad; bool min_set = false;
    for(Min_circle::Support_point_iterator it = mc.support_points_begin(); it != mc.support_points_end(); ++it) {
        vector<K::Point_2>::iterator sp = find(points.begin(), points.end(), *it);
        iter_swap(sp, points.begin());
        Min_circle mc2(points.begin()+1, points.end(), true);
        Traits::Circle c = mc2.circle();
        K::FT radius= c.squared_radius();
        if(radius < min_rad || !min_set) {
            min_rad = radius;
            min_set = true;
        }
    }
   
    cout << ceil_to_double(CGAL::sqrt(min_rad))<< "\n";
}

int main() {
    cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    while(true) {
        int N; cin >> N;
        if(N == 0) return 0;
        testcase(N);
    }
}
