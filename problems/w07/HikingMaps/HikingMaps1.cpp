#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/ch_jarvis.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;      // does not pass last TC with exact constructions.
typedef vector<int> vi;
typedef vector<vi> vii;

void testcase() {
    int M, N; cin >> M >> N; // M-1 legs, N maps.
    
    vector<pair<K::Point_2, K::Point_2> > legs;     // using a vector a segment, prevents from passing the 4th TC.
    K::Point_2 prev; 
    cin >> prev;
    for(int m = 1; m < M; ++m) {
        int x, y; cin >> x >> y;
        K::Point_2 now(x, y);
        legs.push_back(make_pair(prev, now));
        prev = now;
    }
    
    vii lists(M-1); // storing "leg contained by map" data.
    for(int n = 0; n < N; ++n) {
        vector<K::Point_2> points(6);
        for(int i = 0; i < 6; ++i)
            cin >> points[i];
       
        vector<K::Point_2> ccw; // store the given vertices in counter-clockwise fashion.
        CGAL::ch_jarvis_march(points.begin(), points.end(), points[0], points[0], back_inserter(ccw));
        if(points[1] != ccw[1]) {   // ugly... making sure two consecutive vertices span a triangle edge.
            ccw.clear();
            CGAL::ch_jarvis_march(points.begin(), points.end(), points[1], points[1], back_inserter(ccw));
        }
        
        for(int l = 0; l < legs.size(); ++l) {  // iterate over each leg. 
            bool isOutside;     // is set if to true, if origin or source is to the right to the edges.
            for(int p = 0; p < ccw.size()-1; p = p+2) {
                isOutside = (CGAL::right_turn(ccw[p], ccw[p+1], legs[l].first) || 
                CGAL::right_turn(ccw[p], ccw[p+1], legs[l].second)) ? true : false;   // if one of the leg points outside, then set to yes.
                if(isOutside) break;
            }
            if(!isOutside) lists[l].push_back(n);   // both end points of leg are inside.
        }
    }
    
    vi pointers(M-1, 0);
    priority_queue<int> max_heap;
    priority_queue<pair<int, int>, std::vector<pair<int, int> >, greater<pair<int, int> > > min_heap;
    for(int l = 0; l < lists.size(); ++l) {
        max_heap.push(lists[l][0]);
        min_heap.push(make_pair(lists[l][0], l));
    }
    
    int min_interval = INT_MAX;
    while(true) {
        pair<int, int> min_pair = min_heap.top(); min_heap.pop();
		int min_value = min_pair.first;
		int min_list = min_pair.second;

        int max_value = max_heap.top();
		int min_new = abs(max_value - min_value);
		min_interval = min(min_new, min_interval);
        if(pointers[min_list] == lists[min_list].size()-1) break;

        pointers[min_list]++;
        int new_value = lists[min_list][pointers[min_list]];
		max_heap.push(new_value);
		min_heap.push(make_pair(new_value, min_list));
    }
   
    cout << min_interval+1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    int TC; cin >> TC;
    while(TC--) testcase();
    return 0;
}
