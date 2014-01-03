#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Min_circle_2_traits_2<K> MinCircleTraits;
typedef CGAL::Min_circle_2<MinCircleTraits> Min_circle;
typedef vector<pair<K::FT, K::Point_2> > dp;

bool pairCompare(const pair<K::FT, K::Point_2>& lhs, const pair<K::FT, K::Point_2>& rhs) {
    return lhs.first > rhs.first;
}

double ceil_to_double(const K::FT& x) {
    double a = std::ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a >= x+1) a -= 1;
    return a;
}

void testcase() {
    int N; cin >> N;
    dp cities;

    int x, y; cin >> x >> y;
    K::Point_2 capitol(x, y);
    cities.push_back(make_pair(0, capitol));

    for(int n = 1; n < N; ++n) {
        int x, y; cin >> x >> y;
        K::Point_2 p(x, y);
        K::FT dist = CGAL::squared_distance(capitol, p);
        cities.push_back(make_pair(dist, p));
    }
    sort(cities.begin(), cities.end(), pairCompare);

    int i = 0;
    K::FT r1 = cities[0].first, r2 = 0;
    K::FT t = r1;
    Min_circle mc;
    while(r1 > r2 && i < N-1) {
        r1 = cities[i+1].first;
        
        //cout << "insert in mincircle: " << cities[i].second << "\n";
        mc.insert(cities[i].second);
        MinCircleTraits::Circle c = mc.circle();
        r2 = c.squared_radius();
        //cout << "r1: " << r1 << "\n" << "r2: " << r2 << "\n";
        //cout << "diff: " << abs(r1 - r2) << " r1: " << r1 << " r2:" << r2 << "\n";
        ++i;
    }

    if(r1 == r2)
        t = r1;
    if(r2 > r1) 
        t = min(r2, cities[i-1].first);

    cout << ceil_to_double(t) << "\n";
}

int main() {
    cin.sync_with_stdio(false);
  	cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    int TC; cin >> TC;
    while(TC--) testcase();
}
