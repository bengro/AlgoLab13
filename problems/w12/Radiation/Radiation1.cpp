#include <iostream>
#include <vector>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
using namespace std;

struct Point { int x; int y; int z; };

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET, IT;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
map<pair<int, int>, IT> Powers;

IT pw(int b, int e) {
    if(Powers[make_pair(b, e)] != 0)  
        return Powers[make_pair(b, e)];

    IT sol = 1;
    for(int i = 1; i <= e; ++i) {
        sol *= b;
    }
    Powers[make_pair(b, e)] = sol;
    return sol;
}

void testcase() {
    int H, T; cin >> H >> T;
    
    vector<Point> cells; 
    for(int c = 0; c < (H+T); ++c) {
        Point p;
        cin >> p.x >> p.y >> p.z;
        cells.push_back(p);
    }

    int lo = 0; 
    int hi = 29;
    int d = -1;
    vector<int> results(30, -1);
    
    while(lo <= hi) {
        Program lp(CGAL::SMALLER, false, 0, false, 0);
        lp.set_c(0, -1);
        lp.set_u(0, true, 1); // MISTAKE!!! before set_u(0, 1);

        int deg = lo + (hi-lo+1)/2;
        for(int row = 0; row < cells.size(); ++row) {
            lp.set_b(row, 0);
            if(row >= H) { // tumor cell
                lp.set_a(0, row, -1); 
                lp.set_r(row, CGAL::LARGER);
            }
            
            int col = 1;
            for(int i = 0; i <= deg; ++i) {
                for(int j = 0; j <= deg-i; ++j) {
                    for(int k = 0; k <= deg-i-j; ++k) {
                        IT coeff = pw(cells[row].x, i) * pw(cells[row].y, j) * pw(cells[row].z, k);
                        lp.set_a(col++, row, coeff);
                    }
                }
            }
        }

        CGAL::Quadratic_program_options options;
        options.set_pricing_strategy(CGAL::QP_BLAND);
        Solution s = CGAL::solve_linear_program(lp, ET(), options); 
        results[deg] = (CGAL::to_double(s.objective_value()) < 0 && s.is_optimal()) ? true : false;
        
        if((lo < 29) && (results[lo] == 0) && (results[lo+1] == 1)) {
            d = lo+1;
            break;
        } else if((hi > 0) && (results[hi] == 1 && results[hi-1] == 0)) {
            d = hi;
            break;
        } else if(results[0] == 1) {
            d = 0; 
            break;
        } else {
            if(results[deg]) hi = deg-1;
            else lo = deg + 1;
        }
    }
    (d == -1) ? cout << "Impossible!\n" : cout << d << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    int TC; cin >> TC;
    while(TC--) testcase();
}
