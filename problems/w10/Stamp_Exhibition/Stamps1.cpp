#include <iostream>
#include <cassert>
#include <cmath>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
using namespace std;

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpq.h>
typedef CGAL::Gmpq ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase() {
    int L, S, W; cin >> L >> S >> W;

    vector<K::Point_2> lamps;
    for(int l = 0; l < L; ++l) {
        int x, y; cin >> x >> y;
        lamps.push_back(K::Point_2(x, y));
    }
    
    vector<pair<K::Point_2, double> > stamps;
    for(int s = 0; s < S; ++s) {
        int x, y; double m; cin >> x >> y >> m;
        stamps.push_back(make_pair(K::Point_2(x, y), m));
    }

    vector<K::Segment_2> walls;
    for(int w = 0; w < W; ++w) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        walls.push_back(K::Segment_2(K::Point_2(x1, y1), K::Point_2(x2, y2)));
    }
    
    if(S == 0) { cout << "yes\n"; return; }
    if(L == 0) { cout << "no\n"; return; } 

    Program lp (CGAL::SMALLER, true, 1, true, pow(2.0, 12));
    for(int l = 0; l < L; ++l) {
        for(int s = 0; s < S; ++s) {
            bool intersect = false;
            for(int w = 0; w < W; ++w) {
                K::Segment_2 stamp_lamp(stamps[s].first, lamps[l]);
                if(CGAL::do_intersect(stamp_lamp, walls[w])) {
                    intersect = true;
                    break;
                }
            }

            double param = 0;
            if(!intersect) 
                param = 1.0/CGAL::squared_distance(stamps[s].first, lamps[l]);
            lp.set_a(l, s, param);
            lp.set_a(l, S+s, param);
            lp.set_b(s, stamps[s].second);
            lp.set_b(S+s, 1.0);
            lp.set_r(S+s, CGAL::LARGER);
        }
    }
    
    Solution s = CGAL::solve_linear_program(lp, ET());
    assert (s.solves_linear_program(lp));
    (!s.is_infeasible()) ? cout << "yes\n" : cout << "no\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
