#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
typedef vector<pair<K::Point_2, int> > vp;

int P, L, H;

vector<int> get_winners(int maxLamp, vp& participants, vector<K::Point_2>& lamps) {
    Delaunay t;
    t.insert(lamps.begin(), lamps.begin()+maxLamp);
    
    vector<int> winners;
    for(int p = 0; p < P; ++p) {
        int radius = participants[p].second;
        K::Point_2 loc = participants[p].first;
        Delaunay::Vertex_handle lamp = t.nearest_vertex(loc);
        K::FT dist = CGAL::squared_distance(loc, lamp->point());
        K::FT dist_p = H+radius;
        if(dist >= dist_p*dist_p) {
            winners.push_back(p);
        }
    }
    return winners;
}

void testcase() {
    cin >> P >> L;
    vp participants;
    for(size_t p = 0; p < P; ++p) {
        int x, y, r; 
        cin >> x >> y >> r;
        participants.push_back(make_pair(K::Point_2(x, y), r));
    }

    cin >> H;

    vector<K::Point_2> lamps;
    for(size_t l = 0; l < L; ++l) {
        int x, y; 
        cin >> x >> y;
        lamps.push_back(K::Point_2(x, y));
    }
    
    vector<int> winners;
    winners = get_winners(L, participants, lamps); 
    if(winners.size() != 0) {
        for(int i = 0; i < winners.size(); ++i) cout << winners[i] << " ";
        cout << "\n";
        return;
    }

    int lo = 0;
    int hi = L;
    int D = -1;
    map<int, int> results;
    while(lo < hi) {
        int mid = lo + (hi-lo+1)/2;
        vector<int> survivers = get_winners(mid, participants, lamps);
        int count = survivers.size();
        results[mid] = (count == 0) ? -1 : count;

        if(lo+1 == hi && results[lo] != 0 && results[hi] == -1) {
            D = lo;
            break;
        }

        if(count == 0) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    winners = get_winners(D, participants, lamps); 
    for(int i = 0; i < winners.size(); ++i) cout << winners[i] << " ";
    cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int TC; cin >> TC;
    while (TC--) testcase();
    return 0;
}
