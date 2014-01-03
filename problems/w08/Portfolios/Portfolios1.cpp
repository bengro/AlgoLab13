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

// N: assets, M: portfolios
void testcase(int N, int M) {
    Program qp(CGAL::SMALLER, true, 0, false, 0);

    for(int n = 0; n < N; ++n) {
        int c, r; cin >> c >> r;
        qp.set_a(n, 0, c);
        qp.set_a(n, 1, r);
    }
    
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            int cij; cin >> cij;
            qp.set_d(i, j, 2*cij);
        }
    }

    for(int m = 0; m < M; ++m) {
        int C, R, V; cin >> C >> R >> V;
        qp.set_b(0, C);
        qp.set_b(1, R);
        qp.set_r(1, CGAL::LARGER);

        Solution s = CGAL::solve_quadratic_program(qp, ET());
        assert(s.solves_quadratic_program(qp));

        //cout << s; 

        if(s.is_optimal() && (to_double(s.objective_value()) <= V)) {
            cout << "Yes.\n";
        } else {
            cout << "No.\n";
        }
    }
}

int main() {
    while(true) {
        int N, M; cin >> N >> M;
        if(N == 0 && M == 0) return 0;
        testcase(N, M);
    }
}
