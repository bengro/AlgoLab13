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

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;

    while(n > 0) {
        int d; cin >> d;
        Program lp(CGAL::SMALLER, false, 0, false, 0);
        lp.set_c(d, -1);
        lp.set_l(d, true, 0);

        for(int i = 0; i < n; ++i) {
            int l2 = 0;
            for(int j = 0; j < d; ++j) {
                int a; cin >> a;
                lp.set_a(j, i, a);
                l2 += a*a;
            }
            l2 = sqrt(l2);
            lp.set_a(d, i, l2);

            int b; cin >> b;
            lp.set_b(i, b);
        }
        
        Solution s = CGAL::solve_linear_program(lp, ET());
        if(s.is_infeasible()) {
            cout << "none\n";
        } else if(s.is_unbounded()) {
            cout << "inf\n";
        } else {
            cout << floor(-CGAL::to_double(s.objective_value())) << "\n";
        }

        cin >> n;
    }
}
