#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
using namespace std;

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void program_1(int a, int b) {
    Program qp (CGAL::SMALLER, true, 0, false, 0);      // use bounds instead of extra constraints.
    const int X = 0;
    const int Y = 1;

    // minimize -b*y + a*x^2
    qp.set_c(Y, -b);
    qp.set_d(X, X, a*2);

    // x + y <= 4 
    qp.set_a(X, 0, 1);
    qp.set_a(Y, 0, 1);
    qp.set_b(0, 4);

    // 4x + 2y <= a*b
    qp.set_a(X, 1, 4);
    qp.set_a(Y, 1, 2);
    qp.set_b(1, a*b);

    // -x + y <= 1
    qp.set_a(X, 2, -1);
    qp.set_a(Y, 2, 1);
    qp.set_b(2, 1);
    
    Solution s = CGAL::solve_quadratic_program(qp, ET());
    assert(s.solves_quadratic_program(qp));
    
    if(s.is_optimal()) { 
        int sign;
        (s.objective_value() <= 0) ? sign = -1 : sign = 1;
        cout << floor(to_double(sign*s.objective_value())) << "\n";     // std::ceil?, ceil_to_double fct?
    } else if(s.is_unbounded()) 
        cout << "unbounded\n";
    else if(s.is_infeasible()) 
        cout << "no\n";

}

void program_2(int a, int b) {
    Program qp (CGAL::SMALLER, false, 0, true, 0);
    const int X = 0;
    const int Y = 1;
    const int Z = 2;
    
    qp.set_l(Z, 0);
    qp.set_u(Z, false);

    // minimize a*x^2 + b*y + z^4
    qp.set_d(X, X, 2*a);
    qp.set_d(Z, Z, 2*1);        // by convention: we multiply value by 2.

    qp.set_c(Y, b);

    qp.set_a(X, 0, 1);
    qp.set_a(Y, 0, 1);
    qp.set_b(0, -4);
    qp.set_r(0, CGAL::LARGER);

    qp.set_a(X, 1, 4);
    qp.set_a(Y, 1, 2);
    qp.set_a(Z, 1, 1);
    qp.set_b(1, -1*a*b);
    qp.set_r(1, CGAL::LARGER);

    qp.set_a(X, 2, -1);
    qp.set_a(Y, 2, 1);
    qp.set_b(2, -1);
    qp.set_r(2, CGAL::LARGER);

    qp.set_a(Z, 3, 1);
    qp.set_b(3, 0);
    qp.set_r(3, CGAL::LARGER);

    Solution s = CGAL::solve_quadratic_program(qp, ET());
    assert(s.solves_quadratic_program(qp));
    
    if(s.is_optimal()) {
        double result = ceil(CGAL::to_double(s.objective_value()));        
        cout << result << "\n";
    }
    else if(s.is_unbounded()) 
        cout << "unbounded\n";
    else if(s.is_infeasible()) 
        cout << "no\n";
}

int main() {
    ios_base::sync_with_stdio(false); 
    cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    int p, a, b;
    while(true) {
        cin >> p;
        if(p == 0) return 0;
        cin >> a >> b;
        if(p == 1) program_1(a, b);
        if(p == 2) program_2(a, b); 
    }
}
