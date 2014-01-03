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

// N: nutrients, M: foods
void testcase(int N, int M) {
    Program lp(CGAL::SMALLER, true, 0, false, 0);

    for(int n = 0; n < N; ++n) {
        int min, max; cin >> min >> max;
        lp.set_b(n, min);
        lp.set_r(n, CGAL::LARGER);
        lp.set_b(N+n, max);
    }

    for(int m = 0; m < M; ++m) {
        int p; cin >> p;
        lp.set_c(m, p);

        for(int n = 0; n < N; ++n) {
            int amount; cin >> amount;
            lp.set_a(m, n, amount);
            lp.set_a(m, N+n, amount);
        }
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    assert (s.solves_linear_program(lp));

    if(s.is_infeasible())
        cout << "No such diet.\n";
    else
        cout << floor(to_double(s.objective_value())) << "\n";
}

int main() {
    while(true) {
        int N, M; cin >> N >> M;
        if(N == 0 && M == 0) return 0;
        testcase(N, M);
    }
}
