#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
using namespace std;

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase(int N, int M) {
    Program qp (CGAL::SMALLER, true, 0, false, 0);
    
    for(int n = 0; n < N; ++n) {
        int c, r; cin >> c >> r;
        qp.set_a(n, 0, c);
        qp.set_a(n, 1, r);
    }
    qp.set_r(1, CGAL::LARGER);

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            int vij; cin >> vij;
            qp.set_d(i, j, 2*vij);
        }
    }

    for(int m = 0; m < M; ++m) {
        int C, V; cin >> C >> V;
        int R = 0;
        qp.set_b(0, C);
        qp.set_b(1, R);
        
        int lo = 0; 
        int hi = 100;
        bool fixed = false;
        while(lo <= hi) {
            int mid = (fixed) ? (lo + (hi-lo+1)/2) : hi;

            qp.set_b(1, mid);
            Solution s = CGAL::solve_quadratic_program(qp, ET());
            assert(s.solves_quadratic_program(qp));

            if(s.is_optimal() && s.objective_value() <= V) {
                R = mid;
                if(!fixed) { 
                    lo = hi+1;
                    hi = 2*hi;
                } else {
                    lo = mid+1;
                }
            } else {
                fixed = true;
                hi = mid-1;
            }
        }
        cout << R << "\n";
    }
}

int main() {
    while(true) {
        int N, M; cin >> N >> M;
        if(N == 0 && M == 0) return 0;
        testcase(N, M);
    }
}
