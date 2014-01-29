#include <iostream>
#include <vector>
#include <climits>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}

void testcase() {
    int N; cin >> N;

    vector<pair<K::FT, K::Point_2> > points;
    int x1, y1; cin >> x1 >> y1;
    K::Point_2 t1 = K::Point_2(x1, y1);
    points.push_back(make_pair(0, t1));

    for(int n = 1; n < N; ++n) {
        int x, y; cin >> x >> y;
        K::Point_2 p = K::Point_2(x, y);
        points.push_back(make_pair(CGAL::squared_distance(t1, p), p));
    }
    sort(points.begin(), points.end());
    
    K::FT r1 = points[N-1].first;
    K::FT r2 = 0;
    K::FT s = r1;
    int i = N-2;
    Min_circle mc;
    while(r1 > r2 && i > 0) {
        r1 = points[i].first;
        mc.insert(points[i+1].second);
        Traits::Circle c = mc.circle();
        r2 = c.squared_radius();
        --i;
    }

    if(r1 == r2)
        s = r1;
    if(r2 > r1)
        s = min(points[i+2].first, r2);

    cout << ceil_to_double(s) << "\n";
}

int main() {
    cin.sync_with_stdio(false);
    cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    int TC; cin >> TC;
    while (TC--) testcase();
    return 0;
}
